#ifndef _ADAFRUIT_LVGL_GLUE_H_
#define _ADAFRUIT_LVGL_GLUE_H_

#define LVGL_DEBUG_VERSION_COMPATABILITY_UPTO_8_3_4  1
#define LVGL_DEBUG_VERSION_COMPATABILITY_ABOVE_8_3_4 0

class Adafruit_LvGL_Glue;

#include <lvgl.h>              // LittlevGL core lib
#include <Adafruit_GFX.h>
#if defined(ARDUINO_ARCH_SAMD)
#include <Adafruit_ZeroTimer.h> // SAMD-specific timer lib
#elif defined(ESP32)
#include <Ticker.h> // ESP32-specific timer lib
#elif defined(ARDUINO_ARCH_RP2040)
// Nothing here
#endif

class INPUT_TYPE;
class DISPLAY_TYPE;

typedef void (*InputCallback)(Adafruit_LvGL_Glue *glue,
                    INPUT_TYPE *input,
                    DISPLAY_TYPE *display,
                    lv_indev_drv_t *indev_drv,
                    lv_indev_data_t *data);

typedef void (*DisplayCallback)(Adafruit_LvGL_Glue *glue, 
                    DISPLAY_TYPE *display, 
                    lv_disp_drv_t *disp_drv, 
                    const lv_area_t *area, 
                    lv_color_t *color_p);

typedef enum {
  LVGL_OK,
  LVGL_ERR_ALLOC,
  LVGL_ERR_TIMER,
} LvGLStatus;

/**
 * @brief Class to act as a "glue" layer between the LvGL graphics library and
 * most of Adafruit's TFT displays
 *
 */
class Adafruit_LvGL_Glue {
public:
  Adafruit_LvGL_Glue(void);
  ~Adafruit_LvGL_Glue(void);
  // begin() funcs for Adafruit_GFX based displays
  LvGLStatus begin(Adafruit_GFX *display, DisplayCallback displayCallback, 
                  INPUT_TYPE *input, InputCallback inputCallback,
                  lv_indev_type_t inputDrvierType,
                  bool debug = false);
  LvGLStatus begin(Adafruit_GFX *display, DisplayCallback displayCallback, 
                  bool debug = false);
  // begin() funcs for generic displays
  LvGLStatus begin(DISPLAY_TYPE *display, DisplayCallback displayCallback, 
                  int16_t displayWidth, int16_t displayHeight,
                  INPUT_TYPE *input, InputCallback inputCallback,
                  lv_indev_type_t inputDrvierType,
                  bool debug = false);
  LvGLStatus begin(DISPLAY_TYPE *display, DisplayCallback displayCallback, 
                  bool debug = false);

  // Expose LV Display for ease of getting actual display rather than using NULL
  lv_disp_t *getLvDisplay();
  // Expose LV InputDev for ease of getting input device
  lv_indev_t *getLvInputDevice();

  // Expose the Callback functionality to the static C callback
  void displayCallback(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
  // Expose the Callback functioanlity to the static C callback
  void inputCallback(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
  // These items need to be public for some internal callbacks,
  // but should be avoided by user code please!
  DISPLAY_TYPE *display; ///< Pointer to the SPITFT display instance
  INPUT_TYPE *input;     ///< Pointer to the touchscreen object to use
  bool first_frame;      ///< Tracks if a call to `lv_flush_callback` needs to wait                     

private:
  static lv_disp_drv_t lv_disp_drv;
  static lv_disp_t *lv_disp;
  static lv_disp_draw_buf_t lv_disp_draw_buf;
  static lv_color_t *lv_pixel_buf;
  static lv_indev_drv_t lv_indev_drv;
  lv_indev_t *lv_input_dev_ptr;
  DisplayCallback displayCallbackFunc;
  InputCallback inputCallbackFunc;
  void *tickerIntTimer; ///< Archetecutre independant pointer to some kind of ticker timer implementation
};

#endif // _ADAFRUIT_LVGL_GLUE_H_
