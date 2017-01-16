#include <pebble.h>

#include "global/counter.h"
#include "windows/summary/summary_window.h"
#include "handlers/summary_handlers.h"
#include "io/mobile_client.h"

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  SummaryWindow.update_remaining_time(remaining_minutes_tick());
  if (remaining_minutes() == 0) {
    MobileClient.request_summary();
  }
}

static void init() {
  SummaryWindow.push();
  MobileClient.init(SummaryHandlers.handle_summary_message);
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
}

int main() {
  init();

  APP_LOG(APP_LOG_LEVEL_INFO, "Done initializing.");

  app_event_loop();

  deinit();
}
