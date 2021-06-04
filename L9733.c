#include "L9733.h"

#include <stdio.h>

fms_rslt_t l9733_set_output_status(l9733_t *obj) {
  uint16_t msg = obj->output;
  msg |= L9773_CMD_KEYWORD;
  msg |= L9773_CMD_WM_OUTPUT;
  printf("cmd: out, msg: 0x%04x\n", msg);
  return L9773_OK;
}

fms_rslt_t l9733_set_diag_mode(l9733_t *obj) {
  uint16_t msg = obj->diag_mode;
  msg |= L9773_CMD_KEYWORD;
  msg |= L9773_CMD_WM_DIAG;
  printf("cmd: dia, msg: 0x%04x\n", msg);
  return L9773_OK;
}

fms_rslt_t l9733_set_protection(l9733_t *obj) {
  uint16_t msg = obj->protection;
  msg |= L9773_CMD_KEYWORD;
  msg |= L9773_CMD_WM_PROTECT;
  printf("cmd: pro, msg: 0x%04x\n", msg);
  return L9773_OK;
}