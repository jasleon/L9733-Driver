/**
 * @file L9733.h
 * @brief Provides a high level interface for interacting with an L9733 device.
 */
#ifndef L9733_H_
#define L9733_H_

#include <stdint.h>

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