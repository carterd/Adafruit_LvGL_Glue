#if defined(ARDUINO_ARCH_RP2040)

#include "../Adafruit_LvGL_Tick_Inc.h"
#include <MBED_RPi_Pico_TimerInterrupt.h>

#define TIMER_NUM TIMER_IRQ_0

//
// Globally exposed
//

// This can be checked if the handler has had an issue with setting 
bool tickIncTimerError = false;

// Local to this file

static void (*pico_timer_handler_lv_tick_inc_fnc)(uint32_t tick_period) = NULL;
static unsigned long pico_timer_handler_lv_tick_interval_ms;
// Init MBED_RPI_PICO_Timer
static MBED_RPI_PICO_Timer ITimer(0);

// Modified TIMER_ISR_START function
bool TIMER_ISR_START_ENHANCED(uint alarm_num)
{  
  absAlarmTime[alarm_num]._private_us_since_boot = time_us_64() + _timerCount[alarm_num];                
  return hardware_alarm_set_target(alarm_num, absAlarmTime[alarm_num]);
}

// Timer interrupt service routine
void PIC_TIMER_HANDLER(uint alarm_num)
{ 
  ///////////////////////////////////////////////////////////
  // Always call this for MBED RP2040 before processing ISR
  if (TIMER_ISR_START_ENHANCED(alarm_num)) { tickIncTimerError = true; }
  ///////////////////////////////////////////////////////////

  // Flag for checking to be sure ISR is working as Serial.print is not OK here in ISR
  pico_timer_handler_lv_tick_inc_fnc(pico_timer_handler_lv_tick_interval_ms);

  ////////////////////////////////////////////////////////////
  // Always call this for MBED RP2040 after processing ISR
  TIMER_ISR_END(alarm_num);
  ////////////////////////////////////////////////////////////
}

void* startTickIncTimer(void* gluePtr, const unsigned long lv_tick_interval_ms, void (*lv_tick_inc_fnc)(uint32_t tick_period))
{ 
  // Currently we use a global timer and hence don't track gluePtr

  // Allow the pic_timer to be defined just the once
  if (pico_timer_handler_lv_tick_inc_fnc == NULL) {
    pico_timer_handler_lv_tick_inc_fnc = lv_tick_inc_fnc;
    pico_timer_handler_lv_tick_interval_ms = lv_tick_interval_ms;
    if (!ITimer.attachInterruptInterval(lv_tick_interval_ms * 1000, PIC_TIMER_HANDLER)) {
      // Just return the instance of the ITimer we're using
      return NULL;
    }
  }
  return &ITimer;
}  

bool endTickIncTimer(void* tickerIncTimerPtr) {
  // We could stop with stopTimer() but it's a global timer hence other instances of Glue could be using it
  return true;
}

#endif