#!/usr/bin/env bash
export DEVKITARM="/opt/devkitPro/devkitARM"
export APP_VERSION="v0.0.1"
if [[ "$1" == "-b" ]]; then
    make clean all
elif [[ "$1" == "-c" ]]; then
    make clean
elif [[ "$1" == "-d" ]]; then
    # I highly recommend adding 'set pagination off' to your ~/.gdbinit file to prevent gdb from pausing after every page
    echo "Asking how the meal is to $2..."
    "$DEVKITARM/bin/arm-none-eabi-gdb" ./build/out/Sulfur.elf -ex "set pagination off" -ex "target remote $2:4003" -ex "c"
elif [[ "$1" == "-i" ]]; then
    if [[ -f "./build/out/Sulfur.3dsx" ]]; then
        if [[ "$2" != "" ]]; then
            echo "Serving meal to $2..."
            3dslink ./build/out/Sulfur.3dsx -a $2
        else
            echo "Customer not found. (Specify the 3DS IP address)"
        fi
    fi
    if [[ ! -f "./build/out/Sulfur.3dsx" ]]; then
        echo "No meal found. Please cook the meal first. (Run ./build.sh -b)"
    fi
else
    echo "Usage: ./build.sh [-b] [-c] [-d xxx.xxx.xxx.xxx] [-i xxx.xxx.xxx.xxx]"
    echo "-b: Build the project"
    echo "-c: Clean the build files"
    echo "-d: Debug via gdb [Specify 3DS IP] (requires enabling debugging in Rosalina)"
    echo "-i: Run the project via 3dslink [Specify 3DS IP] (press Y in Homebrew Launcher before running)"
fi