# L9733-Driver
![build](https://github.com/jasleon/L9733-Driver/actions/workflows/main.yml/badge.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/jasleon/L9733-Driver)

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
* This driver does not support daisy-chained configurations

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
  // Create data structures
  spi_t spi = {};
  l9733_t sensor = {};
  
  // Initialize data structures
  spi.speed_hz = 5400000; // 5.4 MHz
  spi.mode = 2; // CPOL = 1; CPHA = 0
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

  // Consider this as an illustrative example:
  // - Mock a fault status response from the L9733 device
  spi.rx_buf = 0xE4E4;
  (void)l9733_get_fault_diag(&sensor);
  if (L9733_SHORT_CIRCUIT == sensor.fault[6]) {
    printf("Oh no! OUT7 is in short circuit!\n");
  }
  return 0;
}
```
Here is the output from the terminal
```
~/L9733-Driver/build$ ./driver 
cmd: out, msg: 0xac01
cmd: out, msg: 0xac00
cmd: dia, msg: 0xa301
cmd: dia, msg: 0xa300
cmd: pro, msg: 0xaa01
cmd: pro, msg: 0xaa00
OUT1: L9733_OK
OUT2: L9733_OPEN_LOAD
OUT3: L9733_SHORT_CIRCUIT
OUT4: L9733_OVERCURRENT
OUT5: L9733_OK
OUT6: L9733_OPEN_LOAD
OUT7: L9733_SHORT_CIRCUIT
OUT8: L9733_OVERCURRENT
thermal_fault: 0
Oh no! OUT7 is in short circuit!
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