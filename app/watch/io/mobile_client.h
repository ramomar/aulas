#pragma once

#include <pebble.h>
#include "../constants/summary_constants.h"
#include "../constants/sessions_constants.h"
#include "../handlers/summary_handlers.h"
#include "../handlers/sessions_handlers.h"

struct MobileClientHandlers {
  SummaryMessageHandler  *summary_msg_handler;
  SessionsMessageHandler *sessions_msg_handler;
};

extern struct _MobileClient {
  void(*init)(struct MobileClientHandlers *handlers);
  void(*request_summary)(void);
  void(*request_sessions)(void);
} MobileClient;
