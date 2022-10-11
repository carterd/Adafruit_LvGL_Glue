#if defined(ESP32)

//  tickerIncTimerPtr should be an instance of:
//
//  Ticker 
//

// This can be checked if the handler has had an issue with setting 
bool tickIncTimerError = false;

static void (*esp32_timer_handler_lv_tick_inc_fnc)(uint32_t tick_period) = NULL;
unsigned long esp32_timer_handler_lv_tick_interval_ms;

Ticker tick;

//
// Timer Callback
//

static void lv_tick_handler(void) { 
    esp32_timer_handler_lv_tick_inc_fnc(esp32_timer_handler_lv_tick_interval_ms); 
}

//
// startTickIncTimer
//

void* startTickIncTimer(void* gluePtr, const unsigned long lv_tick_interval_ms, void (*lv_tick_inc_fnc)(uint32_t tick_period)) {
    if (esp32_timer_handler_lv_tick_inc_fnc == NULL) {
        esp32_timer_handler_lv_tick_inc_fnc = lv_tick_inc_fnc;
        esp32_timer_handler_lv_tick_interval_ms = lv_tick_interval_ms
        tick.attach_ms(esp32_timer_handler_lv_tick_interval_ms, lv_tick_handler);
        status = LVGL_OK;
    }
}

bool endTickIncTimer(void* tickerIncTimerPtr) {
  // We could stop with stopTimer() but it's a global timer hence other instances of Glue could be using it
  return true;
}

//
// endTickIncTimer
//

#endif