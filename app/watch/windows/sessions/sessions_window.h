#pragma once

#include <pebble.h>

#include "../../domain/session.h"

extern struct _SessionsWindow {
  void(*push)(struct Session *sessions, size_t sessions_count);
} SessionsWindow;
