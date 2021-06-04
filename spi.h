/**
 * @file spi.h
 * @brief Provides a high level interface for interacting with the SPI.
 */
#ifndef SPI_H_
#define SPI_H_

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * Simplifies integration with automated testing frameworks in C++ (i.e. gtest)
 *******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief SPI object
 */
typedef struct {
  uint8_t active_ssel;
  uint8_t mode;
  uint8_t data_bits;
  bool msb_first;
  void *rx_buffer;
  uint32_t rx_buffer_size;
  const void *tx_buffer;
  uint32_t tx_buffer_size;
  bool is_async;
} spi_t;

/*******************************************************************************
 * Simplifies integration with automated testing frameworks in C++ (i.e. gtest)
 *******************************************************************************/
#if defined(__cplusplus)
}
#endif

#endif  // SPI_H_