#include "summary_handlers.h"

static void handle_summary_message(Tuple *msg) {
  char separator[] = "|";
  char *token;

  APP_LOG(APP_LOG_LEVEL_INFO, msg->value->cstring);

  token = strtok(msg->value->cstring, separator);

  if (!strcmp(token, FREE_TIME)) {
    SummaryWindow.update(
      "",
      0,
      "",
      VICTORY_EMOJI
    );
  }
  else if (!strcmp(token, BREAK_TIME)) {
    SummaryWindow.update(
      strtok(NULL, separator),
      set_remaining_minutes(atoi(strtok(NULL, separator))),
      "",
      VICTORY_EMOJI
    );
  }
  else {
    SummaryWindow.update(
      strtok(NULL, separator),
      set_remaining_minutes(atoi(strtok(NULL, separator))),
      strtok(NULL, separator),
      strtok(NULL, separator)
    );
  }

  vibes_double_pulse();
}

struct _SummaryHandlers SummaryHandlers = {
  .handle_summary_message = handle_summary_message
};
