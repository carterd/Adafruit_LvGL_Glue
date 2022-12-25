#include <Adafruit_LvGL_Glue.h>
#include <Adafruit_SH110X.h>

#if LV_COLOR_DEPTH == 16 || LV_COLOR_DEPTH == 8 
void displayCallback_SH110X(Adafruit_LvGL_Glue *glue, DISPLAY_TYPE *display, lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
#endif