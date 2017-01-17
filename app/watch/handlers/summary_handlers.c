#include "summary_handlers.h"

#define SEPARATOR "|"

static char *tokens[9];

static enum _TokenMappings {
  status_token                         = 0,
  sessions_ratio_token                 = 1,
  remaining_minutes_token              = 2,
  session_token                        = 3,
  classroom_token                      = 4,
  next_status_token                    = 5,
  next_session_token                   = 6,
  next_classroom_token                 = 7,
  next_session_remaining_minutes_token = 8
} TokenMappings;

static void reset_tokens() {
  for (unsigned int i=0; i<(sizeof(tokens)/sizeof(tokens[0])); i++) {
    tokens[i] = NULL;
  }
}

static char *read_token() {
  return strtok(NULL, SEPARATOR);
}

static void handle_summary_message(Tuple *msg) {
  APP_LOG(APP_LOG_LEVEL_INFO, msg->value->cstring);
  reset_tokens();

  tokens[status_token] = strtok(msg->value->cstring, SEPARATOR);

  if (!strcmp(tokens[status_token], FREE_TIME)) {
    SummaryWindow.free_time();
  }
  else if (!strcmp(tokens[status_token], BREAK_TIME)) {
    tokens[sessions_ratio_token]                 = read_token();
    tokens[next_session_remaining_minutes_token] = read_token();
    tokens[next_session_token]                   = read_token();
    tokens[next_classroom_token]                 = read_token();

    SummaryWindow.break_time(tokens[sessions_ratio_token],
                             tokens[next_session_token],
                             tokens[next_classroom_token],
                             atoi(tokens[next_session_remaining_minutes_token]));
  }
  else if (!strcmp(tokens[status_token], GO_HOME_TIME)) {
    tokens[sessions_ratio_token] = strtok(NULL, SEPARATOR);
    SummaryWindow.go_home_time(tokens[sessions_ratio_token]);
  }
  else {
    tokens[sessions_ratio_token]    = read_token();
    tokens[remaining_minutes_token] = read_token();
    tokens[session_token]           = read_token();
    tokens[classroom_token]         = read_token();

    SummaryWindow.session_time(tokens[sessions_ratio_token],
                               tokens[session_token],
                               tokens[classroom_token],
                               atoi(tokens[remaining_minutes_token]));
  }

  vibes_double_pulse();
}

struct _SummaryHandlers SummaryHandlers = {
  .handle_summary_message = handle_summary_message
};
