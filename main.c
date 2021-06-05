#include <stdio.h>

#include "L9733.h"

int main() {
  // Initialize data structures
  spi_t spi = {};
  l9733_t sensor = {};
  sensor.bus = &spi;

  // Set OUT1 output "ON"
  sensor.output |= L9773_OUT1_BIT;
  (void)l9733_set_output(&sensor);
  // Set OUT1 output "OFF"
  sensor.output &= ~L9773_OUT1_BIT;
  (void)l9733_set_output(&sensor);

  // Set OUT1 diagnostic mode to "Latch Mode"
  sensor.diag_mode |= L9773_OUT1_BIT;
  (void)l9733_set_diag_mode(&sensor);
  // Set OUT1 diagnostic mode to "No Latch Mode"
  sensor.diag_mode &= ~L9773_OUT1_BIT;
  (void)l9733_set_diag_mode(&sensor);

  // Set OUT1 protection "ON"
  sensor.protection |= L9773_OUT1_BIT;
  (void)l9733_set_protection(&sensor);
  // Set OUT1 protection "OFF"
  sensor.protection &= ~L9773_OUT1_BIT;
  (void)l9733_set_protection(&sensor);

  (void)l9733_get_fault_diag(&sensor);
  if (L9773_SHORT_CIRCUIT == sensor.status[7]) {
    printf("Oh no! OUT8 is in short circuit!\n");
  }
  return 0;
}
