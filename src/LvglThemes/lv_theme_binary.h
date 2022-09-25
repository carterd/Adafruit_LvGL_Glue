#ifndef LV_USE_THEME_BINARY_H
#define LV_USE_THEME_BINARY_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <lvgl.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
 /**********************
  *      TYPEDEFS
  **********************/
    typedef struct {
        lv_style_t scr;
        lv_style_t card;
        lv_style_t no_scrollbar;
        lv_style_t scrollbar;
        lv_style_t inv;
        lv_style_t disabled;
        lv_style_t focus;
        lv_style_t edit;
        lv_style_t pad_zero;
        lv_style_t no_radius;
        lv_style_t radius_circle;

        lv_style_t window;

        lv_style_t matrix;

        lv_style_t calender;

        lv_style_t arc;
        lv_style_t arc_indicator;
        lv_style_t arc_knob;

        lv_style_t spinner;
        lv_style_t spinner_indicator;

        lv_style_t slider;
        lv_style_t slider_focus;
        lv_style_t slider_knob;
        lv_style_t slider_knob_edit;
        lv_style_t slider_indicator;

        lv_style_t checkbox;
        lv_style_t checkbox_checked;

        lv_style_t button;
        lv_style_t button_focus;
        lv_style_t button_checked;
        lv_style_t button_pressed;
        lv_style_t button_no_highlight;

        lv_style_t list;
        lv_style_t list_button;
        lv_style_t list_button_focus;
        lv_style_t list_scrollbar;
        lv_style_t slow_label;

#if LV_USE_TEXTAREA
        lv_style_t ta_cursor;
#endif
    } theme_binary_styles_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the theme
 * @param color_primary the primary color of the theme
 * @param color_secondary the secondary color for the theme
 * @param font pointer to a font to use.
 * @return a pointer to reference this theme later
 */
lv_theme_t * lv_theme_binary_init(lv_disp_t * disp, bool dark_bg, const lv_font_t * font);

/**
* Check if the theme is initialized
* @return true if default theme is initialized, false otherwise
*/
bool lv_theme_binary_is_inited(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_USE_THEME_MONO_H*/
