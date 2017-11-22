#include "sessions_handlers.h"

#define SEPARATOR "|"

static char *status;

static char *read_token() {
  return strtok(NULL, SEPARATOR);
}

// TODO: Review how things will be de-allocated
static void handle_sessions_message(Tuple *msg) {
  APP_LOG(APP_LOG_LEVEL_INFO, msg->value->cstring);

  status = read_token();

  if (strcmp(status, SESSIONS)) {
    unsigned int sessions_count = atoi(strtok(msg->value->cstring, SEPARATOR));
    struct Session *sessions[] = malloc(sessions_count * sizeof(struct Session));

    for(unsigned int i=0; i<sessions_count; i++) {
      struct Session *session = (*sessions + i);

      session->name = read_token();
      session->time = read_token();

      *(sessions + i) = session;
    }
  }

  SessionsWindow.push(sessions, 0);
}

struct _SessionsHandlers SessionsHandlers = {
  .handle_sessions_message = handle_sessions_message
};