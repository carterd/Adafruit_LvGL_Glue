#include "InputCallback_TouchScreen.h"
#include <TouchScreen.h>

// TOUCHSCREEN STUFF -------------------------------------------------------

// STMPE610 calibration for raw touch data
#define TS_MINX 100
#define TS_MAXX 3800
#define TS_MINY 100
#define TS_MAXY 3750

// Same, for ADC touchscreen
#define ADC_XMIN 325
#define ADC_XMAX 750
#define ADC_YMIN 240
#define ADC_YMAX 840

#define INPUT_TYPE TouchScreen

void inputCallback_TouchScreen(Adafruit_LvGL_Glue *glue,
                    INPUT_TYPE *input,
                    DISPLAY_TYPE *display,
                    struct _lv_indev_drv_t *indev_drv,
                    lv_indev_data_t *data)
{
    boolean is_adc_touch = true;

    static lv_coord_t last_x = 0, last_y = 0;
    static uint8_t release_count = 0;

    Adafruit_GFX *adaDisplay = (Adafruit_GFX*) display;

    INPUT_TYPE *touch = input;
    TSPoint p = touch->getPoint();
    // Serial.printf("%d %d %d\r\n", p.x, p.y, p.z);
    // Having an issue with spurious z=0 results from TouchScreen lib.
    // Since touch is polled periodically, workaround is to watch for
    // several successive z=0 results, and only then regard it as
    // a release event (otherwise still touched).
    if (p.z < touch->pressureThreshhold)
    { // A zero-ish value
        release_count += (release_count < 255);
        if (release_count >= 4)
        {
            data->state = LV_INDEV_STATE_REL; // Is REALLY RELEASED
        }
        else
        {
            data->state = LV_INDEV_STATE_PR; // Is STILL PRESSED
        }
    }
    else
    {
        release_count = 0;               // Reset release counter
        data->state = LV_INDEV_STATE_PR; // Is PRESSED
        switch (adaDisplay->getRotation())
        {
        case 0:
            last_x = map(p.x, ADC_XMIN, ADC_XMAX, 0, adaDisplay->width() - 1);
            last_y = map(p.y, ADC_YMAX, ADC_YMIN, 0, adaDisplay->height() - 1);
            break;
        case 1:
            last_x = map(p.y, ADC_YMAX, ADC_YMIN, 0, adaDisplay->width() - 1);
            last_y = map(p.x, ADC_XMAX, ADC_XMIN, 0, adaDisplay->height() - 1);
            break;
        case 2:
            last_x = map(p.x, ADC_XMAX, ADC_XMIN, 0, adaDisplay->width() - 1);
            last_y = map(p.y, ADC_YMIN, ADC_YMAX, 0, adaDisplay->height() - 1);
            break;
        case 3:
            last_x = map(p.y, ADC_YMIN, ADC_YMAX, 0, adaDisplay->width() - 1);
            last_y = map(p.x, ADC_XMIN, ADC_XMAX, 0, adaDisplay->height() - 1);
            break;
        }
    }
    data->point.x = last_x; // Last-pressed coordinates
    data->point.y = last_y;
    //return false; // No buffering of ADC touch data
}