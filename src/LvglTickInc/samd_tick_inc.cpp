#if defined(ARDUINO_ARCH_SAMD)

//  tickerIncTimerPtr should be an instance of:
//
// Adafruit_ZeroTimer
//

// Local to this file

static void (*samd_timer_handler_lv_tick_inc_ptr)(uint32_t tick_period) = NULL;
static unsigned long samd_timer_handler_lv_tick_interval_ms;

// Because of the way timer/counters are paired, and because parallel TFT
// uses timer 2 for write strobe, this needs to use timer 4 or above...
#define TIMER_NUM 4
#define TIMER_ISR TC4_Handler

// Interrupt service routine for zerotimer object
void TIMER_ISR(void) { 
    Adafruit_ZeroTimer::timerHandler(TIMER_NUM); 
}

// Timer compare match 0 callback -- invokes LittlevGL timekeeper.
static void timerCallback0(void) { 
    samd_timer_handler_lv_tick_inc_ptr(samd_timer_handler_lv_tick_interval_ms); 
}

//
// startTickIncTimer
//

void* startTickIncTimer(void* gluePtr, const unsigned long lv_tick_interval_ms, void (*lv_tick_inc_ptr)(uint32_t tick_period)) {
  if (nrf52_timer_handler_lv_tick_inc_fnc == NULL) {
      nrf52_timer_handler_lv_tick_inc_fnc = lv_tick_inc_fnc;
      nrf52_timer_handler_lv_tick_interval_ms = lv_tick_interval_ms

    // status is still ERR_ALLOC until proven otherwise...
    if ((zerotimer = new Adafruit_ZeroTimer(TIMER_NUM))) {
      uint16_t divider = 1;
      uint16_t compare = 0;
      tc_clock_prescaler prescaler = TC_CLOCK_PRESCALER_DIV1;

      status = LVGL_OK; // We're prob good now, but one more test...

      int freq = 1000 / nrf52_timer_handler_lv_tick_interval_ms;

      if ((freq < (48000000 / 2)) && (freq > (48000000 / 65536))) {
        divider = 1;
        prescaler = TC_CLOCK_PRESCALER_DIV1;
      } else if (freq > (48000000 / 65536 / 2)) {
        divider = 2;
        prescaler = TC_CLOCK_PRESCALER_DIV2;
      } else if (freq > (48000000 / 65536 / 4)) {
        divider = 4;
        prescaler = TC_CLOCK_PRESCALER_DIV4;
      } else if (freq > (48000000 / 65536 / 8)) {
        divider = 8;
        prescaler = TC_CLOCK_PRESCALER_DIV8;
      } else if (freq > (48000000 / 65536 / 16)) {
        divider = 16;
        prescaler = TC_CLOCK_PRESCALER_DIV16;
      } else if (freq > (48000000 / 65536 / 64)) {
        divider = 64;
        prescaler = TC_CLOCK_PRESCALER_DIV64;
      } else if (freq > (48000000 / 65536 / 256)) {
        divider = 256;
        prescaler = TC_CLOCK_PRESCALER_DIV256;
      } else {
        status = LVGL_ERR_TIMER; // Invalid frequency
      }

      if (status == LVGL_OK) {
        compare = (48000000 / divider) / freq;
        // Initialize timer
        zerotimer->configure(prescaler, TC_COUNTER_SIZE_16BIT,
                             TC_WAVE_GENERATION_MATCH_PWM);
        zerotimer->setCompare(0, compare);
        zerotimer->setCallback(true, TC_CALLBACK_CC_CHANNEL0, timerCallback0);
        zerotimer->enable(true);
      }
      return zerotimer;
    }
  }
}

//
// endTickIncTimer
//

bool endTickIncTimer(void* tickerIncTimerPtr) {
  if (tickerIncTimerPtr) delete tickerIncTimerPtr;
  return true;
}



#endif