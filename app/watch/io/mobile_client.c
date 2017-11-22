#include "mobile_client.h"

static bool mobile_ready;
static SummaryMessageHandler *summary_msg_handler;
static SessionsMessageHandler *sessions_msg_handler;

static void handle_received(DictionaryIterator *iter, void *ctx) {
  if (!mobile_ready) {
    Tuple *ready = dict_find(iter, MESSAGE_KEY_MobileReady);

    if (ready) {
      mobile_ready = true;
      APP_LOG(APP_LOG_LEVEL_INFO, "Client connected.");
    }
  } else {
    Tuple *summary_payload  = dict_find(iter, MESSAGE_KEY_Summary);
    Tuple *sessions_payload = dict_find(iter, MESSAGE_KEY_Sessions);

    if (summary_payload)  summary_msg_handler(summary_payload);
    if (sessions_payload) sessions_msg_handler(sessions_payload);
  }
}

static void request_summary(void) {
  DictionaryIterator *msg;

  AppMessageResult result = app_message_outbox_begin(&msg);

  if (result == APP_MSG_OK) {
    dict_write_cstring(msg, MESSAGE_KEY_Summary, NORMAL_SUMMARY);
  }

  result = app_message_outbox_send();
}

static void request_sessions(void) {
  DictionaryIterator *msg;

  AppMessageResult result = app_message_outbox_begin(&msg);

  if (result == APP_MSG_OK) {
    dict_write_cstring(msg, MESSAGE_KEY_Sessions, SESSIONS);
  }

  result = app_message_outbox_send();
}

static void init(struct MobileClientHandlers *handlers) {
  summary_msg_handler  = handlers->summary_msg_handler;
  sessions_msg_handler = handlers->sessions_msg_handler;

  app_message_register_inbox_received(handle_received);

  app_message_open(app_message_inbox_size_maximum(),
                   app_message_outbox_size_maximum());
}

struct _MobileClient MobileClient = {
  .init             = init,
  .request_summary  = request_summary,
  .request_sessions = request_sessions
};
