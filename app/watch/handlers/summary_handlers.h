#pragma once

#include <pebble.h>

#include "../constants/summary_constants.h"
#include "../windows/summary/summary_window.h"
#include "../util/strtok.h"

typedef void(SummaryMessageHandler)(Tuple *msg);

extern struct _SummaryHandlers {
  SummaryMessageHandler *handle_summary_message;
} SummaryHandlers;
