/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 ******************************************************************************/

#include "lv_font_symbols_8.h"

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap_symbols_8[] = {
//    /* U+0020 " " */
//
//    /* U+0021 "!" */
//    0x58, 0x57, 0x46, 0x23, 0x46,
//
//    /* U+007E "~" */
//    0x29, 0x35, 0x15, 0x6, 0x80,

    /* U+00B0 "°" */
    0b01101001, 0b10010110,

    /* U+2022 "•" */
    0b01101111, 0b11110110,

    /* U+F001 "" LV_SYMBOL_AUDIO */
    0b00000000, 0b00000111, 0b00111111, 0b00111111, 0b00110001, 0b00100001, 0b00100111, 0b11100110, 0b11000000,

    /* U+F008 "" */
    0b10100010, 0b11111111, 0b11101000, 0b10111100, 0b01111011, 0b11101111, 0b00011110, 0b10001011, 0b11111111, 0b10100010, 0b10000000,

    /* U+F00B "" */
    0b11011111, 0b11011111, 0b00000000, 0b11011111, 0b11011111, 0b00000000, 0b11011111, 0b11011111,

    /* U+F00C "" */
    0b00000001, 0b00000011, 0b10000110, 0b11001100, 0b01111000, 0b00110000,

    /* U+F00D "" */
    0b10000011, 0b10001101, 0b10110001, 0b11000011, 0b10001101, 0b10110001, 0b11000001,    

    /* U+F011 "" */
    0b00011000, 0b01011010, 0b11011011, 0b10011001, 0b10000001, 0b11000011, 0b01100110, 0b00111100,

    /* U+F013 "" */
    0b00011000, 0b01111110, 0b11111111, 0b11100111, 0b01100110, 0b11111111, 0b01111110, 0b00011000,

    /* U+F015 "" */
    0b00001001, 0b00001110, 0b10001101, 0b11001101, 0b01101101, 0b11011101, 0b11110100, 0b11011000, 0b01101100,

    /* U+F019 "" */
    0b00011000, 0b00011000, 0b00011000, 0b01111110, 0b00111100, 0b00011000, 0b11100111, 0b11111111,

    /* U+F01C "" */
    0b00111110, 0b00100000, 0b10100000, 0b00111100, 0b01111111, 0b11111111, 0b11111100,

    /* U+F021 "" */
    0b00111000, 0b01000101, 0b10000011, 0b00000111, 0b11100000, 0b11000001, 0b10100010, 0b00011100,

    /* U+F026 "" */
    0b00010011, 0b11111111, 0b11111111, 0b00110001,

    /* U+F027 "" */
    0b00010000, 0b11001111, 0b00111101, 0b11110111, 0b11000011, 0b00000100,

    /* U+F028 "" */
    0b00010000, 0b00110010, 0b11110001, 0b11110101, 0b11110101, 0b11110001, 0b00110010, 0b00010000,

    /* U+F03E "" */
    0b11111111, 0b11011110, 0b11111110, 0b00111010, 0b00011000, 0b00001100, 0b00000111, 0b11111110,
    
    /* U+F043 "" */
    0b00100000, 0b11000111, 0b00011110, 0b11111110, 0b11111101, 0b11011110,

    /* U+F048 "" */
    0b10001100, 0b11101111, 0b11111111, 0b11011110, 0b01110001,

    /* U+F04B "" */
    0b00000001, 0b10000011, 0b11000111, 0b11101111, 0b11111111, 0b11111111, 0b01111000, 0b11000000, 0b00000000,

    /* U+F04C "" */
    0b11101111, 0b11011111, 0b10111111, 0b01111110, 0b11111101, 0b11111011, 0b11110111,

    /* U+F04D "" */
    0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,

    /* U+F051 "" */
    0b10001110, 0b01111011, 0b11111111, 0b11110111, 0b00110001,

    /* U+F052 "" */
    0b00001000, 0b00001110, 0b00001111, 0b10001111, 0b11100111, 0b11110000, 0b00000001, 0b11111100, 0b11111110,

    /* U+F053 "" */
    0b00011001, 0b10011001, 0b10000110, 0b00011000, 0b01100000,

    /* U+F054 "" */
    0b11000011, 0b00001100, 0b00110011, 0b00110011, 0b00000000,

    /* U+F067 "" */
    0b00000000, 0b00110000, 0b01100011, 0b11110111, 0b11100011, 0b00000110, 0b00000000,

    /* U+F068 "" */
    0b11111111, 0b11111100,

    /* U+F06E "" */
    0b00011110, 0b00011011, 0b01101101, 0b01101111, 0b01111011, 0b01101101, 0b10000111, 0b10000000,

    /* U+F070 "" */
    0b01100000, 0b00000110, 0b11100001, 0b01101011, 0b01100110, 0b10111101, 0b01100110, 0b11010110, 0b10000111, 0b01100000, 0b00000110,

    /* U+F071 "" */
    0b00000100, 0b00000001, 0b11000000, 0b00111000, 0b00001101, 0b10000001, 0b10110000, 0b01111111, 0b00011110, 0b11110011, 0b11111110,

    /* U+F074 "" */
    0b00000010, 0b11000111, 0b00101010, 0b00011000, 0b00110010, 0b11001111, 0b00000010, 0b00000000,
    
     /* U+F077 "" */
    0b00000000, 0b00100000, 0b11100011, 0b01101100, 0b01100000, 0b00000000,
    
      /* U+F078 "" */
    0b00000001, 0b10001101, 0b10110001, 0b11000001, 0b00000000, 0b00000000,
    
    /* U+F079 "" */
    0b00100000, 0b00001101, 0b11110011, 0b10000010, 0b00010000, 0b01000010, 0b00001110, 0b01111101, 0b10000000, 0b00100000,

    /* U+F07B "" */
    0b01110000, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
    
    /* U+F093 "" */
    0b00011000, 0b00111100, 0b01111110, 0b00011000, 0b00011000, 0b11011011, 0b11100111, 0b11111111,

    /* U+F095 "" */
    0b00000001, 0b10000001, 0b11000000, 0b11100000, 0b00110000, 0b00110000, 0b00011000, 0b11011000, 0b11111000, 0b01110000, 0b00000000,
    
    /* U+F0C4 "" */
    0b00000010, 0b11000110, 0b10101100, 0b11111000, 0b00111000, 0b11101100, 0b10100110, 0b11000010,

    /* U+F0C5 "" */
    0b00111100, 0b01110110, 0b11111101, 0b11111011,    0b11110111,    0b11100000,    0b01111100,

    /* U+F0C7 "" */
    0b10111100, 0b10110101, 0b10111101, 0b10000001,    0b11111111,    0b11111111,    0b11111111,    0b11111111,

    /* U+F0C9 "" */
    0b11111111, 0b11111100, 0b00000111, 0b11111111,    0b11100000,    0b00111111,    0b11111111,

    /* U+F0E0 "" */
    0b11111111, 0b01111110, 0b10111101, 0b11011011,    0b11100111,    0b11111111,

    /* U+F0E7 "" */
    0b00111000, 0b01110001, 0b11000111, 0b11110001,    0b11000011,    0b00001100,    0b00010000,

    /* U+F0EA "" */
    0b00110001, 0b11111011, 0b00000110, 0b11011101,    0b10011011,    0b11000111,    0b10001111,

    /* U+F0F3 "" */
    0b00010000, 0b01110001, 0b11110011, 0b11100111,    0b11011111,    0b11000000,    0b00001000,

    /* U+F11C "" */
    0b11111111, 0b11011011, 0b01111111, 0b11111011,    0b01111000,    0b00001111,    0b11111100,

    /* U+F124 "" */
    0b00000000, 0b10000000, 0b01100000, 0b01111000, 0b01111100, 0b01111111, 0b00111111, 0b10000000, 0b11100000, 0b00110000, 0b00000100, 0b00000000, 0b00000000,
    
    /* U+F15B "" */
    0b11101011, 0b10111110, 0b00111111, 0b11111111, 0b11111111, 0b11111111,

    /* U+F1EB "" */
    0b00001100, 0b00011111, 0b11101100, 0b00001100, 0b01111000, 0b00110011, 0b00000000, 0b00000000, 0b11000000, 0b00110000,

    /* U+F240 "" */
    0b11111111, 0b10100000, 0b00101011, 0b11101110, 0b11111011, 0b10000000, 0b10111111, 0b11100000,

    /* U+F241 "" */
    0b11111111, 0b10100000, 0b00101011, 0b11001110, 0b11110011, 0b10000000, 0b10111111, 0b11100000,

    /* U+F242 "" */
    0b11111111, 0b10100000, 0b00101011, 0b10001110, 0b11100011, 0b10000000, 0b10111111, 0b11100000,

    /* U+F243 "" */
    0b11111111, 0b10100000, 0b00101011, 0b00001110, 0b11000011, 0b10000000, 0b10111111, 0b11100000,

    /* U+F244 "" */
    0b11111111, 0b10100000, 0b00101000, 0b00001110, 0b00000011, 0b10000000, 0b10111111, 0b11100000,

    /* U+F287 ""  LV_SYMBOL_USB */
    0b00000000, 0b00000000, 0b01000000, 0b00011100, 0b00110010, 0b00111111, 0b11111111, 0b11001000, 0b00000001, 0b11000000, 0b00010000,    

    /* U+F293 ""  LV_SYMBOL_BLUETOOTH */
    0b01111101, 0b11011111, 0b10011101, 0b01011100, 0b01111101, 0b11110001, 0b11010101, 0b11100111, 0b11011101, 0b11110000,

    /* U+F2ED ""  LV_SYMBOL_TRASH */
    0b00111110, 0b00110001, 0b10111111, 0b11101011, 0b01100101, 0b10110010, 0b11011001, 0b01101100, 0b11011010, 0b00111110, 0b00000000,

    /* U+F304 ""  LV_SYMBOL_EDIT */
    0b00000010, 0b00000111, 0b00001110, 0b00011100, 0b00111000, 0b01110000, 0b10100000, 0b11000000, 0b00000000,

    /* U+F55A ""  LV_SYMBOL_BACKSPACE */
    0b00111111, 0b11011101, 0b10111111, 0b10011111, 0b11100111, 0b01110110, 0b11001111, 0b11110000,

    /* U+F7C2 ""  LV_SYMBOL_SD_CARD */
    0b00111100, 0b10101011, 0b01010111, 0b11101111, 0b11011111, 0b10111111, 0b01111110,

    /* U+F8A2 ""  LV_SYMBOL_NEW_LINE */
    0b00000001, 0b00010000, 0b10011000, 0b01011111, 0b11100110, 0b00000001, 0b00000000
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc_symbols_8[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0}         /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 4},       // \xC2\xB0
    {.bitmap_index = 2, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},       // \xE2\x80\xA2 LV_SYMBOL_BULLET
    {.bitmap_index = 4, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -1},     // \xEF\x80\x81 LV_SYMBOL_AUDIO
    {.bitmap_index = 13, .adv_w = 144, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},    // \xEF\x80\x88 LV_SYMBOL_VIDEO
    {.bitmap_index = 24, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},    // \xEF\x80\x8B LV_SYMBOL_LIST
    {.bitmap_index = 32, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},     // \xEF\x80\x8C LV_SYMBOL_OK
    {.bitmap_index = 38, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},    // \xEF\x80\x8D LV_SYMBOL_CLOSE
    {.bitmap_index = 45, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},    // \xEF\x80\x91 LV_SYMBOL_POWER
    {.bitmap_index = 53, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},    // \xEF\x80\x93 LV_SYMBOL_SETTINGS
    {.bitmap_index = 61, .adv_w = 144, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = -1},    // \xEF\x80\x95 LV_SYMBOL_HOME
    {.bitmap_index = 70, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},    // \xEF\x80\x99 LV_SYMBOL_DOWNLOAD
    {.bitmap_index = 78, .adv_w = 144, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},     // \xEF\x80\x9C LV_SYMBOL_DRIVE
    {.bitmap_index = 85, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},    // \xEF\x80\xA1 LV_SYMBOL_REFRESH
    {.bitmap_index = 93, .adv_w = 64, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},     // \xEF\x80\xA6 LV_SYMBOL_MUTE
    {.bitmap_index = 97, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},     // \xEF\x80\xA7 LV_SYMBOL_VOLUME_MID
    {.bitmap_index = 103, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x80\xA8 LV_SYMBOL_VOLUME_MAX
    {.bitmap_index = 111, .adv_w = 144, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},    // \xEF\x80\xBE LV_SYMBOL_IMAGE
    {.bitmap_index = 119, .adv_w = 88, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},    // \xEF\x81\x83 LV_SYMBOL_TINT
    {.bitmap_index = 125, .adv_w = 112, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},   // \xEF\x81\x88 LV_SYMBOL_PREV
    {.bitmap_index = 130, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},  // \xEF\x81\x8B LV_SYMBOL_PLAY
    {.bitmap_index = 139, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x81\x8C LV_SYMBOL_PAUSE
    {.bitmap_index = 146, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x81\x8D LV_SYMBOL_STOP
    {.bitmap_index = 153, .adv_w = 112, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},   // \xEF\x81\x91 LV_SYMBOL_NEXT
    {.bitmap_index = 158, .adv_w = 112, .box_w = 9, .box_h = 8, .ofs_x = -1, .ofs_y = -1},  // \xEF\x81\x92 LV_SYMBOL_EJECT
    {.bitmap_index = 167, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -1},    // \xEF\x81\x93 LV_SYMBOL_LEFT
    {.bitmap_index = 172, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -1},    // \xEF\x81\x94 LV_SYMBOL_RIGHT
    {.bitmap_index = 177, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x81\xA7 LV_SYMBOL_PLUS
    {.bitmap_index = 184, .adv_w = 112, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 2},    // \xEF\x81\xA8 LV_SYMBOL_MINUS
    {.bitmap_index = 186, .adv_w = 152, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},   // \xEF\x81\xAE LV_SYMBOL_EYE_OPEN
    {.bitmap_index = 194, .adv_w = 160, .box_w = 11, .box_h = 8, .ofs_x = -1, .ofs_y = -1}, // \xEF\x81\xB0 LV_SYMBOL_EYE_CLOSE
    {.bitmap_index = 205, .adv_w = 144, .box_w = 11, .box_h = 8, .ofs_x = -1, .ofs_y = -1}, // \xEF\x81\xB1 LV_SYMBOL_WARNING
    {.bitmap_index = 216, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x81\xB4 LV_SYMBOL_SHUFFLE
    {.bitmap_index = 224, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},    // \xEF\x81\xB7 LV_SYMBOL_UP
    {.bitmap_index = 230, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},    // \xEF\x81\xB8 LV_SYMBOL_DOWN
    {.bitmap_index = 236, .adv_w = 160, .box_w = 11, .box_h = 7, .ofs_x = -1, .ofs_y = -1}, // \xEF\x81\xB9 LV_SYMBOL_LOOP
    {.bitmap_index = 246, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},    // \xEF\x81\xBB LV_SYMBOL_DIRECTORY
    {.bitmap_index = 252, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x82\x93 LV_SYMBOL_UPLOAD
    {.bitmap_index = 260, .adv_w = 128, .box_w = 9, .box_h = 9, .ofs_x = -1, .ofs_y = -1},  // \xEF\x82\x95 LV_SYMBOL_CALL
    {.bitmap_index = 271, .adv_w = 112, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x83\x84 LV_SYMBOL_CUT
    {.bitmap_index = 279, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x83\x85 LV_SYMBOL_COPY
    {.bitmap_index = 286, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x83\x87 LV_SYMBOL_SAVE
    {.bitmap_index = 294, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x83\x89 LV_SYMBOL_BARS
    {.bitmap_index = 301, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},    // \xEF\x83\xA0 LV_SYMBOL_ENVELOPE
    {.bitmap_index = 307, .adv_w = 80, .box_w = 7, .box_h = 8, .ofs_x = -1, .ofs_y = -1},   // \xEF\x83\xA7 LV_SYMBOL_CHARGE
    {.bitmap_index = 314, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x83\xAA LV_SYMBOL_PASTE
    {.bitmap_index = 321, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x83\xB3 LV_SYMBOL_BELL
    {.bitmap_index = 328, .adv_w = 144, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},    // \xEF\x84\x9C LV_SYMBOL_KEYBOARD
    {.bitmap_index = 335, .adv_w = 128, .box_w = 10, .box_h = 10, .ofs_x = -1, .ofs_y = -2}, // \xEF\x84\xA4 LV_SYMBOL_GPS
    {.bitmap_index = 348, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // \xEF\x85\x9B LV_SYMBOL_FILE
    {.bitmap_index = 354, .adv_w = 160, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = -1}, // \xEF\x87\xAB LV_SYMBOL_WIFI
    {.bitmap_index = 364, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // \xEF\x89\x80 LV_SYMBOL_BATTERY_FULL
    {.bitmap_index = 372, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // \xEF\x89\x81 LV_SYMBOL_BATTERY_3
    {.bitmap_index = 380, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // \xEF\x89\x82 LV_SYMBOL_BATTERY_2
    {.bitmap_index = 388, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // \xEF\x89\x83 LV_SYMBOL_BATTERY_1
    {.bitmap_index = 396, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // \xEF\x89\x84 LV_SYMBOL_BATTERY_EMPTY
    {.bitmap_index = 404, .adv_w = 160, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = -1}, // LV_SYMBOL_USB
    {.bitmap_index = 415, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -1},  // LV_SYMBOL_BLUETOOTH
    {.bitmap_index = 425, .adv_w = 128, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = -1},  // LV_SYMBOL_TRASH
    {.bitmap_index = 436, .adv_w = 112, .box_w = 8, .box_h = 9, .ofs_x = -1, .ofs_y = -2}, // LV_SYMBOL_EDIT
    {.bitmap_index = 445, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // LV_SYMBOL_BACKSPACE
    {.bitmap_index = 453, .adv_w = 96, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},   // LV_SYMBOL_SD_CARD
    {.bitmap_index = 460, .adv_w = 129, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0}    // LV_SYMBOL_NEW_LINE
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_symbols_8[] = {
    0x0, 0x1f72, 0xef51, 0xef58, 0xef5b, 0xef5c, 0xef5d, 0xef61,
    0xef63, 0xef65, 0xef69, 0xef6c, 0xef71, 0xef76, 0xef77, 0xef78,
    0xef8e, 0xef93, 0xef98, 0xef9b, 0xef9c, 0xef9d, 0xefa1, 0xefa2,
    0xefa3, 0xefa4, 0xefb7, 0xefb8, 0xefbe, 0xefc0, 0xefc1, 0xefc4,
    0xefc7, 0xefc8, 0xefc9, 0xefcb, 0xefe3, 0xefe5, 0xf014, 0xf015,
    0xf017, 0xf019, 0xf030, 0xf037, 0xf03a, 0xf043, 0xf06c, 0xf074,
    0xf0ab, 0xf13b, 0xf190, 0xf191, 0xf192, 0xf193, 0xf194, 0xf1d7,
    0xf1e3, 0xf23d, 0xf254, 0xf4aa, 0xf712, 0xf7f2
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps_symbols_8[] = {
    {
        .range_start = 176, .range_length = 63475, .glyph_id_start = 1,
        .unicode_list = unicode_list_symbols_8, .glyph_id_ofs_list = NULL, .list_length = 62, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR >= 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc_symbols_8 = {
#else
static lv_font_fmt_txt_dsc_t font_dsc_symbols = {
#endif
    .glyph_bitmap = glyph_bitmap_symbols_8,
    .glyph_dsc = glyph_dsc_symbols_8,
    .cmaps = cmaps_symbols_8,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR >= 8
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t lv_font_symbols_8 = {
#else
lv_font_t lv_font_symbols_8 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc_symbols_8  /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};

