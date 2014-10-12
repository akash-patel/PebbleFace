#include <pebble.h>

Window *g_window;
TextLayer *g_text_layer;
GBitmap *g_frame_bitmap;
BitmapLayer *g_frame_layer;


void window_load(Window *window){
    
    //Create and add the image
    
    g_frame_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FRAME);
    g_frame_layer = bitmap_layer_create(GRect(0, 0, 129, 60));
    bitmap_layer_set_bitmap(g_frame_layer, g_frame_bitmap);
    bitmap_layer_set_alignment(g_frame_layer, GAlignRight);
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(g_frame_layer));
    
    
    
    //We will add the creation of the window's elements here soon!
    g_text_layer = text_layer_create(GRect(0,59,144,50)); //0,59 <- top left corner, 144 is the width, 50 is the height
    text_layer_set_background_color(g_text_layer,GColorClear);
    text_layer_set_text_color(g_text_layer, GColorBlack);
    
    //improve the layour to be more like a watchface
    text_layer_set_font(g_text_layer,fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS));
    text_layer_set_text_alignment(g_text_layer, GTextAlignmentCenter);
    
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(g_text_layer));
    
    //text_layer_set_text(g_text_layer, "Doggy doggg");
    
    
}

void window_unload(Window *window){
    //we wills afely destroy the window's elements here!
    
    text_layer_destroy(g_text_layer);
    
    gbitmap_destroy(g_frame_bitmap);
    bitmap_layer_destroy(g_frame_layer);
    
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed){
    //allocate long-lived storage(required by TextLayer)
    static char buffer[]="00:00:00";
    
    //write the time to the buffer in a safe manner
    strftime(buffer,sizeof("00:00:00"),"%H:%M:%S",tick_time);
    
    //set the textlayer to display the buffer
    text_layer_set_text(g_text_layer,buffer);
}

void init()
  {
  //Create app elements here
    g_window = window_create();
    window_set_window_handlers(g_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
        
    });
    
    tick_timer_service_subscribe(SECOND_UNIT, (TickHandler)tick_handler);
    
    window_stack_push(g_window,true);
}

void deinit()
  {
  // Destroy app elements here
    window_destroy(g_window);
}

int main (void)
{
  init();
  app_event_loop();
  deinit();
}