#pragma once

#include <pebble.h>
#include "../constants/summary_constants.h"
#include "../handlers/summary_handlers.h"

extern struct _MobileClient {
  void(*init)(SummaryMessageHandler *summary_msg_handler);
  void(*request_summary)(void);
} MobileClient;
