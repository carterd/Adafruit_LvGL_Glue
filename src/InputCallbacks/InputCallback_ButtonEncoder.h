#ifndef _INPUTCALLBACK_BUTTONENCODER_H_
#define _INPUTCALLBACK_BUTTONENCODER_H_

#include <Adafruit_LvGL_Glue.h>

void inputCallback_ButtonEncoder(Adafruit_LvGL_Glue *glue,
                    INPUT_TYPE *input,
                    DISPLAY_TYPE *display,
                    struct _lv_indev_drv_t *indev_drv,
                    lv_indev_data_t *data);
                    
#endif