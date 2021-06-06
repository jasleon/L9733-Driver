/**
 * @mainpage My L9733 Driver
 * @section intro_section Introduction
 * - This driver provides easy access to the core features of the L9733 device.
 * - The L9733 is a highly flexible output driver that incorporates 8 outputs
 * that can be used as either internal low or high-side drives in any
 * combination.
 * - The device has an 16 bit SPI input to command the 8 output drivers either
 * "On" or "Off", reducing the I/O port requirement of the microcontroller.
 * - In addition the SPI output indicates latched fault conditions that may have
 * occurred.
 * @section feat_section Features
 * - Set outputs 1-8 ON or OFF
 * - Set the diagnostic mode on outputs 1-8 to "Latch Mode" or "No Latch Mode"
 * - Set the overcurrent protection on outputs 1-8 ON or OFF
 * - Get the fault diagnostic of outputs 1-8
 * - Get the thermal fault status
 * @section limit_section Limitations
 * - The SPI object should be configured before calling the driver functions
 * - This driver does not support daisy-chained configurations
 * @section cfg_section SPI Configuration
 * - The datasheet does not define a maximum SPI rate. However, it should reach
 * at least 5.4 MHz.
 * - The Clock Polarity (CPOL) is 1
 * - The Clock Phase (CPHA) is 0
 * - Therefore, the SPI communication mode is 2 in the majority of
 * microcontrollers.
 * - The SPI transmit and receive buffers need to store at least 16 bits of
 * data.
 * @section ref_section References
 * - <a href="https://www.st.com/resource/en/datasheet/l9733.pdf">L9733
 * Datasheet</a>
 */
/**
 * @file L9733.h
 * @brief Provides a high level interface for interacting with an L9733 device.
 * @author Antonio Sanchez
 * @date Jun 6, 2021
 */
#ifndef L9733_H_
#define L9733_H_

#include <stdbool.h>
#include <stdint.h>

#include "spi.h"

/*******************************************************************************
 * Simplifies integration with automated testing frameworks in C++ (i.e. gtest)
*******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/** Number of outputs available in the L9733 chip */
#define L9733_OUTPUT_NUM     (8)
/** Keyword used in the command register */
#define L9733_CMD_KEYWORD    (0b1010 << 12)
/** Nibble used to set the writing mode to output in the command register */
#define L9733_CMD_WM_OUTPUT  (0b1100 << 8)
/** Nibble used to set the writing mode to diagnostic in the command register */
#define L9733_CMD_WM_DIAG    (0b0011 << 8)
/** Nibble used to set the writing mode to protection in the command register */
#define L9733_CMD_WM_PROTECT (0b1010 << 8)

/** OUT1 bit in command register */
#define L9733_OUT1_BIT (1 << 0)
/** OUT2 bit in command register */
#define L9733_OUT2_BIT (1 << 1)
/** OUT3 bit in command register */
#define L9733_OUT3_BIT (1 << 2)
/** OUT4 bit in command register */
#define L9733_OUT4_BIT (1 << 3)
/** OUT5 bit in command register */
#define L9733_OUT5_BIT (1 << 4)
/** OUT6 bit in command register */
#define L9733_OUT6_BIT (1 << 5)
/** OUT7 bit in command register */
#define L9733_OUT7_BIT (1 << 6)
/** OUT8 bit in command register */
#define L9733_OUT8_BIT (1 << 7)

/** Types of results from the flight management system (FMS) */
typedef enum {
  FMS_RSLT_CMD_COMPLETE = 1,  //!< Command complete
  FMS_RSLT_CMD_FAILED = 2,    //!< Command failed
} fms_rslt_t;

/** Types of fault status from the L9733 chip */
typedef enum {
  L9733_OK = 0,             //!< No fault is present
  L9733_OPEN_LOAD = 1,      //!< Open load
  L9733_SHORT_CIRCUIT = 2,  //!< Short circuit to GND (low-side) or short
                            //!< circuit to Vbat (high-side)
  L9733_OVERCURRENT = 4,    //!< Overcurrent
} l9733_fault_status_t;

/** @brief L9733 Object */
typedef struct {
  spi_t *bus;          //!< The SPI object to use for interfacing with the chip
  uint8_t id;          //!< The L9733 ID number
  uint8_t output;      //!< The output status value
  uint8_t diag_mode;   //!< The diagnostic mode value
  uint8_t protection;  //!< The overcurrent protection value
  l9733_fault_status_t
      fault[L9733_OUTPUT_NUM];  //!< The fault status of outputs 1-8
  bool thermal_fault;  //!< This flag is set when a thermal fault occurs
} l9733_t;

/**
 * Set outputs 1-8 ON or OFF
 * @param[in] obj  The L9733 object to use for sending the command
 * @return The status of the request
 * @pre
 * - The SPI object should be configured before calling this function
 * @note
 * - Writes the values from the **output** data field in the L9733 object
 * - Updates the fault status in the L9733 object, if the SPI communication is
 * in full-duplex.
 */
fms_rslt_t l9733_set_output(l9733_t *obj);

/**
 * Set the diagnostic mode on outputs 1-8 to "Latch Mode" or "No Latch Mode"
 * @param[in] obj  The L9733 object to use for sending the command
 * @return The status of the request
 * @pre
 * - The SPI object should be configured before calling this function
 * @note
 * - Writes the values from the **diag_mode** data field in the L9733 object
 * - Set bit to 1 for "Latch Mode"
 * - Set bit to 0 for "No Latch Mode"
 * - Updates the fault status in the L9733 object, if the SPI communication is
 * in full-duplex.
 */
fms_rslt_t l9733_set_diag_mode(l9733_t *obj);

/**
 * Set the overcurrent protection on outputs 1-8 ON or OFF
 * @param[in] obj  The L9733 object to use for sending the command
 * @return The status of the request
 * @pre
 * - The SPI object should be configured before calling this function
 * @note
 * - Writes the values from the **protection** data field in the L9733 object
 * - Updates the fault status in the L9733 object, if the SPI communication is
 * in full-duplex.
 */
fms_rslt_t l9733_set_protection(l9733_t *obj);

/**
 * Get the fault diagnostic of outputs 1-8
 * @param[in] obj  The L9733 object to use for sending the command
 * @return The status of the request
 * @pre
 * - The SPI object should be configured before calling this function
 * @note
 * - Copies the status from the fault register to the **fault** array data field
 * - Sets the **thermal_fault** data field if a thermal fault occurred in at
 * least on one of the independent outputs
 */
fms_rslt_t l9733_get_fault_diag(l9733_t *obj);

/*******************************************************************************
 * Simplifies integration with automated testing frameworks in C++ (i.e. gtest)
*******************************************************************************/
#if defined(__cplusplus)
}
#endif

#endif  // L9733_H_