#pragma once

#include <pebble.h>

extern struct _SummaryWindow {
  void(*push)(void);
  void(*update)(char *current_session_text,
                char *current_classroom_text,
                int  remaining_minutes,
                char *sessions_summary_text);
} SummaryWindow;
