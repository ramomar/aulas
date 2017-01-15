#include "mobile_client.h"

static bool mobile_ready;
static SummaryMessageHandler *summary_msg_handler;

static void handle_received(DictionaryIterator *iter, void *ctx) {
  if (!mobile_ready) {
    Tuple *ready = dict_find(iter, MESSAGE_KEY_MobileReady);

    if (ready) {
      mobile_ready = true;
      APP_LOG(APP_LOG_LEVEL_INFO, "Client connected.");
    }
  } else {
    Tuple *summary_payload = dict_find(iter, MESSAGE_KEY_Summary);

    if (summary_payload) summary_msg_handler(summary_payload);
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

static void init(SummaryMessageHandler *summary_msg_hl) {
  summary_msg_handler = summary_msg_hl;

  app_message_register_inbox_received(handle_received);

  app_message_open(app_message_inbox_size_maximum(),
                   app_message_outbox_size_maximum());
}

struct _MobileClient MobileClient = {
  .init            = init,
  .request_summary = request_summary
};
