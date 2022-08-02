#include "Adafruit_LvGL_Glue.h"
#include <lvgl.h>

lv_disp_draw_buf_t Adafruit_LvGL_Glue::lv_disp_draw_buf;
lv_disp_drv_t Adafruit_LvGL_Glue::lv_disp_drv;
lv_color_t *Adafruit_LvGL_Glue::lv_pixel_buf;
lv_indev_drv_t Adafruit_LvGL_Glue::lv_indev_drv;
lv_disp_t *Adafruit_LvGL_Glue::lv_disp;

// ARCHITECTURE-SPECIFIC TIMER STUFF ---------------------------------------

// Tick interval for LittlevGL internal timekeeping; 1 to 10 ms recommended
static const int lv_tick_interval_ms = 10;

#if defined(ARDUINO_ARCH_SAMD) // --------------------------------------

// Because of the way timer/counters are paired, and because parallel TFT
// uses timer 2 for write strobe, this needs to use timer 4 or above...
#define TIMER_NUM 4
#define TIMER_ISR TC4_Handler

// Interrupt service routine for zerotimer object
void TIMER_ISR(void) { Adafruit_ZeroTimer::timerHandler(TIMER_NUM); }

// Timer compare match 0 callback -- invokes LittlevGL timekeeper.
static void timerCallback0(void) { lv_tick_inc(lv_tick_interval_ms); }

#elif defined(ESP32) // ------------------------------------------------

static void lv_tick_handler(void) { lv_tick_inc(lv_tick_interval_ms); }

#elif defined(NRF52_SERIES) // -----------------------------------------

#define TIMER_ID NRF_TIMER4
#define TIMER_IRQN TIMER4_IRQn
#define TIMER_ISR TIMER4_IRQHandler
#define TIMER_FREQ 16000000

extern "C" {
// Timer interrupt service routine
void TIMER_ISR(void) {
  if (TIMER_ID->EVENTS_COMPARE[0]) {
    TIMER_ID->EVENTS_COMPARE[0] = 0;
  }
  lv_tick_inc(lv_tick_interval_ms);
}
}

#elif defined(ARDUINO_ARCH_RP2040)

#include <MBED_RPi_Pico_TimerInterrupt.h>
#define TIMER_NUM TIMER_IRQ_3

// Timer interrupt service routine
void PIC_TIMER_HANDLER(uint alarm_num)
{ 
  // Always call this for MBED RP2040 before processing ISR
  TIMER_ISR_START(alarm_num);

  // Flag for checking to be sure ISR is working as Serial.print is not OK here in ISR
  lv_tick_inc(lv_tick_interval_ms);

  // Always call this for MBED RP2040 after processing ISR
  TIMER_ISR_END(alarm_num);
}
#endif

// INPUT STUFF -------------------------------------------------------------

static void lv_read_callback(lv_indev_drv_t *indev_drv,
                             lv_indev_data_t *data) {

  // Get pointer to glue object from indev user data
  Adafruit_LvGL_Glue *glue = (Adafruit_LvGL_Glue *)indev_drv->user_data;
  DISPLAY_TYPE *display = glue->display;
  INPUT_TYPE *input = glue->input;
  glue->inputCallback(indev_drv, data);
}

// OTHER LITTLEVGL VITALS --------------------------------------------------

#if LV_COLOR_DEPTH != 16
#pragma error("LV_COLOR_DEPTH must be 16")
#endif
// This isn't necessarily true, don't mention it for now. See notes later.
//#if LV_COLOR_16_SWAP != 0
//  #pragma message("Set LV_COLOR_16_SWAP to 0 for best display performance")
//#endif

// Actual RAM usage will be 2X these figures, since using 2 DMA buffers...
#ifdef _SAMD21_
#define LV_BUFFER_ROWS 4 // Don't hog all the RAM on SAMD21
#else
#define LV_BUFFER_ROWS 8 // Most others have a bit more space
#endif

// This is the flush function required for LittlevGL screen updates.
// It receives a bounding rect and an array of pixel data (conveniently
// already in 565 format, so the Earth was lucky there).
static void lv_flush_callback(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                              lv_color_t *color_p) {

  // Get pointer to glue object from indev user data
  Adafruit_LvGL_Glue *glue = (Adafruit_LvGL_Glue *)disp_drv->user_data;
  Adafruit_GFX *display = (Adafruit_GFX *) glue->display;

  glue->displayCallback(disp_drv, area, color_p);
}

#if (LV_USE_LOG)
// Optional LittlevGL debug print function, writes to Serial if debug is
// enabled when calling glue begin() function.
static void lv_debug(const char *buf) { Serial.println(buf); }
#endif

// GLUE LIB FUNCTIONS ------------------------------------------------------

// Constructor
/**
 * @brief Construct a new Adafruit_LvGL_Glue::Adafruit_LvGL_Glue object,
 * initializing minimal variables
 *
 */
Adafruit_LvGL_Glue::Adafruit_LvGL_Glue(void)
    : first_frame(true) , displayCallbackFunc(NULL), inputCallbackFunc(NULL) {
#if defined(ARDUINO_ARCH_SAMD)
  zerotimer = NULL;
#elif defined(ARDUINO_ARCH_RP2040)
  picoTimer = NULL;
#endif
}

// Destructor
/**
 * @brief Destroy the Adafruit_LvGL_Glue::Adafruit_LvGL_Glue object, freeing any
 * memory previously allocated within this library.
 *
 */
Adafruit_LvGL_Glue::~Adafruit_LvGL_Glue(void) {
  delete[] lv_pixel_buf;
#if defined(ARDUINO_ARCH_SAMD)
  delete zerotimer;
#elif defined(ARDUINO_ARCH_RP2040)
  delete picoTimer;
#endif
  // Probably other stuff that could be deallocated here
}

// begin() function is overloaded for STMPE610 touch, ADC touch, or none.

// Pass in POINTERS to ALREADY INITIALIZED display & touch objects (user code
// should have previously called corresponding begin() functions and checked
// return states before invoking this),
// they are NOT initialized here. Debug arg is
// touch arg can be NULL (or left off) if using LittlevGL as a passive widget
// display.

/**
 * @brief Configure the glue layer and the underlying LvGL code to use the given
 * TFT display driver instance and touchscreen controller
 *
 * @param display Pointer to an **already initialized** display object instance
 * @param displayCallback Pointer to the display callback function
 * @param debug Debug flag to enable debug messages. Only used if LV_USE_LOG is
 * configured in LittleLVGL's lv_conf.h
 * @return LvGLStatus The status of the initialization:
 * * LVGL_OK : Success
 * * LVGL_ERR_TIMER : Failure to set up timers
 * * LVGL_ERR_ALLOC : Failure to allocate memory
 */
LvGLStatus Adafruit_LvGL_Glue::begin(Adafruit_GFX *display, DisplayCallback displayCallback, bool debug) {
  return begin(display, displayCallback, (INPUT_TYPE *)NULL, (InputCallback) NULL, LV_INDEV_TYPE_NONE, debug);
}
/**
 * @brief Configure the glue layer and the underlying LvGL code to use the given
 * TFT display driver instance and touchscreen controller
 *
 * @param display Pointer to an **already initialized** display object instance
 * @param displayCallback Pointer to the display callback function
 * @param input Pointer to an **already initialized** input object instance
 * @param inputCallback Pointer to the input callback function
 * @param inputDriverType The type of input device
 * @param debug Debug flag to enable debug messages. Only used if LV_USE_LOG is
 * configured in LittleLVGL's lv_conf.h
 * @return LvGLStatus The status of the initialization:
 * * LVGL_OK : Success
 * * LVGL_ERR_TIMER : Failure to set up timers
 * * LVGL_ERR_ALLOC : Failure to allocate memory
 */
LvGLStatus Adafruit_LvGL_Glue::begin(Adafruit_GFX *display, DisplayCallback displayCallback, 
                                     INPUT_TYPE *input, InputCallback inputCallback,
                                     lv_indev_type_t inputDriverType,
                                     bool debug) {
  return begin((DISPLAY_TYPE*) display, displayCallback, display->width(), display->height(), input, inputCallback, inputDriverType, debug);
}
/**
 * @brief Configure the glue layer and the underlying LvGL code to use the given
 * TFT display driver and touchscreen controller instances
 *
 * @param display Pointer to an **already initialized** display object instance
 * @param displayCallback Pointer to the display callback function
 * @param displayWidth The width of the display in number of pixels
 * @param displayHeight The height of the display in number of pixels
 * @param input Pointer to an **already initialized** input object instance
 * @param inputCallback Pointer to the input callback function
 * @param inputDriverType The type of input device
 * @param debug Debug flag to enable debug messages. Only used if LV_USE_LOG is
 * configured in LittleLVGL's lv_conf.h
 * @return LvGLStatus The status of the initialization:
 * * LVGL_OK : Success
 * * LVGL_ERR_TIMER : Failure to set up timers
 * * LVGL_ERR_ALLOC : Failure to allocate memory
 */
LvGLStatus Adafruit_LvGL_Glue::begin(DISPLAY_TYPE *display, DisplayCallback displayCallback, 
                                     int16_t displayWidth, int16_t displayHeight,
                                     INPUT_TYPE *input, InputCallback inputCallback,
                                     lv_indev_type_t inputDrvierType,
                                     bool debug) {
  this->displayCallbackFunc = displayCallback;
  this->inputCallbackFunc = inputCallback;
  lv_init();
#if (LV_USE_LOG)
  if (debug) {
    lv_log_register_print_cb(lv_debug); // Register debug print function
  }
#endif

  // Allocate LvGL display buffer (x2 because DMA double buffering)
  LvGLStatus status = LVGL_ERR_ALLOC;
#if defined(USE_SPI_DMA)
  if ((lv_pixel_buf = new lv_color_t[displayWidth * LV_BUFFER_ROWS * 2])) {
#else
  if ((lv_pixel_buf = new lv_color_t[displayWidth * LV_BUFFER_ROWS])) {
#endif

    this->display = display;
    this->input = input;

    // Initialize LvGL display buffers. The "second half" buffer is only
    // used if USE_SPI_DMA is enabled in Adafruit_GFX.
    lv_disp_draw_buf_init(&lv_disp_draw_buf, lv_pixel_buf,
#if defined(USE_SPI_DMA)
                          &lv_pixel_buf[displayWidth * LV_BUFFER_ROWS],
#else
                          NULL, // No double-buffering
#endif
                          displayWidth * LV_BUFFER_ROWS);

    // Initialize LvGL display driver
    lv_disp_drv_init(&lv_disp_drv);
#if defined(ARDUINO_NRF52840_CLUE) || defined(ARDUINO_NRF52840_CIRCUITPLAY) || \
    defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
    // ST7789 library (used by CLUE and TFT Gizmo for Circuit Playground
    // Express/Bluefruit) is sort of low-level rigged to a 240x320
    // screen, so this needs to work around that manually...
    lv_disp_drv.hor_res = 240;
    lv_disp_drv.ver_res = 240;
#else
    lv_disp_drv.hor_res = displayWidth;
    lv_disp_drv.ver_res = displayHeight;
#endif
    lv_disp_drv.flush_cb = lv_flush_callback;
    lv_disp_drv.draw_buf = &lv_disp_draw_buf;
    lv_disp_drv.user_data = this;
    lv_disp = lv_disp_drv_register(&lv_disp_drv);

    // Initialize LvGL input device (touchscreen already started)
    if ((input)) { // Can also pass NULL if passive widget display
      lv_indev_drv_init(&lv_indev_drv);          // Basic init
      lv_indev_drv.type = inputDrvierType;       // Set the input type
      lv_indev_drv.read_cb = lv_read_callback;   // Read callback
      lv_indev_drv.user_data = this;
      lv_input_dev_ptr = lv_indev_drv_register(&lv_indev_drv);
    }

    // TIMER SETUP is architecture-specific ----------------------------

#if defined(ARDUINO_ARCH_RP2040)
    if ((picoTimer = new MBED_RPI_PICO_Timer(TIMER_NUM))) {
      if (((MBED_RPI_PICO_Timer*) picoTimer)->attachInterruptInterval(lv_tick_interval_ms * 1000, PIC_TIMER_HANDLER))
      {
        status = LVGL_OK;
      }
    }
#elif defined(ARDUINO_ARCH_SAMD) // --------------------------------------

    // status is still ERR_ALLOC until proven otherwise...
    if ((zerotimer = new Adafruit_ZeroTimer(TIMER_NUM))) {
      uint16_t divider = 1;
      uint16_t compare = 0;
      tc_clock_prescaler prescaler = TC_CLOCK_PRESCALER_DIV1;

      status = LVGL_OK; // We're prob good now, but one more test...

      int freq = 1000 / lv_tick_interval_ms;

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
    }

#elif defined(ESP32) // ------------------------------------------------

    tick.attach_ms(lv_tick_interval_ms, lv_tick_handler);
    status = LVGL_OK;

#elif defined(NRF52_SERIES) // -----------------------------------------

  TIMER_ID->TASKS_STOP = 1;               // Stop timer
  TIMER_ID->MODE = TIMER_MODE_MODE_Timer; // Not counter mode
  TIMER_ID->TASKS_CLEAR = 1;
  TIMER_ID->BITMODE = TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos;
  TIMER_ID->PRESCALER = 0; // 1:1 prescale (16 MHz)
  TIMER_ID->INTENSET = TIMER_INTENSET_COMPARE0_Enabled
                       << TIMER_INTENSET_COMPARE0_Pos; // Event 0 int
  TIMER_ID->CC[0] = TIMER_FREQ / (lv_tick_interval_ms * 1000);

  NVIC_DisableIRQ(TIMER_IRQN);
  NVIC_ClearPendingIRQ(TIMER_IRQN);
  NVIC_SetPriority(TIMER_IRQN, 2); // Lower priority than soft device
  NVIC_EnableIRQ(TIMER_IRQN);

  TIMER_ID->TASKS_START = 1; // Start timer

  status = LVGL_OK;

#endif // end timer setup --------------------------------------------------
  }

  if (status != LVGL_OK) {
    delete[] lv_pixel_buf;
    lv_pixel_buf = NULL;
#if defined(ARDUINO_ARCH_RP2040)
    delete picoTimer;
    picoTimer = NULL;
#elif defined(ARDUINO_ARCH_SAMD)
    delete zerotimer;
    zerotimer = NULL;
#endif
  }

  return status;
}
/**
 * @brief Provides a callback to the registered external displayCallbackFunc
 * 
 * @param disp_drv This is the lv_disp_drv_t display driver structure
 * @param area The area for the display callback
 * @param color_p Pointer to the color pixel array for transferring to the display
 */
void Adafruit_LvGL_Glue::displayCallback(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
  if (this->displayCallbackFunc != NULL) {
    this->displayCallbackFunc(this, this->display, disp_drv, area, color_p);
  }
}

/**
 * @brief Provides a callback to the registered external inputCallback
 * 
 * @param indev_drv This is the input device driver structure
 * @param data Pointer to the data for processing the input device
 */
void Adafruit_LvGL_Glue::inputCallback(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
  if (this->inputCallbackFunc != NULL) {
    this->inputCallbackFunc(this, this->input, this->display, indev_drv, data);
  }
}

lv_disp_t *Adafruit_LvGL_Glue::getLvDisplay() {
  return this->lv_disp;
}

lv_indev_t *Adafruit_LvGL_Glue::getLvInputDevice() {
  return this->lv_input_dev_ptr;
}