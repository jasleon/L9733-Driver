/**
 * @file L9733.h
 * @brief Provides a high level interface for interacting with an L9733 device.
 */
#ifndef L9733_H_
#define L9733_H_

#include <stdint.h>

/** Keyword used in the command register */
#define L9773_CMD_KEYWORD    (0b1010 << 12)
/** Nibble used to set the writing mode to output in the command register */
#define L9773_CMD_WM_OUTPUT  (0b1100 << 8)
/** Nibble used to set the writing mode to diagnostic in the command register */
#define L9773_CMD_WM_DIAG    (0b0011 << 8)
/** Nibble used to set the writing mode to protection in the command register */
#define L9773_CMD_WM_PROTECT (0b1010 << 8)

/** Position of OUT1 in command register */
#define L9773_DAT_OUT1 (1 << 0)
/** Position of OUT2 in command register */
#define L9773_DAT_OUT2 (1 << 1)
/** Position of OUT3 in command register */
#define L9773_DAT_OUT3 (1 << 2)
/** Position of OUT4 in command register */
#define L9773_DAT_OUT4 (1 << 3)
/** Position of OUT5 in command register */
#define L9773_DAT_OUT5 (1 << 4)
/** Position of OUT6 in command register */
#define L9773_DAT_OUT6 (1 << 5)
/** Position of OUT7 in command register */
#define L9773_DAT_OUT7 (1 << 6)
/** Position of OUT8 in command register */
#define L9773_DAT_OUT8 (1 << 7)

/** Types of results from the flight management system (FMS) */
typedef enum {
  FMS_RSLT_CMD_COMPLETE = 0x01,  //!< Command complete
  FMS_RSLT_CMD_FAILED   = 0x02,  //!< Command failed
  FMS_RSLT_CMD_TIMEOUT  = 0x03,  //!< Command timeout
} fms_rslt_t;

fms_rslt_t l9733_set_output_status(void);

fms_rslt_t l9733_set_diag_mode(void);

fms_rslt_t l9733_set_overcurrent_protection(void);

#endif  // L9733_H_