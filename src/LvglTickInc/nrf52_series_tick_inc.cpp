#if defined(NRF52_SERIES)

// Local to this file

static void (*nrf52_timer_handler_lv_tick_inc_fnc)(uint32_t tick_period) = NULL;
static unsigned long nrf52_timer_handler_lv_tick_interval_ms;

#define TIMER_ID NRF_TIMER4
#define TIMER_IRQN TIMER4_IRQn
#define TIMER_ISR TIMER4_IRQHandler
#define TIMER_FREQ 16000000

//
// Timer Callback
//

extern "C" {
// Timer interrupt service routine
void TIMER_ISR(void) {
  if (TIMER_ID->EVENTS_COMPARE[0]) {
    TIMER_ID->EVENTS_COMPARE[0] = 0;
  }
  nrf52_timer_handler_lv_tick_inc_fnc(nrf52_timer_handler_lv_tick_interval_ms);
}
}

//
// startTickIncTimer
//
void* startTickIncTimer(void* gluePtr, const unsigned long lv_tick_interval_ms, void (*lv_tick_inc_fnc)(uint32_t tick_period)) {
    if (nrf52_timer_handler_lv_tick_inc_fnc == NULL) {
        nrf52_timer_handler_lv_tick_inc_fnc = lv_tick_inc_fnc;
        nrf52_timer_handler_lv_tick_interval_ms = lv_tick_interval_ms

        TIMER_ID->TASKS_STOP = 1;               // Stop timer
        TIMER_ID->MODE = TIMER_MODE_MODE_Timer; // Not counter mode
        TIMER_ID->TASKS_CLEAR = 1;
        TIMER_ID->BITMODE = TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos;
        TIMER_ID->PRESCALER = 0; // 1:1 prescale (16 MHz)
        TIMER_ID->INTENSET = TIMER_INTENSET_COMPARE0_Enabled
                           << TIMER_INTENSET_COMPARE0_Pos; // Event 0 int
        TIMER_ID->CC[0] = TIMER_FREQ / (nrf52_timer_handler_lv_tick_interval_ms * 1000);

        NVIC_DisableIRQ(TIMER_IRQN);
        NVIC_ClearPendingIRQ(TIMER_IRQN);
        NVIC_SetPriority(TIMER_IRQN, 2); // Lower priority than soft device
        NVIC_EnableIRQ(TIMER_IRQN);

        TIMER_ID->TASKS_START = 1; // Start timer

    }
}

//
// endTickIncTimer
//

bool endTickIncTimer(void* tickerIncTimerPtr) {
  // We could stop with stopTimer() but it's a global timer hence other instances of Glue could be using it
  return true;
}

#endif