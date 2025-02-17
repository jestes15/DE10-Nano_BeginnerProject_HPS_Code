#!/bin/bash

echo "All downloads are going to $PWD"
echo "" > downloads.txt

if ! test -f SoCEDSSetup-20.1.0.711-linux.run; then
	echo "Downloading SoC EDS 20.1"
	echo https://downloads.intel.com/akdlm/software/acdsinst/20.1std/711/ib_installers/SoCEDSSetup-20.1.0.711-linux.run >> downloads.txt
fi

if ! test -f arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu.tar.xz; then
	echo "Downloading Arm GNU Toolchain 14.2.rel1 (Aarch64)"
	echo https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu.tar.xz >> downloads.txt
fi

if ! test -f arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-linux-gnueabihf.tar.xz; then
	echo "Downloading Arm GNU Toolchain 14.2.rel1 (Aarch32)"
	echo https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-linux-gnueabihf.tar.xz >> downloads.txt
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
mkdir -p $HOME/intelFPGA/20.1/embedded/host_tools/arm_toolchains/Aarch32 $HOME/intelFPGA/20.1/embedded/host_tools/arm_toolchains/Aarch64
tar xf arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu.tar.xz
tar xf arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-linux-gnueabihf.tar.xz
cp -r arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu/* $HOME/intelFPGA/20.1/embedded/host_tools/arm_toolchains/Aarch64/
cp -r arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-linux-gnueabihf/* $HOME/intelFPGA/20.1/embedded/host_tools/arm_toolchains/Aarch32/

rm arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu.tar.xz arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-linux-gnueabihf.tar.xz
rm -rf arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-linux-gnueabihf

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
echo "export CROSS_COMPILE_AARCH32=$HOME/intelFPGA/20.1/embedded/host_tools/arm_toolchains/Aarch32/bin/arm-none-linux-gnueabihf-"  >> ~/.bash_aliases
echo "export CROSS_COMPILE_AARCH64=$HOME/intelFPGA/20.1/embedded/host_tools/arm_toolchains/Aarch64/bin/aarch64-none-linux-gnu-"  >> ~/.bash_aliases

export CROSS_COMPILE_AARCH32=$HOME/intelFPGA/20.1/embedded/host_tools/arm_toolchains/Aarch32/bin/arm-none-linux-gnueabihf-
export CROSS_COMPILE_AARCH64=$HOME/intelFPGA/20.1/embedded/host_tools/arm_toolchains/Aarch64/bin/aarch64-none-linux-gnu-

rm SoCEDSSetup-20.1.0.711-linux.run
rm QuartusLiteSetup-20.1.0.711-linux.run
rm Quartus-lite-18.1.0.625-linux.tar
rm -rf components readme.txt setup.sh