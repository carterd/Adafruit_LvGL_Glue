#ifndef _ADAFRUIT_LVGL_TICKINC_H_
#define _ADAFRUIT_LVGL_TICKINC_H_

#include <Arduino.h>

//
// This is to completely seperate the code between the Adafruit LvGL glue object and the associated ticker implementations.
//

/**
 * @brief This is the initialise interface been archetecture specific tick inc timer implementations and the Adafruit glue common code
 *
 * @param gluePtr this is a pointer to the LvGL glue object instance, useful if the ticker is required to track multiple instance of lvgl glue
 * @param lv_tick_interval_ms this is the tick interval that needs to be implemented by the tick inc timer
 * @param lv_tick_inc_fnc this should always be the function pointer to the lv_tick_inc function to be called by the tick inc timer.
 * @return A pointer to some class or identifier for the tickTimer for tracking of dynamic creation and deletion of tick timer, or NULL if failure
 */
void* startTickIncTimer(void* gluePtr, const unsigned long lv_tick_interval_ms, void (*lv_tick_inc_fnc)(uint32_t tick_period));

/**
 * @brief This is the detroy interface been archetecture specific tick inc timer and the Adafruit glue common code.
 * 
 * @param tickerIncTimerPtr the pointer to some class or identifier for the tickTimer for tracking of dynamic creation and deletion of tick timer
 * @return true If the end function was a success
 * @return false If there was some issue in attempting the end function
 */
bool endTickIncTimer(void* tickerIncTimerPtr);

/**
 * @brief This boolean tracks if there has been an issue in the current implementation of any TickIncTimer(s)
 */
extern bool tickIncTimerError;

#endif