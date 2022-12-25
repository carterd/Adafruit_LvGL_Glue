#include <Adafruit_LvGL_Glue.h>
#include "DisplayCallback_SH110X.h"


void displayCallback_SH110X(Adafruit_LvGL_Glue *glue, DISPLAY_TYPE *display, lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
  Adafruit_SH110X *adaDisplay = (Adafruit_SH110X *) display;

  if (!glue->first_frame) {
    // display->dmaWait();  // Wait for prior DMA transfer to complete
    adaDisplay->endWrite(); // End transaction from any prior call
  } else {
    glue->first_frame = false;
  }

  uint16_t width = (area->x2 - area->x1 + 1);
  uint16_t height = (area->y2 - area->y1 + 1);


  adaDisplay->startWrite();
  adaDisplay->setRotation(disp_drv->rotated);
  for (int y = area->y1; y <= area->y2 ; y++ ) {    
    for (int x = area->x1; x <= area->x2 ; x++) {
      lv_color_t color_t = *color_p;
#if LV_COLOR_DEPTH == 16
      int mono_color = (color_t.ch.blue + (color_t.ch.green >> 1) + color_t.ch.red > 48 ? 1 : 0 );
#else
      int mono_color = ((color_t.ch.blue << 1) + color_t.ch.green + color_t.ch.red > 12 ? 1 : 0 );
#endif
      adaDisplay->writePixel(x, y, mono_color);
      color_p++;
    }
  }

  if (lv_disp_flush_is_last(disp_drv)) {
    adaDisplay->display();
  }

  lv_disp_flush_ready(disp_drv);
}

