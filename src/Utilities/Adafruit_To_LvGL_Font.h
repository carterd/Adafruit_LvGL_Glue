#ifndef _ADAFRUIT_TO_LVGL_FONT_H_
#define _ADAFRUIT_TO_LVGL_FONT_H_

#include <lvgl.h>
#include <Adafruit_GFX.h>

bool adafruitToLvGLFont(const GFXfont *adafruitFont, lv_font_t *lvFont, const lv_font_t *lvFontFallback = NULL);

#endif