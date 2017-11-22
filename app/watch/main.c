#include <pebble.h>

#include "windows/summary/summary_window.h"
#include "windows/sessions/sessions_window.h"
#include "handlers/summary_handlers.h"
#include "handlers/sessions_handlers.h"
#include "io/mobile_client.h"

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  if (SummaryWindow.minute_tick() == 0) {
    MobileClient.request_summary();
  }
}

static void down_click_handler(void *context) {
  MobileClient.request_sessions();
}

static void setup_mobile_client(void) {
  MobileClient.init(&(struct MobileClientHandlers) {
    .summary_msg_handler  = SummaryHandlers.handle_summary_message,
    .sessions_msg_handler = SessionsHandlers.handle_sessions_message
  });
}

static void setup_event_handlers(void) {
  window_set_click_config_provider(window_stack_get_top_window(), down_click_handler);
}

static void setup_service_subscriptions(void) {
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void init(void) {
  SummaryWindow.push();

  setup_mobile_client();
  setup_event_handlers();
  setup_service_subscriptions();
}

static void deinit(void) {
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_INFO, "Done initializing.");

  app_event_loop();

  deinit();
}
