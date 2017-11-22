#pragma once

#include <pebble.h>

#include "../constants/sessions_constants.h"
#include "../windows/sessions/sessions_window.h"

typedef void(SessionsMessageHandler)(Tuple *msg);

extern struct _SessionsHandlers {
  SessionsMessageHandler *handle_sessions_message;
} SessionsHandlers;
