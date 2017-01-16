#include "summary_window.h"

static Window         *window;
static StatusBarLayer *status_bar;

static TextLayer   *current_session;
static TextLayer   *current_classroom;
static TextLayer   *time_remaining;
static TextLayer   *next_summary;
static TextLayer   *sessions_summary;
static BitmapLayer *bear_image_layer;
static GBitmap     *bear_image;

static const bool animated = true;

static char* human_remaining_time(int minutes) {
  static char human_remaining_minutes_buffer[10];

  if (minutes > 60)
    snprintf(human_remaining_minutes_buffer, sizeof(human_remaining_minutes_buffer), "%d hrs", minutes/60);
  else
    snprintf(human_remaining_minutes_buffer, sizeof(human_remaining_minutes_buffer), "%d min", minutes);

  return human_remaining_minutes_buffer;
}

static void render_status_bar(Window *w) {
  status_bar = status_bar_layer_create();
  layer_add_child(window_get_root_layer(w),
                   status_bar_layer_get_layer(status_bar));
}

static void render_bear_image(Window *w) {
  bear_image       = gbitmap_create_with_resource(RESOURCE_ID_BEAR);
  bear_image_layer = bitmap_layer_create(GRect(38, 40, 72, 63));

  bitmap_layer_set_background_color(bear_image_layer, GColorClear);
  bitmap_layer_set_bitmap(bear_image_layer, bear_image);
  layer_add_child(window_get_root_layer(w),
                  bitmap_layer_get_layer(bear_image_layer));
}

static void render_session_name(Window *w) {
  current_session = text_layer_create(GRect(0, 100, 144, 24));
  text_layer_set_background_color(current_session, GColorClear);
  text_layer_set_text_color(current_session, GColorBlack);
  text_layer_set_text(current_session, "");

  text_layer_set_font(current_session, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(current_session, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(w), text_layer_get_layer(current_session));
}

static void render_current_classroom(Window *w) {
  current_classroom = text_layer_create(GRect(0, 120, 144, 18));
  text_layer_set_background_color(current_classroom, GColorClear);
  text_layer_set_text_color(current_classroom, GColorBlack);
  text_layer_set_text(current_classroom, VICTORY_EMOJI);

  text_layer_set_font(current_classroom, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  text_layer_set_text_alignment(current_classroom, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(w), text_layer_get_layer(current_classroom));
}

static void render_time_remaining(Window *w) {
  time_remaining = text_layer_create(GRect(0, 138, 144, 14));
  text_layer_set_background_color(time_remaining, GColorClear);
  text_layer_set_text_color(time_remaining, GColorBlack);
  text_layer_set_text(time_remaining, "");

  text_layer_set_font(time_remaining, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(time_remaining, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(w), text_layer_get_layer(time_remaining));
}

static void render_sessions_summary(Window *w) {
  sessions_summary = text_layer_create(GRect(15, 20, 144, 14));
  text_layer_set_background_color(sessions_summary, GColorClear);
  text_layer_set_text_color(sessions_summary, GColorBlack);
  text_layer_set_text(sessions_summary, "");

  text_layer_set_font(sessions_summary, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(window_get_root_layer(w), text_layer_get_layer(sessions_summary));
}

static void render_next_summary(Window *w) {
  next_summary = text_layer_create(GRect(80, 20, 144, 14));
  text_layer_set_background_color(next_summary, GColorClear);
  text_layer_set_text_color(next_summary, GColorBlack);
  text_layer_set_text(next_summary, "");

  text_layer_set_font(next_summary, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(window_get_root_layer(w), text_layer_get_layer(next_summary));
}

static void window_load(Window *w) {
  render_status_bar(w);
  render_sessions_summary(w);
  render_bear_image(w);
  render_session_name(w);
  render_current_classroom(w);
  render_time_remaining(w);
}

static void window_unload(Window *w) {
   status_bar_layer_destroy(status_bar);
   window_destroy(window);
}

static void update_remaining_time(int minutes) {
  text_layer_set_text(time_remaining, human_remaining_time(minutes));
}

static void update(char *sessions_summary_text,
                   int  remaining_minutes,
                   char *current_session_text,
                   char *current_classroom_text) {
  text_layer_set_text(current_session, current_session_text);
  text_layer_set_text(current_classroom, current_classroom_text);
  text_layer_set_text(current_classroom, current_classroom_text);
  update_remaining_time(remaining_minutes);
  text_layer_set_text(sessions_summary, sessions_summary_text);
}

static void push() {
  if (!window) {
    window = window_create();
    window_set_window_handlers(window, (WindowHandlers) {
      .load   = window_load,
      .unload = window_unload
    });
  }

  window_stack_push(window, animated);
}

struct _SummaryWindow SummaryWindow = {
  .push                  = push,
  .update                = update,
  .update_remaining_time = update_remaining_time
};
