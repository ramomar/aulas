#include "sessions_window.h"

#define ANIMATED true
#define SECTIONS 1

static Window            *window;
static SimpleMenuLayer   *sessions_layer;
static size_t            sessions_count;
static struct Session    *sessions;
static SimpleMenuItem    *items;
static SimpleMenuSection sections[SECTIONS];

static void render_sessions_layer(Window *w) {
  items = malloc(sessions_count * sizeof(SimpleMenuItem));

  struct Session *session = sessions;
  SimpleMenuItem *item    = malloc(sizeof(SimpleMenuItem));

  for (size_t i=0; i<sessions_count; i++) {
    item->title    = session->name;
    item->subtitle = session->time;

    memcpy(items+i, item, sizeof(SimpleMenuItem));
    session++;
  }

  sections[0] = (SimpleMenuSection) {
   .num_items = SECTIONS,
   .items     = items
  };

  Layer *window_layer = window_get_root_layer(w);
  GRect bounds        = layer_get_frame(window_layer);
  sessions_layer      = simple_menu_layer_create(bounds, w, sections, SECTIONS, NULL);
  layer_add_child(window_layer, simple_menu_layer_get_layer(sessions_layer));
  free(item);
}

static void window_load(Window *w) {
  render_sessions_layer(w);
}

static void window_unload(Window *w) {
   free(sessions); // TODO: this should be refactored
   free(items);
   simple_menu_layer_destroy(sessions_layer);
   window_destroy(window);
}

static void push(struct Session *sessions, size_t sessions_count) {
  if (!window) {

    window = window_create();
    window_set_window_handlers(window, (WindowHandlers) {
      .load   = window_load,
      .unload = window_unload
    });
  }

  sessions       = sessions;
  sessions_count = sessions_count;

  window_stack_push(window, ANIMATED);
}

struct _SessionsWindow SessionsWindow = {
  .push = push
};
