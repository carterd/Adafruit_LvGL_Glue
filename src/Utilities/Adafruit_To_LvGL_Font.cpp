#include "Adafruit_To_LvGL_Font.h"

static uint32_t adafruitGetGlyphDscId(const lv_font_t * font, uint32_t letter)
{
    if(letter == '\0') return 0;

    GFXfont * fdsc = (GFXfont *)font->dsc;

    /*Relative code point*/
    uint32_t dsc_id = letter - fdsc->first;
    if(dsc_id > fdsc->last) return 0;

    // Note we return the relative code point +1
    return dsc_id + 1;
}

bool adafruitGetGlyphDsc(const _lv_font_t * font, lv_font_glyph_dsc_t * dsc_out, uint32_t unicode_letter, uint32_t unicode_letter_next) {
    LV_LOG_USER("adafruitGetGlyphDsc");
    bool is_tab = false;
    if(unicode_letter == '\t') {
        unicode_letter = ' ';
        is_tab = true;
    }
    GFXfont * fdsc = (GFXfont *)font->dsc;
    uint32_t gid = adafruitGetGlyphDscId(font, unicode_letter);
    if(!gid) return false;

    /*Put together a glyph dsc*/
    const GFXglyph * gdsc = &fdsc->glyph[gid - 1];

    uint32_t adv_w = gdsc->xAdvance << 4;
    if(is_tab) adv_w *= 2;
    adv_w  = (adv_w + (1 << 3)) >> 4;

    dsc_out->adv_w = adv_w;
    dsc_out->box_h = gdsc->height;
    dsc_out->box_w = gdsc->width;
    dsc_out->ofs_x = gdsc->xOffset;
    dsc_out->ofs_y = gdsc->yOffset;
    dsc_out->ofs_y = -(gdsc->yOffset + gdsc->height);

    dsc_out->bpp   = 1;
    dsc_out->is_placeholder = false;

    if(is_tab) dsc_out->box_w = dsc_out->box_w * 2;

    LV_LOG_USER("unicode letter '%c'", unicode_letter);

    return true;
}

const uint8_t *adafruitGetGlyphBitmap(const lv_font_t * font, uint32_t unicode_letter) {
    LV_LOG_USER("adafruitGetGlyphBitmap");
    if(unicode_letter == '\t') unicode_letter = ' ';

    GFXfont * fdsc = (GFXfont *)font->dsc;
    uint32_t gid = adafruitGetGlyphDscId(font, unicode_letter);
    if(!gid) return NULL;

    const GFXglyph * gdsc = &fdsc->glyph[gid - 1];

    return &fdsc->bitmap[gdsc->bitmapOffset];
}

bool adafruitToLvGLFont(const GFXfont *adafruitFont, lv_font_t *lvFont) {
    lvFont->line_height=adafruitFont->yAdvance;    
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    lvFont->subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    lvFont->underline_position = 0,
    lvFont->underline_thickness = 0,
#endif
    lvFont->dsc = adafruitFont;
    lvFont->get_glyph_dsc = *adafruitGetGlyphDsc;
    lvFont->get_glyph_bitmap = *adafruitGetGlyphBitmap;
    lvFont->fallback = NULL;
    
    // calculate baseline
    const GFXglyph *glyphPtr = adafruitFont->glyph;
    int8_t lineHeight = lvFont->line_height;
    int8_t maxAscent = -lineHeight;
    int8_t maxDescent = -lineHeight;
    for (int i = adafruitFont->first ; i <= adafruitFont->last ; i++) {
        int8_t ascent = -glyphPtr->yOffset;
        int8_t descent = glyphPtr->yOffset + glyphPtr->height;
        if ( ascent > maxAscent) maxAscent = ascent;
        if ( descent > maxDescent) maxDescent = descent;
        int height = glyphPtr->height;
        int yoffset = glyphPtr->yOffset;
        LV_LOG_USER("LOOKING %d %d %d",i , maxAscent, maxDescent);
        glyphPtr++;
    }
    lvFont->base_line = (lineHeight + maxDescent - maxAscent) >> 1;
    return true;
}