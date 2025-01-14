// Minimal "Hello" example for LittlevGL on TFT Gizmo display for Adafruit
// Circuit Playground Express or Circuit Playground Bluefruit. Requires
// LittlevGL, Adafruit_LvGL_Glue, Adafruit_GFX and Adafruit_ST7735 libraries.

// Prior Adafruit_LvGL_Glue users: see hello_changes example for updates!

#include <Adafruit_LvGL_Glue.h> // Always include this BEFORE lvgl.h!
#include <lvgl.h>
#include <Adafruit_ST7789.h>
#include <DisplayCallbacks/DisplayCallback_SPITFT.h> // Display-specific callback

#define TFT_ROTATION   2
#define TFT_CS        A6
#define TFT_DC        A7
#define TFT_RST       -1
#define TFT_BACKLIGHT A3
#if defined(NRF52_SERIES) // Circuit Playground Bluefruit
  #define TFT_SPI    SPI
#else                     // Circuit Playground Express
  // Please note this example NO LONGER FITS on Circuit Playground Express,
  // this is just for posterity in case something's worked out later.
  #define TFT_SPI   SPI1
#endif

Adafruit_ST7789    tft(&TFT_SPI, TFT_CS, TFT_DC, TFT_RST);
Adafruit_LvGL_Glue glue;

// This example sketch's LittlevGL UI-building calls are all in this
// function rather than in setup(), so simple programs can just 
// copy-and-paste this sketch as a starting point, then embellish here:
void lvgl_setup(void) {
  // Create simple label centered on screen
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "Hello Arduino!");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void setup(void) {
  Serial.begin(115200);

  // Initialize display BEFORE glue setup
  tft.init(240, 240);
  tft.setRotation(TFT_ROTATION);
  pinMode(TFT_BACKLIGHT, OUTPUT);
  analogWrite(TFT_BACKLIGHT, 255); // USE analogWrite() FOR GIZMO BACKLIGHT!

  // Initialize glue, passing in address of display
  LvGLStatus status = glue.begin(&tft, displayCallback_SPITFT);
  if(status != LVGL_OK) {
    Serial.printf("Glue error %d\r\n", (int)status);
    for(;;);
  }

  lvgl_setup(); // Call UI-building function above
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}
