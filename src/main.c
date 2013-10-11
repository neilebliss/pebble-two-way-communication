
#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x03, 0x7E, 0xE1, 0x06, 0x16, 0x01, 0x43, 0x39, 0x98, 0x52, 0x5E, 0xC4, 0x49, 0xB2, 0x68, 0xD3 }
PBL_APP_INFO_SIMPLE(MY_UUID, "2way comms", "Yoda dev", 1 /* App version */);


static struct YodaData
{
	Window window;
	TextLayer textLayer;
	AppSync sync;
	char *message;
} yoda_data;

// Modify these common button handlers

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

}


void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

}


void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  text_layer_set_text(&textLayer, "Select!");
}


void select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

}


// This usually won't need to be modified

void click_config_provider(ClickConfig **config, Window *window) {
  (void)window;

  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;

  config[BUTTON_ID_SELECT]->long_click.handler = (ClickHandler) select_long_click_handler;

  config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
  config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

  config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) down_single_click_handler;
  config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;
}


// Standard app initialisation

void handle_init(AppContextRef ctx) {
  (void)ctx;
  Window* window = &yoda_data.window;
  window_init(window, "2way comms");
  window_stack_push(&window, true /* Animated */);

	TextLayer* textLayer = &yoda_data.textLayer;
  text_layer_init(textLayer, window.layer.frame);
  text_layer_set_text(textLayer, "Press SELECT to update remote");
  text_layer_set_font(textLayer, fonts_get_system_font(FONT_KEY_GOTHAM_30_BLACK));
  layer_add_child(&window->layer, &textLayer->layer);

  // Attach our desired button functionality
  window_set_click_config_provider(window, (ClickConfigProvider) click_config_provider);
		
	Tuplet initial_values[] = {
		TupletCString(0x0, "Initial Message")
	}
	
	app_sync_init()

}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
	  .deinit_handler = &handle_deinit
  };
  app_event_loop(params, &handlers);
}
