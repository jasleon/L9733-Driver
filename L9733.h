/**
 * @file L9733.h
 * @brief Provides a high level interface for interacting with an L9733 device.
 */
#ifndef L9733_H_
#define L9733_H_

#include <stdint.h>

#include "spi.h"

/** Number of outputs available in the L9773 chip */
#define L9773_OUTPUTS        (8)
/** Keyword used in the command register */
#define L9773_CMD_KEYWORD    (0b1010 << 12)
/** Nibble used to set the writing mode to output in the command register */
#define L9773_CMD_WM_OUTPUT  (0b1100 << 8)
/** Nibble used to set the writing mode to diagnostic in the command register */
#define L9773_CMD_WM_DIAG    (0b0011 << 8)
/** Nibble used to set the writing mode to protection in the command register */
#define L9773_CMD_WM_PROTECT (0b1010 << 8)

/** Position of OUT1 in command register */
#define L9773_OUT1 (1 << 0)
/** Position of OUT2 in command register */
#define L9773_OUT2 (1 << 1)
/** Position of OUT3 in command register */
#define L9773_OUT3 (1 << 2)
/** Position of OUT4 in command register */
#define L9773_OUT4 (1 << 3)
/** Position of OUT5 in command register */
#define L9773_OUT5 (1 << 4)
/** Position of OUT6 in command register */
#define L9773_OUT6 (1 << 5)
/** Position of OUT7 in command register */
#define L9773_OUT7 (1 << 6)
/** Position of OUT8 in command register */
#define L9773_OUT8 (1 << 7)

/** Types of results from the flight management system (FMS) */
typedef enum {
  FMS_RSLT_CMD_COMPLETE = 1,  //!< Command complete
  FMS_RSLT_CMD_FAILED = 2,    //!< Command failed
} fms_rslt_t;

/** Types of fault status from the L9773 chip */
typedef enum {
  L9773_OK = 0,             //!< No fault is present
  L9773_OPEN_LOAD = 1,      //!< Open load
  L9773_SHORT_CIRCUIT = 2,  //!< Short circuit to GND (low-side) or short
                            //!< circuit to Vbat (high-side)
  L9733_OVERCURRENT = 4,    //!< Overcurrent
} l9733_fault_status_t;

/** @brief L9773 Object */
typedef struct {
  spi_t *bus;          //!< The SPI object to use for interfacing with the chip
  uint8_t id;          //!< The L9773 ID number
  uint8_t output;      //!< The output status value
  uint8_t diag_mode;   //!< The diagnostic mode value
  uint8_t protection;  //!< The overcurrent protection value
  l9733_fault_status_t
      status[L9773_OUTPUTS];  //!< The fault status of outputs 1-8
} l9733_t;

/**
 * Set outputs 1-8 ON or OFF
 * @param[in] obj  The L9773 object to use for sending the command
 * @note
 * - Writes the values from the output data field in the L9773 object
 * @return The status of the request
*/
fms_rslt_t l9733_set_output_status(l9733_t *obj);

/**
 * Set the diagnostic mode on outputs 1-8 to "Latch Mode" or "No Latch Mode"
 * @param[in] obj  The L9773 object to use for sending the command
 * @note
 * - Writes the values from the diag_mode data field in the L9773 object
 * - Set bit to 1 for "Latch Mode"
 * - Set bit to 0 for "No Latch Mode"
 * @return The status of the request
*/
fms_rslt_t l9733_set_diag_mode(l9733_t *obj);

/**
 * Set the overcurrent protection on outputs 1-8 ON or OFF
 * @param[in] obj  The L9773 object to use for sending the command
 * @note
 * - Writes the values from the protection data field in the L9773 object
 * @return The status of the request
*/
fms_rslt_t l9733_set_protection(l9733_t *obj);

/**
 * Get the fault diagnostic of outputs 1-8
 * @param[in] obj  The L9773 object to use for sending the command
 * @note
 * - Copies the status from the fault register to the status data field
 * @return The status of the request
*/
fms_rslt_t l9733_get_fault_diag(l9733_t *obj);

#endif  // L9733_H_