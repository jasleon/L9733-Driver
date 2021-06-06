#include <stdio.h>

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
  spi.rx_buf = 0x8001;
  (void)l9733_get_fault_diag(&sensor);
  if (L9733_SHORT_CIRCUIT == sensor.fault[7]) {
    printf("Oh no! OUT8 is in short circuit!\n");
  }
  return 0;
}
