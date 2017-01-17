#include "summary_window.h"

#define ANIMATED          true

#define VICTORY_EMOJI     "\U0000270C" /*✌*/
#define BEER_EMOJI        "\U0001F37A"
#define PARTY_EMOJI       "\U0001F389"

static Window         *window;

static StatusBarLayer *status_bar_layer;

static BitmapLayer    *bear_image_layer;
static GBitmap        *bear_image;

static TextLayer      *sessions_ratio_layer;
static TextLayer      *session_layer;
static TextLayer      *classroom_layer;
static TextLayer      *remaining_time_layer;

static char* human_remaining_time(int minutes) {
  static char human_remaining_minutes_buffer[10];

  if (minutes > 60)
    snprintf(human_remaining_minutes_buffer, sizeof(human_remaining_minutes_buffer), "%d:%d", minutes/60, minutes%60);
  else
    snprintf(human_remaining_minutes_buffer, sizeof(human_remaining_minutes_buffer), "00:%d", minutes);

  return human_remaining_minutes_buffer;
}

static void update_sessions_ratio_layer(char *sessions_ratio) {
  text_layer_set_text(sessions_ratio_layer, sessions_ratio);
}

static void update_session_layer(char *session) {
  text_layer_set_text(session_layer, session);
}

static void update_classroom_layer(char *classroom) {
  text_layer_set_text(classroom_layer, classroom);
}

static void update_remaining_time_layer(int minutes) {
  text_layer_set_background_color(sessions_ratio_layer, GColorClear);
  text_layer_set_text_color(sessions_ratio_layer, GColorBlack);
  text_layer_set_text(remaining_time_layer, human_remaining_time(minutes));
}

static void update_remaining_time_layer_dont_display() {
  text_layer_set_background_color(remaining_time_layer, GColorClear);
  text_layer_set_text_color(remaining_time_layer, GColorBlack);
  text_layer_set_text(remaining_time_layer, "");
}

static void update_remaining_time_layer_break_time(int minutes) {
  text_layer_set_background_color(remaining_time_layer, GColorBlack);
  text_layer_set_text_color(remaining_time_layer, GColorClear);
  text_layer_set_text(remaining_time_layer, human_remaining_time(minutes));
}

static void render_bear_image_layer(Window *w) {
  bitmap_layer_set_background_color(bear_image_layer, GColorClear);
  bitmap_layer_set_bitmap(bear_image_layer, bear_image);
  layer_add_child(window_get_root_layer(w), bitmap_layer_get_layer(bear_image_layer));
}

static void render_status_bar_layer(Window *w) {
  status_bar_layer_set_separator_mode(status_bar_layer, StatusBarLayerSeparatorModeDotted);
  layer_add_child(window_get_root_layer(w), status_bar_layer_get_layer(status_bar_layer));
}

static void render_sessions_ratio_layer(Window *w) {
  text_layer_set_background_color(sessions_ratio_layer, GColorClear);
  text_layer_set_text_color(sessions_ratio_layer, GColorBlack);
  text_layer_set_text(sessions_ratio_layer, "");

  text_layer_set_font(sessions_ratio_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  layer_add_child(window_get_root_layer(w), text_layer_get_layer(sessions_ratio_layer));
}

static void render_session_layer(Window *w) {
  text_layer_set_background_color(session_layer, GColorClear);
  text_layer_set_text_color(session_layer, GColorBlack);
  text_layer_set_text(session_layer, "");

  text_layer_set_font(session_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(session_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(w), text_layer_get_layer(session_layer));
}

static void render_classroom_layer(Window *w) {
  text_layer_set_background_color(classroom_layer, GColorClear);
  text_layer_set_text_color(classroom_layer, GColorBlack);
  text_layer_set_text(classroom_layer, VICTORY_EMOJI);

  text_layer_set_font(classroom_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  text_layer_set_text_alignment(classroom_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(w), text_layer_get_layer(classroom_layer));
}

static void render_remaining_time_layer(Window *w) {
  text_layer_set_background_color(remaining_time_layer, GColorClear);
  text_layer_set_text_color(remaining_time_layer, GColorBlack);
  text_layer_set_text(remaining_time_layer, "");

  text_layer_set_font(remaining_time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
  text_layer_set_text_alignment(remaining_time_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(w), text_layer_get_layer(remaining_time_layer));
}

static void update(char *sessions_ratio,
                   char *session,
                   char *classroom,
                   int remaining_minutes) {
  update_sessions_ratio_layer(sessions_ratio);
  update_session_layer(session);
  update_classroom_layer(classroom);
  update_remaining_time_layer(remaining_minutes);
}

static void session_time(char *sessions_ratio,
                         char *session,
                         char *classroom,
                         int remaining_minutes) {
  update_sessions_ratio_layer(sessions_ratio);
  update_session_layer(session);
  update_classroom_layer(classroom);
  update_remaining_time_layer(remaining_minutes);
}

static void break_time(char *sessions_ratio,
                       char *next_session,
                       char *next_classroom,
                       int remaining_minutes) {
  update_sessions_ratio_layer(sessions_ratio);
  update_session_layer(next_session);
  update_classroom_layer(next_classroom);
  update_remaining_time_layer_break_time(remaining_minutes);
}

static void go_home_time(char *sessions_ratio) {
  update_sessions_ratio_layer(sessions_ratio);
  update_session_layer(PARTY_EMOJI);
  update_classroom_layer("Go home");
  update_remaining_time_layer_dont_display();
}

static void free_time() {
  update_sessions_ratio_layer("0/0");
  update_session_layer(BEER_EMOJI);
  update_classroom_layer("yeah");
  update_remaining_time_layer_dont_display();
}

static void window_load(Window *w) {
  bear_image           = gbitmap_create_with_resource(RESOURCE_ID_BEAR);
  bear_image_layer     = bitmap_layer_create(GRect(38, 40, 72, 63));
  status_bar_layer     = status_bar_layer_create();
  sessions_ratio_layer = text_layer_create(GRect(15, 20, 144, 14));
  session_layer        = text_layer_create(GRect(0, 100, 144, 24));
  classroom_layer      = text_layer_create(GRect(0, 120, 144, 18));
  remaining_time_layer = text_layer_create(GRect(0, 138, 144, 14));

  render_status_bar_layer(w);
  render_bear_image_layer(w);
  render_sessions_ratio_layer(w);
  render_session_layer(w);
  render_classroom_layer(w);
  render_remaining_time_layer(w);
}

static void window_unload(Window *w) {
   gbitmap_destroy(bear_image);
   bitmap_layer_destroy(bear_image_layer);
   status_bar_layer_destroy(status_bar_layer);
   text_layer_destroy(sessions_ratio_layer);
   text_layer_destroy(session_layer);
   text_layer_destroy(classroom_layer);
   text_layer_destroy(remaining_time_layer);
   window_destroy(window);
}

static void push() {
  if (!window) {
    window = window_create();
    window_set_window_handlers(window, (WindowHandlers) {
      .load   = window_load,
      .unload = window_unload
    });
  }

  window_stack_push(window, ANIMATED);
}

struct _SummaryWindow SummaryWindow = {
  .push                  = push,
  .update                = update,
  .session_time          = session_time,
  .break_time            = break_time,
  .go_home_time          = go_home_time,
  .free_time             = free_time,
  .update_remaining_time = update_remaining_time_layer
};
