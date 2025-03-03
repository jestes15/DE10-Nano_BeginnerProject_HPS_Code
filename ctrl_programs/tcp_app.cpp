#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

#include "main.h"

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
  public:
    session(tcp::socket socket) : socket_(std::move(socket))
    {
    }

    void start()
    {
        memory_manager_instance = std::make_shared<memory_manager>();

        do_read();
    }

  private:
    void do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                [this, self](boost::system::error_code ec, std::size_t length) {
                                    if (!ec)
                                    {
                                        uint64_t addr = *reinterpret_cast<uint64_t *>(data_);
                                        do_write(addr);

                                        printf("0x%08llx\n", addr);
                                    }
                                });
    }

    void do_write(uint64_t address)
    {
        auto self(shared_from_this());

        int mem_region = 0;
        uint64_t offset = 0;

        if (address > FPGASLAVES && address < FPGASLAVES + FPGASLAVES_SPAN)
        {
            mem_region = FPGA_SLAVES_MEM_REGION;
            offset = address - FPGASLAVES;
        }
        else if (address > PERIPH && address < PERIPH + PERIPH_SPAN)
        {
            mem_region = PERIPH_MEM_REGION;
            offset = address - PERIPH;
        }
        else if (address > LWFPGASLAVES && address < LWFPGASLAVES + LWFPGASLAVES_SPAN)
        {
            mem_region = LW_FPGA_SLAVES_MEM_REGION;
            offset = address - LWFPGASLAVES;
        }

        std::optional<uint64_t> value =
            this->memory_manager_instance->read_from_register(static_cast<MEM_REGIONS>(mem_region), offset);

        uint64_t data = 0;
        if (value.has_value() == false)
        {
            data = 0;
        }
        else
            data = value.value();

        boost::asio::async_write(socket_, boost::asio::buffer(reinterpret_cast<char*>(&data), max_length),
                                 [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                     if (!ec)
                                     {
                                         do_read();
                                     }
                                 });
    }

    tcp::socket socket_;
    enum
    {
        max_length = 8
    };

    char data_[max_length];
    std::shared_ptr<memory_manager> memory_manager_instance;
};

class server
{
  public:
    server(boost::asio::io_context &io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), socket_(io_context)
    {
        do_accept();
    }

  private:
    void do_accept()
    {
        acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
            if (!ec)
            {
                std::make_shared<session>(std::move(socket_))->start();
            }

            do_accept();
        });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        server s(io_context, std::atoi(argv[1]));

        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}