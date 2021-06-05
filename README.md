# L9733-Driver
My interface for a driver of the L9733 integrated circuit

## Dependencies
I developed this project in Ubuntu. The following dependencies should be installed.
* cmake
* make
* gcc/g++

## Build instructions
1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./driver`

## Introduction
This driver provides easy access to the core features of the L9773 device.

The L9733 is a highly flexible output driver that incorporates 8 outputs that can be used as either internal low or high-side drives in any combination. The device has an 16 bit SPI input to command the 8 output drivers either "On" or "Off", reducing the I/O port requirement of the microcontroller. In addition the SPI output indicates latched fault conditions that may have occurred.

## Features
* Set outputs 1-8 ON or OFF
* Set the diagnostic mode on outputs 1-8 to "Latch Mode" or "No Latch Mode"
* Set the overcurrent protection on outputs 1-8 ON or OFF
* Get the fault diagnostic of outputs 1-8
* Get the thermal fault status

## Limitations
* The SPI object should be configured before calling this function
* This driver should not be used in daisy-chained configurations

## Toolchain
* Visual Studio Code, code editing
* Git, version control
* GitHub, code hosting service
* CMake, build automation
* Doxygen, documentation generator
* Ubuntu, operating system

## References
* [L9773 Datasheet](https://www.st.com/resource/en/datasheet/l9733.pdf)