// Minimal "Hello" example for LittlevGL on Adafruit TFT FeatherWings.
// Requires LittlevGL, Adafruit_LvGL_Glue, Adafruit_STMPE610, Adafruit_GFX
// and Adafruit_ILI9341 (2.4" TFT) or Adafruit_HX8357 (3.5") libraries.
// This example doesn't use any touchscreen input, but it's declared anyway
// so this sketch can be copied-and-pasted to serve as a starting point for
// other projects. If display is scrambled, check that correct FeatherWing
// type is selected below (set BIG_FEATHERWING to 0 or 1 as needed).

// Prior Adafruit_LvGL_Glue users: see hello_changes example for updates!

#define BIG_FEATHERWING 0 // Set this to 1 for 3.5" (480x320) FeatherWing!
#define USE_ADAFRUIT_FONT 1 // Use adafruit converted font

#include <Adafruit_LvGL_Glue.h> // Always include this BEFORE lvgl.h!
#include <lvgl.h>
#include <Adafruit_SH110X.h>
#include <DisplayCallbacks/DisplayCallback_SH110X.h> // Display-specific callback

#if USE_ADAFRUIT_FONT
#include <Fonts/PixelOperator8pt7b.h>
#include <Utilities/Adafruit_To_LvGL_Font.h>
#endif

#ifdef ESP32
   #define TFT_CS   15
   #define TFT_DC   33
   #define STMPE_CS 32
#else
   #define TFT_CS    9
   #define TFT_DC   10
   #define STMPE_CS  6
#endif
#define TFT_ROTATION 1 // Landscape orientation on FeatherWing
#define TFT_RST     -1

#if BIG_FEATHERWING
  #include <Adafruit_HX8357.h>
  Adafruit_HX8357  tft(TFT_CS, TFT_DC, TFT_RST);
#else
  #include <Adafruit_ILI9341.h>
  #define TFT_WIDTH    64
  #define TFT_HEIGHT   128

  Adafruit_SH1107 tft(TFT_WIDTH, TFT_HEIGHT, &Wire, TFT_RST);
#endif

Adafruit_LvGL_Glue glue;

// This example sketch's LittlevGL UI-building calls are all in this
// function rather than in setup(), so simple programs can just 
// copy-and-paste this sketch as a starting point, then embellish here:
void lvgl_setup(void) {
#if USE_ADAFRUIT_FONT
  // Ensure that fonts are static otherwise, there will be problems
  static lv_font_t myAdaFont = {};
  adafruitToLvGLFont(&PixelOperator8pt7b, &myAdaFont);
  // Ensure using the mono theme
  lv_theme_t* mono_theme = lv_theme_mono_init(glue.getLvDisplay(), false, &myAdaFont);
#else
  lv_theme_t* mono_theme = lv_theme_mono_init(glue.getLvDisplay(), false, lv_font_default());
#endif
  lv_disp_set_rotation(NULL, LV_DISP_ROT_90);
  lv_disp_set_theme(NULL, mono_theme);

  // Create simple label centered on screen
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "Hello Arduino!");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void setup(void) {
  Serial.begin(115200);

  // Initialize display and touchscreen BEFORE glue setup
  tft.begin();
  // Use lv_disp_set_rotation to set rotation rather than tft.setRotation(TFT_ROTATION);

  // Initialize glue, passing in address of display & touchscreen
  LvGLStatus status = glue.begin(&tft, displayCallback_SH110X);
  if(status != LVGL_OK) {
    Serial.print("Glue error ");
    Serial.println((int)status);
    for(;;);
  }

  lvgl_setup(); // Call UI-building function above
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}
