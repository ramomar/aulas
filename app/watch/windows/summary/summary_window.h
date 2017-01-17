#pragma once

#include <pebble.h>
#include "../../constants/summary_constants.h"

extern struct _SummaryWindow {
  void(*push)(void);

  void(*update)(char *sessions_ratio,
                char *session,
                char *classroom,
                int remaining_minutes);

  void(*session_time)(char *sessions_ratio,
                      char *current_session,
                      char *current_classroom,
                      int remaining_minutes);

  void(*break_time)(char *sessions_ratio,
                    char *next_session,
                    char *next_classroom,
                    int  remaining_minutes);

  void(*go_home_time)(char *sessions_ratio);

  void(*free_time)(void);

  void(*update_remaining_time)(int minutes);
} SummaryWindow;
