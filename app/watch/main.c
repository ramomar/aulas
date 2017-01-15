#include <pebble.h>

#include "io/mobile_client.h"

static void init() {
}

static void deinit() {
}

int main() {
  init();

  APP_LOG(APP_LOG_LEVEL_INFO, "Done initializing.");

  app_event_loop();

  deinit();
}
