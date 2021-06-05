# L9733-Driver
My interface for a driver of the L9733 integrated circuit

## Dependencies
I developed this project in Ubuntu. The following dependencies should be installed.
* cmake
* make
* gcc/g++

## Build Instructions
1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./driver`

## Introduction
This driver provides easy access to the core features of the L9733 device.

Here's a brief description of the integrated circuit taken from the datasheet

> The L9733 is a highly flexible output driver that incorporates 8 outputs that can be used as either internal low or high-side drives in any combination. The device has an 16 bit SPI input to command the 8 output drivers either "On" or "Off", reducing the I/O port requirement of the microcontroller. In addition the SPI output indicates latched fault conditions that may have occurred.
>

## Features
* Set outputs 1-8 ON or OFF
* Set the diagnostic mode on outputs 1-8 to "Latch Mode" or "No Latch Mode"
* Set the overcurrent protection on outputs 1-8 ON or OFF
* Get the fault diagnostic of outputs 1-8
* Get the thermal fault status

## Limitations
* The SPI object should be configured before calling the driver functions
* This driver does not support full-duplex SPI communication
* This driver should not be used in daisy-chained configurations

## SPI Configuration

- The datasheet does not define a maximum SPI rate. However, it should reach at least 5.4 MHz
- The Clock Polarity (CPOL) is 1
- The Clock Phase (CPHA) is 0
- Therefore, the SPI communication mode is 2 in the majority of microcontrollers
- The SPI transmit and receive buffers need to store at least 16 bits of data

## Example

This snippet shows how this driver should be used

```c
#include "L9733.h"

int main() {
  // Initialize data structures
  spi_t spi = {};
  l9733_t sensor = {};
  sensor.bus = &spi;

  // Set OUT1 output "ON"
  sensor.output |= L9733_OUT1_BIT;
  (void)l9733_set_output(&sensor);
  // Set OUT1 output "OFF"
  sensor.output &= ~L9733_OUT1_BIT;
  (void)l9733_set_output(&sensor);

  // Set OUT1 diagnostic mode to "Latch Mode"
  sensor.diag_mode |= L9733_OUT1_BIT;
  (void)l9733_set_diag_mode(&sensor);
  // Set OUT1 diagnostic mode to "No Latch Mode"
  sensor.diag_mode &= ~L9733_OUT1_BIT;
  (void)l9733_set_diag_mode(&sensor);

  // Set OUT1 protection "ON"
  sensor.protection |= L9733_OUT1_BIT;
  (void)l9733_set_protection(&sensor);
  // Set OUT1 protection "OFF"
  sensor.protection &= ~L9733_OUT1_BIT;
  (void)l9733_set_protection(&sensor);

  (void)l9733_get_fault_diag(&sensor);
  if (L9733_SHORT_CIRCUIT == sensor.fault[7]) {
    printf("Oh no! OUT8 is in short circuit!\n");
  }
  return 0;
}
```

## Tool Chain
* Visual Studio Code, code editing
* Git, version control
* GitHub, code hosting service
* CMake, build automation
* Doxygen, documentation generator
* Ubuntu, operating system

## References
* [L9733 Datasheet](https://www.st.com/resource/en/datasheet/l9733.pdf)