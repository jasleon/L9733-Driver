#include "L9733.h"

#include <stdio.h>

typedef enum {
  L9733_CMD_TYPE_OUTPUT,
  L9733_CMD_TYPE_DIAG_MODE,
  L9733_CMD_TYPE_PROTECT,
} l9733_cmd_type_t;

static fms_rslt_t l9733_set_cmd(l9733_t *obj, l9733_cmd_type_t cmd) {
  const char *strings[] = {
      "out",
      "dia",
      "pro",
  };
  uint16_t msg = 0U;
  msg |= L9733_CMD_KEYWORD;
  switch (cmd) {
    case L9733_CMD_TYPE_OUTPUT:
      msg |= L9733_CMD_WM_OUTPUT;
      msg |= obj->output;
      break;
    case L9733_CMD_TYPE_DIAG_MODE:
      msg |= L9733_CMD_WM_DIAG;
      msg |= obj->diag_mode;
      break;
    case L9733_CMD_TYPE_PROTECT:
      msg |= L9733_CMD_WM_PROTECT;
      msg |= obj->protection;
      break;
  }
  printf("cmd: %s, msg: 0x%04x\n", strings[cmd], msg);
  return FMS_RSLT_CMD_COMPLETE;
}

fms_rslt_t l9733_set_output(l9733_t *obj) {
  return l9733_set_cmd(obj, L9733_CMD_TYPE_OUTPUT);
}

fms_rslt_t l9733_set_diag_mode(l9733_t *obj) {
  return l9733_set_cmd(obj, L9733_CMD_TYPE_DIAG_MODE);
}

fms_rslt_t l9733_set_protection(l9733_t *obj) {
  return l9733_set_cmd(obj, L9733_CMD_TYPE_PROTECT);
}

fms_rslt_t l9733_get_fault_diag(l9733_t *obj) {
  const char *strings[] = {
      "L9733_OK",
      "L9733_OPEN_LOAD",
      "L9733_SHORT_CIRCUIT",
      "L9733_OVERCURRENT",
  };

  const uint16_t recv = 0x8001;
  for (uint16_t i = 0U; i < L9733_OUTPUT_NUM; ++i) {
    uint16_t status = recv >> (2 * i);
    status &= 0x0003;
    obj->fault[i] = status;
    printf("OUT%d: %s\n", i + 1, strings[obj->fault[i]]);
  }
  obj->thermal_fault = (0xFFFF == recv);
  printf("thermal_fault: %d\n", obj->thermal_fault);
  return FMS_RSLT_CMD_COMPLETE;
}