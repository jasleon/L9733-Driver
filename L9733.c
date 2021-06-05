#include "L9733.h"

#include <stdio.h>

fms_rslt_t l9733_set_output(l9733_t *obj) {
  uint16_t msg = obj->output;
  msg |= L9773_CMD_KEYWORD;
  msg |= L9773_CMD_WM_OUTPUT;
  printf("cmd: out, msg: 0x%04x\n", msg);
  return FMS_RSLT_CMD_COMPLETE;
}

fms_rslt_t l9733_set_diag_mode(l9733_t *obj) {
  uint16_t msg = obj->diag_mode;
  msg |= L9773_CMD_KEYWORD;
  msg |= L9773_CMD_WM_DIAG;
  printf("cmd: dia, msg: 0x%04x\n", msg);
  return FMS_RSLT_CMD_COMPLETE;
}

fms_rslt_t l9733_set_protection(l9733_t *obj) {
  uint16_t msg = obj->protection;
  msg |= L9773_CMD_KEYWORD;
  msg |= L9773_CMD_WM_PROTECT;
  printf("cmd: pro, msg: 0x%04x\n", msg);
  return FMS_RSLT_CMD_COMPLETE;
}

fms_rslt_t l9733_get_fault_diag(l9733_t *obj) {
  const char *strings[] = {
      "L9773_OK",
      "L9773_OPEN_LOAD",
      "L9773_SHORT_CIRCUIT",
      "L9733_OVERCURRENT",
  };

  const uint16_t recv = 0x8001;
  for (uint16_t i = 0U; i < L9773_OUTPUT_NUM; ++i) {
    uint16_t status = recv >> (2 * i);
    status &= 0x0003;
    obj->status[i] = status;
    printf("OUT%d: %s\n", i + 1, strings[obj->status[i]]);
  }
  return FMS_RSLT_CMD_COMPLETE;
}