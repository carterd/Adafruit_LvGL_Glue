/*********************
 *      INCLUDES
 *********************/
#include <lvgl.h>


#if LV_USE_THEME_MONO

#include "lv_theme_binary.h"

 /*********************
  *      DEFINES
  *********************/

#define COLOR_FG      dark_bg ?  lv_color_white() : lv_color_black() 
#define COLOR_BG      dark_bg ?  lv_color_black() : lv_color_white() 

  // Card Presets
#define CARD_OUTLINE_WIDTH      0
#define CARD_OUTLINE_PAD        0
#define CARD_BORDER_WIDTH       0
#define CARD_PAD                0
#define CARD_GAP_PAD            4

// Window Presets
#define WINDOW_OUTLINE_WIDTH    1
#define WINDOW_OUTLINE_PAD      1
#define WINDOW_BORDER_WIDTH     1
#define WINDOW_PAD              1

// Matrix Presets
#define MATRIX_OUTLINE_WIDTH    0
#define MATRIX_OUTLINE_PAD      0
#define MATRIX_BORDER_WIDTH     0
#define MATRIX_PAD              4

// Arc Presets
#define ARC_WIDTH               1
#define ARC_PAD                 0
#define ARC_INDICATOR_WIDTH     3
#define ARC_INDICATOR_PAD       -1
#define ARC_KNOB_OUTLINE_WIDTH       1                           // White outline beyond the black border
#define ARC_KNOB_OUTLINE_PAD         1                           // Black border size around the knob (0=no border)
#define ARC_KNOB_BORDER_WIDTH        SLIDER_KNOB_OUTLINE_PAD     //
#define ARC_KNOB_RADIUS              LV_RADIUS_CIRCLE            // The shape of the Knob (0=square ... LV_RADIUS_CIRCLE=round)
#define ARC_KNOB_PAD                 2                          // Padding Knob makes it larger than slider

// Spinner Presets
#define SPINNER_WIDTH           4
#define SPINNER_PAD             0
#define SPINNER_INDICATOR_WIDTH 4
#define SPINNER_INDICATOR_PAD   0

// Slider Presets
#define SLIDER_OUTLINE_WIDTH            1                           // White outline beyond the black border
#define SLIDER_OUTLINE_PAD              1                           // Black border size around the slider (0=no border)
#define SLIDER_BORDER_WIDTH             SLIDER_OUTLINE_PAD          //
#define SLIDER_RADIUS                   LV_RADIUS_CIRCLE            // The shape of the slider (0=square ... LV_RADIUS_CIRCLE=round)
#define SLIDER_PAD                      0                           // Slider horizontal increase beyond knob extremes
#define SLIDER_INDICATOR_BORDER_WIDTH   1                           // Black border around indicator (0=no border)
#define SLIDER_KNOB_OUTLINE_WIDTH       1                           // White outline beyond the black border
#define SLIDER_KNOB_OUTLINE_PAD         1                           // Black border size around the knob (0=no border)
#define SLIDER_KNOB_BORDER_WIDTH        SLIDER_KNOB_OUTLINE_PAD     //
#define SLIDER_KNOB_RADIUS              LV_RADIUS_CIRCLE            // The shape of the Knob (0=square ... LV_RADIUS_CIRCLE=round)
#define SLIDER_KNOB_PAD                 0                           // Padding Knob makes it larger than slider
#define SLIDER_ANIM_SPEED                50

// CheckBox Presets
#define CHECKBOX_PAD                    -2

// Button Presets
#define BUTTON_OUTLINE_WIDTH    1
#define BUTTON_OUTLINE_PAD      1
#define BUTTON_BORDER_WIDTH     1
#define BUTTON_RADIUS           2
#define BUTTON_PAD              1
#define BUTTON_PAD_COL          4
#define BUTTON_PAD_HOR          2

// List Presets
#define LIST_OUTLINE_WIDTH      0
#define LIST_OUTLINE_PAD        0
#define LIST_BORDER_WIDTH       0
#define LIST_SCROLL_WIDTH       1
#define LIST_BUTTON_PAD_COL     4
#define LIST_BUTTON_PAD_HOR     1

// Scroll Bar Presets
#define SCROLL_WIDTH        2

#define BORDER_W_PR         0
#define BORDER_W_DIS        0
#define BORDER_W_FOCUS      0
#define BORDER_W_EDIT       10
#define PAD_DEF             4

#define LABEL_ANIM_SPEED    10
#define DEFAULT_ANIM_SPEED  1



/**********************
 *  STATIC PROTOTYPES
 **********************/
static void style_init_reset(lv_style_t* style);
static void theme_apply(lv_theme_t* th, lv_obj_t* obj);

/**********************
 *  STATIC VARIABLES
 **********************/
static theme_binary_styles_t* binary_styles = NULL;
static lv_theme_t binary_theme;
static bool inited;

/**********************
 *      MACROS
 **********************/

 /**********************
  *   STATIC FUNCTIONS
  **********************/

static void style_init(bool dark_bg, const lv_font_t* font)
{

    // Screen
    style_init_reset(&binary_styles->scr);
    lv_style_set_bg_opa(&binary_styles->scr, LV_OPA_COVER);
    lv_style_set_bg_color(&binary_styles->scr, COLOR_BG);
    lv_style_set_text_color(&binary_styles->scr, COLOR_FG);
    lv_style_set_pad_row(&binary_styles->scr, PAD_DEF);
    lv_style_set_pad_column(&binary_styles->scr, PAD_DEF);
    lv_style_set_text_font(&binary_styles->scr, font);
    lv_style_set_shadow_opa(&binary_styles->scr, LV_OPA_TRANSP);
    lv_style_set_anim_speed(&binary_styles->scr, DEFAULT_ANIM_SPEED);

    // Inverted
    style_init_reset(&binary_styles->inv);
    lv_style_set_bg_opa(&binary_styles->inv, LV_OPA_COVER);
    lv_style_set_bg_color(&binary_styles->inv, COLOR_FG);
    lv_style_set_border_color(&binary_styles->inv, COLOR_BG);
    lv_style_set_line_color(&binary_styles->inv, COLOR_BG);
    lv_style_set_arc_color(&binary_styles->inv, COLOR_BG);
    lv_style_set_text_color(&binary_styles->inv, COLOR_BG);
    lv_style_set_outline_color(&binary_styles->inv, COLOR_BG);

    // Disabled
    style_init_reset(&binary_styles->disabled);
    lv_style_set_border_width(&binary_styles->disabled, BORDER_W_DIS);

    // Focused
    style_init_reset(&binary_styles->focus);
    lv_style_set_bg_opa(&binary_styles->focus, LV_OPA_COVER);
    lv_style_set_outline_pad(&binary_styles->focus, BORDER_W_FOCUS);
    lv_style_set_pad_gap(&binary_styles->focus, 20);

    lv_style_set_bg_color(&binary_styles->focus, COLOR_FG);
    lv_style_set_border_color(&binary_styles->focus, COLOR_BG);
    lv_style_set_line_color(&binary_styles->focus, COLOR_BG);
    lv_style_set_arc_color(&binary_styles->focus, COLOR_BG);
    lv_style_set_text_color(&binary_styles->focus, COLOR_BG);

    // Edit
    style_init_reset(&binary_styles->edit);
    lv_style_set_outline_width(&binary_styles->edit, BORDER_W_EDIT);

    style_init_reset(&binary_styles->pad_zero);
    lv_style_set_pad_all(&binary_styles->pad_zero, 0);
    lv_style_set_pad_gap(&binary_styles->pad_zero, 0);

    style_init_reset(&binary_styles->no_radius);
    lv_style_set_radius(&binary_styles->no_radius, 0);

    style_init_reset(&binary_styles->radius_circle);
    lv_style_set_radius(&binary_styles->radius_circle, LV_RADIUS_CIRCLE);


    lv_style_t* sp;

    // ScrollBar
    //---------------------------------------------------------------------------------------------

    // On ScrollBar
    sp = &binary_styles->scrollbar;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);
    lv_style_set_bg_color(sp, COLOR_FG);
    lv_style_set_width(sp, SCROLL_WIDTH);
    // Off ScrollBar
    sp = &binary_styles->no_scrollbar;
    style_init_reset(sp);
    lv_style_set_width(sp, 0);


    // Card Style
    //---------------------------------------------------------------------------------------------
    sp = &binary_styles->card;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_text_font(sp, font);

    lv_style_set_outline_width(sp, CARD_OUTLINE_WIDTH);       // Outline width    +===================+
    lv_style_set_outline_pad(sp, CARD_OUTLINE_PAD);           // Outline pad      |                   |
    lv_style_set_border_width(sp, CARD_BORDER_WIDTH);         // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, CARD_PAD);                       // Pad all          |  |             |  |
    lv_style_set_pad_gap(sp, CARD_GAP_PAD);                     // Pad gap          |  | XXXXX XXXXX |  |

    lv_style_set_bg_color(sp, COLOR_BG);
    lv_style_set_border_color(sp, COLOR_FG);
    lv_style_set_radius(sp, 0);

    lv_style_set_text_color(sp, COLOR_FG);
    lv_style_set_line_width(sp, 1);
    lv_style_set_line_color(sp, COLOR_FG);
    lv_style_set_arc_width(sp, 1);
    lv_style_set_arc_color(sp, COLOR_FG);
    lv_style_set_outline_color(sp, COLOR_FG);
    lv_style_set_anim_time(sp, 300);

    // Window Style
    //---------------------------------------------------------------------------------------------
    sp = &binary_styles->window;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_text_font(sp, font);

    lv_style_set_outline_width(sp, WINDOW_OUTLINE_WIDTH);       // Outline width    +===================+
    lv_style_set_outline_pad(sp, WINDOW_OUTLINE_PAD);           // Outline pad      |                   |
    lv_style_set_border_width(sp, WINDOW_BORDER_WIDTH);         // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, WINDOW_PAD);                       // Pad all          |  |             |  |
    lv_style_set_pad_gap(sp, WINDOW_PAD);                       // Pad gap          |  | XXXXX XXXXX |  |

    lv_style_set_pad_column(sp, BUTTON_PAD_COL);                // Gap between button symbols and label
    lv_style_set_pad_hor(sp, BUTTON_PAD_HOR);                   // Gap between edges on list entries

    lv_style_set_radius(sp, BUTTON_RADIUS);                     // Widget Radius
    lv_style_set_border_color(sp, COLOR_BG);
    lv_style_set_outline_color(sp, COLOR_FG);
    lv_style_set_bg_color(sp, COLOR_BG);
    lv_style_set_text_color(sp, COLOR_FG);
    lv_style_set_outline_color(sp, COLOR_FG);

    // Matrix Style
    //---------------------------------------------------------------------------------------------
    sp = &binary_styles->matrix;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_bg_color(sp, COLOR_BG);
    lv_style_set_outline_width(sp, MATRIX_OUTLINE_WIDTH);       // Outline width    +===================+
    lv_style_set_outline_pad(sp, MATRIX_OUTLINE_PAD);           // Outline pad      |                   |
    lv_style_set_border_width(sp, MATRIX_BORDER_WIDTH);         // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, MATRIX_PAD);                       // Pad all          |  |             |  |
    //lv_style_set_pad_right(sp, MATRIX_PAD - 2);
    //lv_style_set_pad_bottom(sp, MATRIX_PAD - 2);
    lv_style_set_pad_gap(sp, MATRIX_PAD);                       // Pad gap          |  | XXXXX XXXXX |  |

    // Calender Style
    //---------------------------------------------------------------------------------------------
    sp = &binary_styles->calender;
    style_init_reset(&binary_styles->calender);

    lv_style_set_border_opa(sp, LV_OPA_TRANSP);
    //lv_style_set_bg_opa(sp, LV_OPA_TRANSP);
    lv_style_set_pad_all(sp, 0);
    lv_style_set_outline_width(sp, 1);       // Outline width    +===================+
    lv_style_set_outline_pad(sp, 1);           // Outline pad     |                   |   
    lv_style_set_border_width(sp, 0);         // Border width     |  +=============+  |
    lv_style_set_outline_color(sp, COLOR_FG);
    lv_style_set_bg_color(sp, COLOR_FG);

    // Spinner Style
    //---------------------------------------------------------------------------------------------
    sp = &binary_styles->spinner;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_TRANSP);

    lv_style_set_arc_width(sp, SPINNER_WIDTH);
    lv_style_set_arc_color(sp, COLOR_FG);
    lv_style_set_arc_rounded(sp, true);
    lv_style_set_pad_all(sp, SPINNER_PAD);

    sp = &binary_styles->spinner_indicator;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_TRANSP);

    lv_style_set_arc_width(sp, SPINNER_INDICATOR_WIDTH);
    lv_style_set_arc_color(sp, COLOR_BG);
    lv_style_set_arc_rounded(sp, true);
    lv_style_set_pad_all(sp, SPINNER_INDICATOR_PAD);


    // Arc Style
    //---------------------------------------------------------------------------------------------
    sp = &binary_styles->arc;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_TRANSP);

    lv_style_set_outline_width(sp, 0);                          // Outline width    +===================+
    lv_style_set_outline_pad(sp, 0);                            // Outline pad      |                   |
    lv_style_set_border_width(sp, 0);                           // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, ARC_PAD);                          // Pad all          |  |             |  |

    lv_style_set_arc_width(sp, ARC_WIDTH);
    lv_style_set_arc_color(sp, COLOR_FG);
    lv_style_set_arc_rounded(sp, true);

    lv_style_set_bg_color(sp, COLOR_BG);
    lv_style_set_text_color(sp, COLOR_FG);

    // Arc Indicator
    sp = &binary_styles->arc_indicator;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_TRANSP);

    lv_style_set_pad_all(sp, ARC_INDICATOR_PAD);

    lv_style_set_arc_width(sp, ARC_INDICATOR_WIDTH);
    lv_style_set_arc_color(sp, COLOR_FG);
    lv_style_set_arc_rounded(sp, true);

    // Arc Knob
    sp = &binary_styles->arc_knob;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_outline_width(sp, ARC_KNOB_OUTLINE_WIDTH);       // Outline width    +===================+
    lv_style_set_outline_pad(sp, ARC_KNOB_OUTLINE_PAD);           // Outline pad      |                   |
    lv_style_set_border_width(sp, ARC_KNOB_BORDER_WIDTH);         // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, ARC_KNOB_PAD);                       // Pad all          |  |             |  |
    lv_style_set_pad_gap(sp, ARC_KNOB_PAD);                       // Pad gap          |  | XXXXX XXXXX |  |

    lv_style_set_radius(sp, SLIDER_KNOB_RADIUS);                     // Widget Radius
    lv_style_set_border_color(sp, COLOR_BG);
    lv_style_set_outline_color(sp, COLOR_FG);
    lv_style_set_bg_color(sp, COLOR_FG);
    lv_style_set_text_color(sp, COLOR_FG);
    lv_style_set_outline_color(sp, COLOR_FG);


    // Slider Style
    //---------------------------------------------------------------------------------------------
    sp = &binary_styles->slider;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_outline_width(sp, SLIDER_OUTLINE_WIDTH);       // Outline width    +===================+
    lv_style_set_outline_pad(sp, SLIDER_OUTLINE_PAD);           // Outline pad      |                   |
    lv_style_set_border_width(sp, SLIDER_BORDER_WIDTH);         // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, SLIDER_PAD);                       // Pad all          |  |             |  |
    lv_style_set_pad_hor(sp, SLIDER_PAD);                       // Pad gap          |  | XXXXX XXXXX |  |

    lv_style_set_radius(sp, SLIDER_RADIUS);                     // Widget Radius
    lv_style_set_border_color(sp, COLOR_BG);
    lv_style_set_outline_color(sp, COLOR_FG);
    lv_style_set_bg_color(sp, COLOR_BG);
    lv_style_set_text_color(sp, COLOR_FG);
    lv_style_set_outline_color(sp, COLOR_FG);

    lv_style_set_anim_time(sp, SLIDER_ANIM_SPEED);

    // Slider Indicator
    sp = &binary_styles->slider_indicator;
    style_init_reset(sp);
    lv_style_set_radius(sp, SLIDER_RADIUS);                     // Widget Radius
    lv_style_set_bg_opa(sp, LV_OPA_COVER);
    lv_style_set_border_width(sp, SLIDER_INDICATOR_BORDER_WIDTH);
    lv_style_set_border_color(sp, COLOR_BG);
    lv_style_set_bg_color(sp, COLOR_FG);

    // Slider Focus
    sp = &binary_styles->slider_focus;
    style_init_reset(sp);
    lv_style_set_border_color(sp, COLOR_FG);

    // Slider Knob
    sp = &binary_styles->slider_knob;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_outline_width(sp, SLIDER_KNOB_OUTLINE_WIDTH);       // Outline width    +===================+
    lv_style_set_outline_pad(sp, SLIDER_KNOB_OUTLINE_PAD);           // Outline pad      |                   |
    lv_style_set_border_width(sp, SLIDER_KNOB_BORDER_WIDTH);         // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, SLIDER_KNOB_PAD);                       // Pad all          |  |             |  |
    lv_style_set_pad_gap(sp, SLIDER_KNOB_PAD);                       // Pad gap          |  | XXXXX XXXXX |  |

    lv_style_set_radius(sp, SLIDER_KNOB_RADIUS);                     // Widget Radius
    lv_style_set_border_color(sp, COLOR_BG);
    lv_style_set_outline_color(sp, COLOR_FG);
    lv_style_set_bg_color(sp, COLOR_FG);
    lv_style_set_text_color(sp, COLOR_FG);
    lv_style_set_outline_color(sp, COLOR_FG);

    // Slider Knob Focus
    sp = &binary_styles->slider_knob_edit;
    style_init_reset(sp);
    lv_style_set_border_color(sp, COLOR_FG);
    lv_style_set_outline_color(sp, COLOR_BG);

    // Checkbox Style
    //---------------------------------------------------------------------------------------------
    sp = &binary_styles->checkbox;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_outline_width(sp, BUTTON_OUTLINE_WIDTH);       // Outline width    +===================+
    lv_style_set_outline_pad(sp, BUTTON_OUTLINE_PAD);           // Outline pad      |                   |
    lv_style_set_border_width(sp, BUTTON_BORDER_WIDTH);         // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, CHECKBOX_PAD);                       // Pad all          |  |             |  |
    lv_style_set_pad_gap(sp, CHECKBOX_PAD);                       // Pad gap          |  | XXXXX XXXXX |  |

    //lv_style_set_pad_column(sp, BUTTON_PAD_COL);                // Gap between button symbols and label
    //lv_style_set_pad_hor(sp, BUTTON_PAD_HOR);                   // Gap between edges on list entries

    lv_style_set_radius(sp, BUTTON_RADIUS);                     // Widget Radius
    lv_style_set_border_color(sp, COLOR_BG);
    lv_style_set_outline_color(sp, COLOR_FG);
    lv_style_set_bg_color(sp, COLOR_BG);
    lv_style_set_text_color(sp, COLOR_FG);
    lv_style_set_outline_color(sp, COLOR_FG);

    lv_style_set_bg_img_src(sp, NULL);

    // Checkbox checked
    sp = &binary_styles->checkbox_checked;
    style_init_reset(sp);
    lv_style_set_bg_img_src(sp, LV_SYMBOL_OK);
    lv_style_set_text_color(sp, COLOR_BG);
    lv_style_set_bg_color(sp, COLOR_FG);
    lv_style_set_text_color(sp, COLOR_BG);

    // Button Style
    //---------------------------------------------------------------------------------------------
    sp = &binary_styles->button;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_outline_width(sp, BUTTON_OUTLINE_WIDTH);       // Outline width    +===================+
    lv_style_set_outline_pad(sp, BUTTON_OUTLINE_PAD);           // Outline pad      |                   |
    lv_style_set_border_width(sp, BUTTON_BORDER_WIDTH);         // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, BUTTON_PAD);                       // Pad all          |  |             |  |
    lv_style_set_pad_gap(sp, BUTTON_PAD);                       // Pad gap          |  | XXXXX XXXXX |  |

    lv_style_set_pad_column(sp, BUTTON_PAD_COL);                // Gap between button symbols and label
    lv_style_set_pad_hor(sp, BUTTON_PAD_HOR);                   // Gap between edges on list entries

    lv_style_set_radius(sp, BUTTON_RADIUS);                     // Widget Radius
    lv_style_set_border_color(sp, COLOR_BG);
    lv_style_set_outline_color(sp, COLOR_FG);
    lv_style_set_bg_color(sp, COLOR_BG);
    lv_style_set_text_color(sp, COLOR_FG);
    lv_style_set_outline_color(sp, COLOR_FG);

    // Button Focus
    sp = &binary_styles->button_focus;
    style_init_reset(sp);
    lv_style_set_border_color(sp, COLOR_FG);

    //lv_style_set_border_width(&binary_styles->button, BUTTON_BORDER_WIDTH + 1);

    // Button Checked
    sp = &binary_styles->button_checked;
    style_init_reset(sp);
    lv_style_set_bg_color(sp, COLOR_FG);
    lv_style_set_text_color(sp, COLOR_BG);

    // Button Pressed
    sp = &binary_styles->button_pressed;
    style_init_reset(sp);
    lv_style_set_outline_color(sp, COLOR_BG);
    lv_style_set_border_color(sp, COLOR_FG);

    // Button No Highlight (no borders)
    sp = &binary_styles->button_no_highlight;
    style_init_reset(sp);
    lv_style_set_outline_width(sp, 0);                          // Outline width    +===================+
    lv_style_set_outline_pad(sp, 0);                            // Outline pad      |                   |
    lv_style_set_border_width(sp, 0);                           // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, 0);                                // Pad all          |  |             |  |
    lv_style_set_pad_gap(sp, 0);                                // Pad gap          |  | XXXXX XXXXX |  |

    // List Style
    //---------------------------------------------------------------------------------------------
    sp = &binary_styles->list;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_outline_width(sp, LIST_OUTLINE_WIDTH);      // Outline width    +===================+
    lv_style_set_outline_pad(sp, LIST_OUTLINE_PAD);          // Outline pad      |                   |
    lv_style_set_border_width(sp, LIST_BORDER_WIDTH);        // Border width     |  +=============+  |
    lv_style_set_pad_all(sp, 0);                             // Pad all          |  |             |  |
    lv_style_set_pad_gap(sp, 0);                             // Pad gap          |  | XXXXX XXXXX |  |

    lv_style_set_radius(sp, 0);                              // Widget Radius
    lv_style_set_line_width(sp, 1);                          // Line Widths
    lv_style_set_arc_width(sp, 1);                           // Arc Widths

    lv_style_set_bg_color(sp, COLOR_BG);                     // Background Colour
    lv_style_set_outline_color(sp, COLOR_FG);                // Outline Colour
    lv_style_set_border_color(sp, COLOR_FG);                 // Border Colour       
    lv_style_set_text_color(sp, COLOR_FG);                   // Text Colour
    lv_style_set_line_color(sp, COLOR_FG);                   // Line Colour
    lv_style_set_arc_color(sp, COLOR_FG);                    // Arcs Colour

    lv_style_set_text_decor(sp, LV_TEXT_DECOR_UNDERLINE);    // Default text in list to underlined

    // List Button
    sp = &binary_styles->list_button;
    style_init_reset(sp);
    lv_style_set_pad_column(sp, LIST_BUTTON_PAD_COL); // Gap between button symbols and label
    lv_style_set_pad_hor(sp, LIST_BUTTON_PAD_HOR);    // Gap between edges on list entries

    lv_style_set_text_decor(sp, LV_TEXT_DECOR_NONE);   // Default text in buttons not underlined

    // List Focus
    sp = &binary_styles->list_button_focus;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_bg_color(sp, COLOR_FG);        // Background Colour
    lv_style_set_outline_color(sp, COLOR_FG);   // Outline Colour
    lv_style_set_border_color(sp, COLOR_FG);    // Border Colour
    lv_style_set_text_color(sp, COLOR_BG);      // Text Colour
    lv_style_set_line_color(sp, COLOR_BG);      // Line Colour
    lv_style_set_arc_color(sp, COLOR_BG);       // Arcs Colour

    // List ScrollBar
    sp = &binary_styles->list_scrollbar;
    style_init_reset(sp);
    lv_style_set_bg_opa(sp, LV_OPA_COVER);

    lv_style_set_bg_color(sp, COLOR_FG);
    lv_style_set_width(sp, LIST_SCROLL_WIDTH);

    // Slow Label Style
    sp = &binary_styles->slow_label;
    style_init_reset(sp);
    lv_style_set_anim_speed(sp, LABEL_ANIM_SPEED);     // Specific Animation for labels

#if LV_USE_TEXTAREA
    // TA Cursor
    //---------------------------------------------------------------------------------------------

    sp = &binary_styles->ta_cursor;
    style_init_reset(sp);
    lv_style_set_border_side(sp, LV_BORDER_SIDE_LEFT);
    lv_style_set_border_color(sp, COLOR_FG);
    lv_style_set_pad_left(sp, -1);
    lv_style_set_border_width(sp, 1);
    lv_style_set_bg_opa(sp, LV_OPA_TRANSP);
    lv_style_set_anim_time(sp, 500);
#endif
}


/**********************
 *   GLOBAL FUNCTIONS
 **********************/

bool lv_theme_binary_is_inited(void)
{
    return  binary_styles == NULL ? false : true;
}

lv_theme_t* lv_theme_binary_init(lv_disp_t* disp, bool dark_bg, const lv_font_t* font)
{
    /*This trick is required only to avoid the garbage collection of
     *styles' data if LVGL is used in a binding (e.g. Micropython)
     *In a general case styles could be in simple `static lv_style_t my_style...` variables*/
    if (!lv_theme_binary_is_inited()) {
        inited = false;
#if LVGL_VERSION_MAJOR > 8
        binary_styles = lv_malloc(sizeof(theme_binary_styles_t));
#else
        binary_styles = lv_mem_alloc(sizeof(theme_binary_styles_t));
#endif
    }

    binary_theme.disp = disp;
    binary_theme.font_small = LV_FONT_DEFAULT;
    binary_theme.font_normal = LV_FONT_DEFAULT;
    binary_theme.font_large = LV_FONT_DEFAULT;
    binary_theme.apply_cb = theme_apply;
    binary_theme.user_data = binary_styles;

    style_init(dark_bg, font);

    if (disp == NULL || lv_disp_get_theme(disp) != &binary_theme) {
        lv_obj_report_style_change(NULL);
    }

    inited = true;

    return (lv_theme_t*)&binary_theme;
}


static void theme_apply(lv_theme_t* th, lv_obj_t* obj)
{
    LV_UNUSED(th);

    lv_obj_t* parent = lv_obj_get_parent(obj);
    if (parent == NULL) {
        lv_obj_add_style(obj, &binary_styles->scr, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
        return;
    }

    lv_obj_t* parent_parent = lv_obj_get_parent(parent);

    if (lv_obj_check_type(obj, &lv_obj_class)) {
#if LV_USE_TABVIEW
        /*Tabview content area*/
        if (lv_obj_check_type(parent, &lv_tabview_class)) {
            return;
        }
        /*Tabview pages*/
        else if (lv_obj_check_type(parent_parent, &lv_tabview_class)) {
            lv_obj_add_style(obj, &binary_styles->card, LV_PART_MAIN);
            lv_obj_add_style(obj, &binary_styles->no_radius, LV_PART_MAIN);
            lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
            return;
        }
#endif

#if LV_USE_WIN
        /*Header*/
        if (lv_obj_get_index(obj) == 0 && lv_obj_check_type(parent, &lv_win_class)) {
            lv_obj_add_style(obj, &binary_styles->card, LV_PART_MAIN);
            lv_obj_add_style(obj, &binary_styles->no_radius, LV_PART_MAIN);
            return;
        }
        /*Content*/
        else if (lv_obj_get_index(obj) == 1 && lv_obj_check_type(parent, &lv_win_class)) {
            lv_obj_add_style(obj, &binary_styles->card, LV_PART_MAIN);
            lv_obj_add_style(obj, &binary_styles->no_radius, LV_PART_MAIN);
            lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
            return;
        }
#endif
        //lv_obj_add_style(obj, &binary_styles->card, LV_PART_MAIN);
        //lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
    }
#if LV_USE_BTN
    else if (lv_obj_check_type(obj, &lv_btn_class)) {
        lv_obj_add_style(obj, &binary_styles->button, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->button_pressed, LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->button_checked, LV_STATE_CHECKED);
        lv_obj_add_style(obj, &binary_styles->disabled, LV_STATE_DISABLED);
        lv_obj_add_style(obj, &binary_styles->button_focus, LV_STATE_FOCUS_KEY);
    }
#endif
#if LV_USE_BTNMATRIX
    else if (lv_obj_check_type(obj, &lv_btnmatrix_class)) {
#if LV_USE_MSGBOX
        if (lv_obj_check_type(parent, &lv_msgbox_class)) {
            lv_obj_add_style(obj, &binary_styles->matrix, LV_PART_MAIN);
            lv_obj_add_style(obj, &binary_styles->button_focus, LV_STATE_FOCUS_KEY);
            lv_obj_add_style(obj, &binary_styles->button, LV_PART_ITEMS);
            lv_obj_add_style(obj, &binary_styles->button_pressed, LV_PART_ITEMS | LV_STATE_PRESSED);
            lv_obj_add_style(obj, &binary_styles->button_checked, LV_PART_ITEMS | LV_STATE_CHECKED);
            lv_obj_add_style(obj, &binary_styles->disabled, LV_PART_ITEMS | LV_STATE_DISABLED);
            lv_obj_add_style(obj, &binary_styles->button_focus, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);

            return;
        }
#endif
#if LV_USE_TABVIEW
        if (lv_obj_check_type(parent, &lv_tabview_class)) {
            lv_obj_add_style(obj, &binary_styles->matrix, LV_PART_MAIN);
            lv_obj_add_style(obj, &binary_styles->button_focus, LV_STATE_FOCUS_KEY);
            lv_obj_add_style(obj, &binary_styles->button, LV_PART_ITEMS);
            lv_obj_add_style(obj, &binary_styles->button_pressed, LV_PART_ITEMS | LV_STATE_PRESSED);
            lv_obj_add_style(obj, &binary_styles->button_checked, LV_PART_ITEMS | LV_STATE_CHECKED);
            lv_obj_add_style(obj, &binary_styles->disabled, LV_PART_ITEMS | LV_STATE_DISABLED);
            lv_obj_add_style(obj, &binary_styles->button_focus, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
            return;
        }
#endif
#if LV_USE_CALENDAR
        if (lv_obj_check_type(parent, &lv_calendar_class)) {
            lv_obj_add_style(obj, &binary_styles->matrix, LV_PART_MAIN);

            //lv_obj_add_style(obj, &binary_styles->button_focus, LV_STATE_FOCUS_KEY);
            lv_obj_add_style(obj, &binary_styles->button, LV_PART_ITEMS);
            lv_obj_add_style(obj, &binary_styles->button_pressed, LV_PART_ITEMS | LV_STATE_PRESSED);
            lv_obj_add_style(obj, &binary_styles->button_checked, LV_PART_ITEMS | LV_STATE_CHECKED);
            lv_obj_add_style(obj, &binary_styles->card, LV_PART_ITEMS | LV_STATE_DISABLED);
            lv_obj_add_style(obj, &binary_styles->button_focus, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
            //lv_obj_add_style(obj, &binary_styles->focus, LV_PART_ITEMS | LV_STATE_DISABLED | LV_BTNMATRIX_CTRL_DISABLED);
            return;
        }
#endif
        lv_obj_add_style(obj, &binary_styles->matrix, LV_PART_MAIN);
        //lv_obj_add_style(obj, &binary_styles->button_focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->button, LV_PART_ITEMS);
        lv_obj_add_style(obj, &binary_styles->button_pressed, LV_PART_ITEMS | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->button_checked, LV_PART_ITEMS | LV_STATE_CHECKED);
        lv_obj_add_style(obj, &binary_styles->disabled, LV_PART_ITEMS | LV_STATE_DISABLED);
        lv_obj_add_style(obj, &binary_styles->button_focus, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
    }
#endif

#if LV_USE_BAR
    else if (lv_obj_check_type(obj, &lv_bar_class)) {

        lv_obj_add_style(obj, &binary_styles->button, LV_PART_MAIN);
        //lv_obj_add_style(obj, &binary_styles->pad_zero, 0);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_INDICATOR);
        //lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
    }
#endif

#if LV_USE_SLIDER
    else if (lv_obj_check_type(obj, &lv_slider_class)) {
        lv_obj_add_style(obj, &binary_styles->slider, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->slider_indicator, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->slider_knob, LV_PART_KNOB);
        lv_obj_add_style(obj, &binary_styles->slider_focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->slider_focus, LV_PART_INDICATOR | LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->slider_knob_edit, LV_PART_KNOB | LV_STATE_EDITED);
    }
#endif

#if LV_USE_TABLE
    else if (lv_obj_check_type(obj, &lv_table_class)) {
        lv_obj_add_style(obj, &binary_styles->matrix, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &binary_styles->scr, LV_PART_ITEMS);
        //lv_obj_add_style(obj, &binary_styles->no_radius, LV_PART_ITEMS);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_PART_ITEMS | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_STATE_FOCUS_KEY);
        //lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_CHECKBOX
    else if (lv_obj_check_type(obj, &lv_checkbox_class)) {
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->checkbox, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->disabled, LV_PART_INDICATOR | LV_STATE_DISABLED);
        lv_obj_add_style(obj, &binary_styles->checkbox_checked, LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_add_style(obj, &binary_styles->button_pressed, LV_PART_INDICATOR | LV_STATE_PRESSED);
    }
#endif

#if LV_USE_SWITCH
    else if (lv_obj_check_type(obj, &lv_switch_class)) {
        lv_obj_add_style(obj, &binary_styles->slider, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->slider_indicator, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->slider_knob, LV_PART_KNOB);
        lv_obj_add_style(obj, &binary_styles->slider_focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->slider_focus, LV_PART_INDICATOR | LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->slider_knob_edit, LV_PART_KNOB | LV_STATE_PRESSED);
    }
#endif

#if LV_USE_CHART
    else if (lv_obj_check_type(obj, &lv_chart_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_ITEMS);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_TICKS);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_CURSOR);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
    }
#endif

#if LV_USE_ROLLER
    else if (lv_obj_check_type(obj, &lv_roller_class)) {
        lv_obj_add_style(obj, &binary_styles->list, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_PART_SELECTED);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_STATE_FOCUS_KEY);
        //lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_DROPDOWN
    else if (lv_obj_check_type(obj, &lv_dropdown_class)) {
        lv_obj_add_style(obj, &binary_styles->button, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->button_pressed, LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->button_focus, LV_STATE_FOCUS_KEY);
        //lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
    else if (lv_obj_check_type(obj, &lv_dropdownlist_class)) {
        lv_obj_add_style(obj, &binary_styles->list, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_PART_SELECTED | LV_STATE_CHECKED);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_PART_SELECTED | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_STATE_FOCUS_KEY);
        //lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif
#if LV_USE_SPINNER
    else if (lv_obj_check_type(obj, &lv_spinner_class)) {

        lv_obj_add_style(obj, &binary_styles->spinner, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->spinner_indicator, LV_PART_INDICATOR);
        //lv_obj_add_style(obj, &binary_styles->slider_knob, LV_PART_KNOB);
        //lv_obj_add_style(obj, &binary_styles->slider_focus, LV_STATE_FOCUS_KEY);
        //lv_obj_add_style(obj, &binary_styles->slider_focus, LV_PART_INDICATOR | LV_STATE_FOCUS_KEY);
        //lv_obj_add_style(obj, &binary_styles->slider_knob_edit, LV_PART_KNOB | LV_STATE_EDITED);
    }
#endif
#if LV_USE_ARC
    else if (lv_obj_check_type(obj, &lv_arc_class)) {
        lv_obj_add_style(obj, &binary_styles->arc, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->arc_indicator, LV_PART_INDICATOR);
        //lv_obj_add_style(obj, &binary_styles->slider_indicator, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->arc_knob, LV_PART_KNOB);
        lv_obj_add_style(obj, &binary_styles->slider_focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->slider_focus, LV_PART_INDICATOR | LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->slider_knob_edit, LV_PART_KNOB | LV_STATE_EDITED);

        //lv_obj_add_style(obj, &binary_styles->card, 0);
        //lv_obj_add_style(obj, &binary_styles->inv, LV_PART_INDICATOR);
        //lv_obj_add_style(obj, &binary_styles->pad_zero, LV_PART_INDICATOR);
        //lv_obj_add_style(obj, &binary_styles->card, LV_PART_KNOB);
        //lv_obj_add_style(obj, &binary_styles->radius_circle, LV_PART_KNOB);
        //lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        //lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_METER
    else if (lv_obj_check_type(obj, &lv_meter_class)) {
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_MAIN);
    }
#endif

#if LV_USE_TEXTAREA
    else if (lv_obj_check_type(obj, &lv_textarea_class)) {
        lv_obj_add_style(obj, &binary_styles->button, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &binary_styles->ta_cursor, LV_PART_CURSOR | LV_STATE_FOCUSED);
        lv_obj_add_style(obj, &binary_styles->button_focus, LV_STATE_FOCUSED);
        lv_obj_add_style(obj, &binary_styles->button_pressed, LV_STATE_EDITED);
    }
#endif

#if LV_USE_CALENDAR
    else if (lv_obj_check_type(obj, &lv_calendar_class)) {
        lv_obj_add_style(obj, &binary_styles->calender, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->calender, LV_BTNMATRIX_CTRL_DISABLED);
    }
#endif

#if LV_USE_KEYBOARD
    else if (lv_obj_check_type(obj, &lv_keyboard_class)) {

        lv_obj_add_style(obj, &binary_styles->matrix, LV_PART_MAIN);
        //lv_obj_add_style(obj, &binary_styles->button_focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->button, LV_PART_ITEMS);
        lv_obj_add_style(obj, &binary_styles->button_pressed, LV_PART_ITEMS | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->button_checked, LV_PART_ITEMS | LV_STATE_CHECKED);
        lv_obj_add_style(obj, &binary_styles->disabled, LV_PART_ITEMS | LV_STATE_DISABLED);
        lv_obj_add_style(obj, &binary_styles->button_focus, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
    }
#endif
#if LV_USE_LIST
    // The List itself
    else if (lv_obj_check_type(obj, &lv_list_class)) {
        lv_obj_add_style(obj, &binary_styles->list, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->list_scrollbar, LV_PART_SCROLLBAR);
    }
    // List Buttons itself
    else if (lv_obj_check_type(obj, &lv_list_btn_class)) {
        lv_obj_add_style(obj, &binary_styles->list_button, LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_STATE_FOCUSED | LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_STATE_PRESSED);
        //lv_obj_add_style(obj, &binary_styles->large_border, LV_STATE_EDITED);
    }
    // List Buttons Text
    else if (lv_obj_check_type(obj, &lv_label_class) && lv_obj_check_type(parent, &lv_list_btn_class)) {
        lv_obj_add_style(obj, &binary_styles->slow_label, 0);
    }
    // List Text
    else if (lv_obj_check_type(obj, &lv_list_text_class)) {
    }
#endif
#if LV_USE_MSGBOX
    else if (lv_obj_check_type(obj, &lv_msgbox_class)) {
        lv_obj_add_style(obj, &binary_styles->window, 0);
        return;
    }
#endif
#if LV_USE_SPINBOX
    else if (lv_obj_check_type(obj, &lv_spinbox_class)) {
        lv_obj_add_style(obj, &binary_styles->window, 0);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_CURSOR);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif
#if LV_USE_TILEVIEW
    else if (lv_obj_check_type(obj, &lv_tileview_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
    }
    else if (lv_obj_check_type(obj, &lv_tileview_tile_class)) {
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
    }
#endif

#if LV_USE_LED
    else if (lv_obj_check_type(obj, &lv_led_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
    }
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void style_init_reset(lv_style_t* style)
{
    if (inited) {
        lv_style_reset(style);
    }
    else {
        lv_style_init(style);
    }
}

#endif
