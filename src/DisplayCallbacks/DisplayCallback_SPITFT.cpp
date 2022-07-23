#include "DisplayCallback_SPITFT.h"

void displayCallback_SPITFT(Adafruit_LvGL_Glue *glue, DISPLAY_TYPE *display, lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
  // Get pointer to glue object from indev user data
  Adafruit_SPITFT *adaDisplay = (Adafruit_SPITFT *) display;

  if (!glue->first_frame) {
    adaDisplay->dmaWait();  // Wait for prior DMA transfer to complete
    adaDisplay->endWrite(); // End transaction from any prior call
  } else {
    glue->first_frame = false;
  }

  uint16_t width = (area->x2 - area->x1 + 1);
  uint16_t height = (area->y2 - area->y1 + 1);
  adaDisplay->startWrite();
  adaDisplay->setAddrWindow(area->x1, area->y1, width, height);
  adaDisplay->writePixels((uint16_t *)color_p, width * height, false,
                       LV_COLOR_16_SWAP);
  lv_disp_flush_ready(disp_drv);
}