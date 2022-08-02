#include "InputCallback_ButtonEncoder.h"

static uint32_t lastKey = LV_KEY_ENTER;
static bool keyPressed = false;
#include <ButtonEncoder.h>

uint32_t last_key() {
    bool buttonPressedA = digitalRead(14) == LOW ? true : false;
    bool buttonPressedB = digitalRead(15) == LOW ? true : false;
    bool buttonPressedC = digitalRead(16) == LOW ? true : false;
    
    if (buttonPressedA && !buttonPressedB && !buttonPressedC) {
        lastKey = LV_KEY_LEFT;
        keyPressed = true;
    }
    else if (buttonPressedC && !buttonPressedA && !buttonPressedB) {
        lastKey = LV_KEY_RIGHT;
        keyPressed = true;        
    }
    else if (buttonPressedB && !buttonPressedA && !buttonPressedC) {
        lastKey = LV_KEY_ENTER;
        keyPressed = true;
    }
    else {
        keyPressed = false;
    }
    return lastKey;
}

void inputCallback_ButtonEncoder(Adafruit_LvGL_Glue *glue,
                    INPUT_TYPE *input,
                    DISPLAY_TYPE *display,
                    struct _lv_indev_drv_t *indev_drv,
                    lv_indev_data_t *data) {
    ButtonEncoder *inputButtonEncoder = (ButtonEncoder *) input;
    inputButtonEncoder->update();

    /*Get the last pressed or released key*/
    Encoder::EncoderKey lastKeyPressed = inputButtonEncoder->lastKeyPressed();
    uint32_t key = LV_KEY_ENTER;
    switch (lastKeyPressed) {
        case Encoder::EncoderKey::ENCODER_LEFT:
            key = LV_KEY_LEFT;
            break;
        case Encoder::EncoderKey::ENCODER_RIGHT:
            key = LV_KEY_RIGHT;
            break;
    }
    data->key = key;

    /* get state of the encoder */
    if(inputButtonEncoder->keyPressed()) {
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}
