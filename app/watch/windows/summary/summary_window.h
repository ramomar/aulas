#pragma once

#include <pebble.h>
#include "../../constants/summary_constants.h"

extern struct _SummaryWindow {
  void(*push)(void);
  void(*update)(char *sessions_summary_text,
                int  remaining_minutes,
                char *current_session_text,
                char *current_classroom_text);
  void(*update_remaining_time)(int minutes);
} SummaryWindow;
