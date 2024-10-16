#!/bin/bash

echo "All downloads are going to $PWD"
echo "" > downloads.txt

if ! test -f SoCEDSSetup-20.1.0.711-linux.run; then
	echo "Downloading SoC EDS 20.1"
	echo https://downloads.intel.com/akdlm/software/acdsinst/20.1std/711/ib_installers/SoCEDSSetup-20.1.0.711-linux.run >> downloads.txt
fi

if ! test -f gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf.tar.xz; then
	echo "Downloading Arm GNU Toolchain 10.3-2021.07"
	echo https://developer.arm.com/-/media/Files/downloads/gnu-a/10.3-2021.07/binrel/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf.tar.xz >> downloads.txt
fi

if ! test -f QuartusLiteSetup-20.1.0.711-linux.run; then
	echo "Downloading Quartus Prime 20.1"
	echo https://downloads.intel.com/akdlm/software/acdsinst/20.1std/711/ib_installers/QuartusLiteSetup-20.1.0.711-linux.run >> downloads.txt
fi

if ! test -f Quartus-lite-18.1.0.625-linux.tar; then
	echo "Downloading Quartus Prime 18.1"
	echo https://downloads.intel.com/akdlm/software/acdsinst/18.1std/625/ib_tar/Quartus-lite-18.1.0.625-linux.tar >> downloads.txt
fi

wget -i downloads.txt

chmod +x SoCEDSSetup-20.1.0.711-linux.run
chmod +x QuartusLiteSetup-20.1.0.711-linux.run

tar -xf Quartus-lite-18.1.0.625-linux.tar

echo "Installing SoC EDS and Quartus"
./SoCEDSSetup-20.1.0.711-linux.run --disable-components qprogrammer --installdir $HOME/intelFPGA/20.1 --accept_eula 1 --mode unattended
./QuartusLiteSetup-20.1.0.711-linux.run --installdir $HOME/intelFPGA/20.1 --accept_eula 1 --mode unattended
./setup.sh --installdir $HOME/intelFPGA/18.1 --accept_eula 1 --mode unattended

echo "Installing Arm GNU Toolchain"
mkdir -p $HOME/intelFPGA/20.1/embedded/host_tools/linaro/gcc
tar xf gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf.tar.xz
cp -r gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/* $HOME/intelFPGA/20.1/embedded/host_tools/linaro/gcc/


touch ~/.bash_aliases
echo "export PATH=$HOME/intelFPGA/18.1/quartus/bin:\$PATH" >> ~/.bash_aliases
echo "export PATH=$HOME/intelFPGA/20.1/embedded:\$PATH" >> ~/.bash_aliases

export PATH=$HOME/intelFPGA/18.1/quartus/bin:$PATH
export PATH=$HOME/intelFPGA/20.1/embedded:$PATH

echo "# DE10-Nano working directory" >> ~/.bash_aliases
echo "export DEWD=$HOME/de10nano_wd"  >> ~/.bash_aliases

export DEWD=$HOME/de10nano_wd
mkdir -p $DEWD

echo "# Cross compiler for DE10-Nano." >> ~/.bash_aliases
echo "export CROSS_COMPILE=$HOME/intelFPGA/20.1/embedded/host_tools/linaro/gcc/bin/arm-none-linux-gnueabihf-"  >> ~/.bash_aliases

export CROSS_COMPILE=$HOME/intelFPGA/20.1/embedded/host_tools/linaro/gcc/bin/arm-none-linux-gnueabihf-

rm SoCEDSSetup-20.1.0.711-linux.run
rm QuartusLiteSetup-20.1.0.711-linux.run
rm Quartus-lite-18.1.0.625-linux.tar
rm gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf.tar.xz
rm -rf gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf

rm -rf components readme.txt setup.sh