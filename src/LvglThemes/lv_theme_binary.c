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

#define LIST_OUTLINE_WIDTH  0
#define LIST_OUTLINE_PAD    0
#define LIST_BORDER_WIDTH   0
#define LIST_SCROLL_WIDTH   1

#define BORDER_W_OFF        0
#define BORDER_W_NORMAL     0
#define BORDER_W_PR         0
#define BORDER_W_DIS        0
#define BORDER_W_FOCUS      0
#define BORDER_W_EDIT       1
#define PAD_DEF             0
#define SCROLL_WIDTH        1
#define LABEL_ANIM_SPEED    10
#define DEFAULT_ANIM_SPEED  1

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    lv_style_t scr;
    lv_style_t card;
    lv_style_t scrollbar;
    lv_style_t btn;
    lv_style_t pr;
    lv_style_t inv;
    lv_style_t disabled;
    lv_style_t focus;
    lv_style_t edit;
    lv_style_t pad_gap;
    lv_style_t pad_zero;
    lv_style_t no_radius;
    lv_style_t radius_circle;
    lv_style_t no_border;
    lv_style_t large_border;
    lv_style_t large_line_space;
    lv_style_t underline;
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
 *  STATIC PROTOTYPES
 **********************/
static void style_init_reset(lv_style_t * style);
static void theme_apply(lv_theme_t * th, lv_obj_t * obj);

/**********************
 *  STATIC VARIABLES
 **********************/
static theme_binary_styles_t * binary_styles = NULL;
static lv_theme_t binary_theme;
static bool inited;

/**********************
 *      MACROS
 **********************/

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void style_init(bool dark_bg, const lv_font_t * font)
{
    // ScrollBar
    style_init_reset(&binary_styles->scrollbar);
    lv_style_set_bg_opa(&binary_styles->scrollbar, LV_OPA_COVER);
    lv_style_set_bg_color(&binary_styles->scrollbar, COLOR_FG);
    lv_style_set_width(&binary_styles->scrollbar,  SCROLL_WIDTH);
    
    // Screen
    style_init_reset(&binary_styles->scr);
    lv_style_set_bg_opa(&binary_styles->scr, LV_OPA_COVER);
    lv_style_set_bg_color(&binary_styles->scr, COLOR_BG);
    lv_style_set_text_color(&binary_styles->scr, COLOR_FG);
    lv_style_set_pad_row(&binary_styles->scr, PAD_DEF);
    lv_style_set_pad_column(&binary_styles->scr, PAD_DEF);
    lv_style_set_text_font(&binary_styles->scr, font);
    lv_style_set_anim_speed(&binary_styles->scr, DEFAULT_ANIM_SPEED);
 
    // Card or Box
    style_init_reset(&binary_styles->card);
    lv_style_set_bg_opa(&binary_styles->card, LV_OPA_COVER);
    lv_style_set_bg_color(&binary_styles->card, COLOR_BG);
    lv_style_set_border_color(&binary_styles->card, COLOR_FG);
    lv_style_set_radius(&binary_styles->card, 1);
    lv_style_set_border_width(&binary_styles->card, BORDER_W_NORMAL);
    lv_style_set_pad_all(&binary_styles->card, PAD_DEF);
    lv_style_set_pad_gap(&binary_styles->card, PAD_DEF);
    lv_style_set_text_color(&binary_styles->card, COLOR_FG);
    lv_style_set_line_width(&binary_styles->card, 1);
    lv_style_set_line_color(&binary_styles->card, COLOR_FG);
    lv_style_set_arc_width(&binary_styles->card, 1);
    lv_style_set_arc_color(&binary_styles->card, COLOR_FG);
    lv_style_set_outline_color(&binary_styles->card, COLOR_FG);
    lv_style_set_anim_time(&binary_styles->card, 300);
 
    // Pressed
    style_init_reset(&binary_styles->pr);
    lv_style_set_border_width(&binary_styles->pr, BORDER_W_PR);
 
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
    lv_style_set_outline_width(&binary_styles->focus, 1);
    lv_style_set_outline_pad(&binary_styles->focus, BORDER_W_FOCUS);
    
    lv_style_set_bg_color(&binary_styles->focus, COLOR_FG);
    lv_style_set_border_color(&binary_styles->focus, COLOR_BG);
    lv_style_set_line_color(&binary_styles->focus, COLOR_BG);
    lv_style_set_arc_color(&binary_styles->focus, COLOR_BG); 
    lv_style_set_text_color(&binary_styles->focus, COLOR_BG); 

 
    // Edit
    style_init_reset(&binary_styles->edit);
    lv_style_set_outline_width(&binary_styles->edit, BORDER_W_EDIT);
 
    // Large border
    style_init_reset(&binary_styles->large_border);
    lv_style_set_border_width(&binary_styles->large_border, BORDER_W_EDIT);
 
    // No border
    style_init_reset(&binary_styles->no_border);
    lv_style_set_border_width(&binary_styles->no_border, BORDER_W_OFF);

    style_init_reset(&binary_styles->pad_gap);
    lv_style_set_pad_gap(&binary_styles->pad_gap, PAD_DEF);
 
    style_init_reset(&binary_styles->pad_zero);
    lv_style_set_pad_all(&binary_styles->pad_zero, 0);
    lv_style_set_pad_gap(&binary_styles->pad_zero, 0);
 
    style_init_reset(&binary_styles->no_radius);
    lv_style_set_radius(&binary_styles->no_radius, 0);
 
    style_init_reset(&binary_styles->radius_circle);
    lv_style_set_radius(&binary_styles->radius_circle, LV_RADIUS_CIRCLE);

    style_init_reset(&binary_styles->large_line_space);
    lv_style_set_text_line_space(&binary_styles->large_line_space, 6);

    style_init_reset(&binary_styles->underline);
    lv_style_set_text_decor(&binary_styles->underline, LV_TEXT_DECOR_UNDERLINE);
    
    // List Style
    //---------------------------------------------------------------------------------------------
    style_init_reset(&binary_styles->list);    
    lv_style_set_bg_opa(&binary_styles->list, LV_OPA_COVER);

    lv_style_set_outline_width(&binary_styles->list, LIST_OUTLINE_WIDTH);      // Outline width    +===================+
    lv_style_set_outline_pad(&binary_styles->list, LIST_OUTLINE_PAD);          // Outline pad      |                   |
    lv_style_set_border_width(&binary_styles->list, LIST_BORDER_WIDTH);        // Border width     |  +=============+  |
    lv_style_set_pad_all(&binary_styles->list, PAD_DEF);                       // Pad all          |  |             |  |
    lv_style_set_pad_gap(&binary_styles->list, PAD_DEF);                       // Pad gap          |  | XXXXX XXXXX |  |

    lv_style_set_radius(&binary_styles->list, 0);                              // Widget Radius
    lv_style_set_line_width(&binary_styles->list, 1);                          // Line Widths
    lv_style_set_arc_width(&binary_styles->list, 1);                           // Arc Widths

    lv_style_set_bg_color(&binary_styles->list, COLOR_BG);                     // Background Colour
    lv_style_set_outline_color(&binary_styles->list, COLOR_FG);                // Outline Colour
    lv_style_set_border_color(&binary_styles->list, COLOR_FG);                 // Border Colour       
    lv_style_set_text_color(&binary_styles->list, COLOR_FG);                   // Text Colour
    lv_style_set_line_color(&binary_styles->list, COLOR_FG);                   // Line Colour
    lv_style_set_arc_color(&binary_styles->list, COLOR_FG);                    // Arcs Colour
    
    // List Button
    style_init_reset(&binary_styles->list_button);
    lv_style_set_pad_column(&binary_styles->list_button, 4);                   // Gap between button symbols and label
    lv_style_set_pad_hor(&binary_styles->list_button, 1);                      // Gap between edges on list entries

    // List Focus
    style_init_reset(&binary_styles->list_button_focus);
    lv_style_set_bg_opa(&binary_styles->list_button_focus, LV_OPA_COVER);

    lv_style_set_bg_color(&binary_styles->list_button_focus, COLOR_FG);        // Background Colour
    lv_style_set_outline_color(&binary_styles->list_button_focus, COLOR_FG);   // Outline Colour
    lv_style_set_border_color(&binary_styles->list_button_focus, COLOR_FG);    // Border Colour
    lv_style_set_text_color(&binary_styles->list_button_focus, COLOR_BG);      // Text Colour
    lv_style_set_line_color(&binary_styles->list_button_focus, COLOR_BG);      // Line Colour
    lv_style_set_arc_color(&binary_styles->list_button_focus, COLOR_BG);       // Arcs Colour

    // List ScrollBar
    style_init_reset(&binary_styles->list_scrollbar);
    lv_style_set_bg_opa(&binary_styles->list_scrollbar, LV_OPA_COVER);

    lv_style_set_bg_color(&binary_styles->list_scrollbar, COLOR_FG);
    lv_style_set_width(&binary_styles->list_scrollbar,  LIST_SCROLL_WIDTH);

    // Slow Label Style
    style_init_reset(&binary_styles->slow_label);
    lv_style_set_anim_speed(&binary_styles->slow_label, LABEL_ANIM_SPEED);     // Specific Animation for labels

#if LV_USE_TEXTAREA
    style_init_reset(&binary_styles->ta_cursor);
    lv_style_set_border_side(&binary_styles->ta_cursor, LV_BORDER_SIDE_LEFT);
    lv_style_set_border_color(&binary_styles->ta_cursor, COLOR_FG);
    lv_style_set_border_width(&binary_styles->ta_cursor, 2);
    lv_style_set_bg_opa(&binary_styles->ta_cursor, LV_OPA_TRANSP);
    lv_style_set_anim_time(&binary_styles->ta_cursor, 500);
#endif
}


/**********************
 *   GLOBAL FUNCTIONS
 **********************/

bool lv_theme_binary_is_inited(void)
{
    return  binary_styles == NULL ? false : true;
}

lv_theme_t * lv_theme_binary_init(lv_disp_t * disp, bool dark_bg, const lv_font_t * font)
{
    /*This trick is required only to avoid the garbage collection of
     *styles' data if LVGL is used in a binding (e.g. Micropython)
     *In a general case styles could be in simple `static lv_style_t my_style...` variables*/
    if(!lv_theme_binary_is_inited()) {
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

    style_init(dark_bg, font);

    if(disp == NULL || lv_disp_get_theme(disp) != &binary_theme) {
        lv_obj_report_style_change(NULL);
    }

    inited = true;

    return (lv_theme_t *)&binary_theme;
}


static void theme_apply(lv_theme_t * th, lv_obj_t * obj)
{
    LV_UNUSED(th);    

    lv_obj_t * parent = lv_obj_get_parent(obj);
    if(parent == NULL) {
        lv_obj_add_style(obj, &binary_styles->scr, 0);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
        return;
    }

    lv_obj_t * parent_parent = lv_obj_get_parent(parent);

    if(lv_obj_check_type(obj, &lv_obj_class)) {
#if LV_USE_TABVIEW
        /*Tabview content area*/
        if(lv_obj_check_type(parent, &lv_tabview_class)) {
            return;
        }
        /*Tabview pages*/
        else if(lv_obj_check_type(parent_parent, &lv_tabview_class)) {
            lv_obj_add_style(obj, &binary_styles->card, 0);
            lv_obj_add_style(obj, &binary_styles->no_radius, 0);
            lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
            return;
        }
#endif

#if LV_USE_WIN
        /*Header*/
        if(lv_obj_get_index(obj) == 0 && lv_obj_check_type(parent, &lv_win_class)) {
            lv_obj_add_style(obj, &binary_styles->card, 0);
            lv_obj_add_style(obj, &binary_styles->no_radius, 0);
            return;
        }
        /*Content*/
        else if(lv_obj_get_index(obj) == 1 && lv_obj_check_type(parent, &lv_win_class)) {
            lv_obj_add_style(obj, &binary_styles->card, 0);
            lv_obj_add_style(obj, &binary_styles->no_radius, 0);
            lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
            return;
        }
#endif
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
    }
#if LV_USE_BTN
    else if(lv_obj_check_type(obj, &lv_btn_class)) {
        //lv_obj_add_style(obj, &styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->no_border, 0);
        lv_obj_add_style(obj, &binary_styles->pr, LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->inv, LV_STATE_CHECKED);
        lv_obj_add_style(obj, &binary_styles->disabled, LV_STATE_DISABLED);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif
#if LV_USE_BTNMATRIX
    else if(lv_obj_check_type(obj, &lv_btnmatrix_class)) {
#if LV_USE_MSGBOX
        if(lv_obj_check_type(parent, &lv_msgbox_class)) {
            lv_obj_add_style(obj, &binary_styles->pad_gap, 0);
            lv_obj_add_style(obj, &binary_styles->card, LV_PART_ITEMS);
            lv_obj_add_style(obj, &binary_styles->pr, LV_PART_ITEMS | LV_STATE_PRESSED);
            lv_obj_add_style(obj, &binary_styles->disabled, LV_PART_ITEMS | LV_STATE_DISABLED);
            lv_obj_add_style(obj, &binary_styles->underline, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
            lv_obj_add_style(obj, &binary_styles->large_border, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
            return;
        }
#endif
#if LV_USE_TABVIEW
        if(lv_obj_check_type(parent, &lv_tabview_class)) {
            lv_obj_add_style(obj, &binary_styles->pad_gap, 0);
            lv_obj_add_style(obj, &binary_styles->card, LV_PART_ITEMS);
            lv_obj_add_style(obj, &binary_styles->pr, LV_PART_ITEMS | LV_STATE_PRESSED);
            lv_obj_add_style(obj, &binary_styles->inv, LV_PART_ITEMS | LV_STATE_CHECKED);
            lv_obj_add_style(obj, &binary_styles->disabled, LV_PART_ITEMS | LV_STATE_DISABLED);
            lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
            lv_obj_add_style(obj, &binary_styles->underline, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
            lv_obj_add_style(obj, &binary_styles->large_border, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
            return;
        }
#endif
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_ITEMS);
        lv_obj_add_style(obj, &binary_styles->pr, LV_PART_ITEMS | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_ITEMS | LV_STATE_CHECKED);
        lv_obj_add_style(obj, &binary_styles->disabled, LV_PART_ITEMS | LV_STATE_DISABLED);
        lv_obj_add_style(obj, &binary_styles->underline, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->large_border, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
    }
#endif

#if LV_USE_BAR
    else if(lv_obj_check_type(obj, &lv_bar_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->pad_zero, 0);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
    }
#endif

#if LV_USE_SLIDER
    else if(lv_obj_check_type(obj, &lv_slider_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->pad_zero, 0);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_KNOB);
        lv_obj_add_style(obj, &binary_styles->radius_circle, LV_PART_KNOB);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_TABLE
    else if(lv_obj_check_type(obj, &lv_table_class)) {
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_ITEMS);
        lv_obj_add_style(obj, &binary_styles->no_radius, LV_PART_ITEMS);
        lv_obj_add_style(obj, &binary_styles->pr, LV_PART_ITEMS | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_CHECKBOX
    else if(lv_obj_check_type(obj, &lv_checkbox_class)) {
        lv_obj_add_style(obj, &binary_styles->pad_gap, LV_PART_MAIN);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->disabled, LV_PART_INDICATOR | LV_STATE_DISABLED);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_add_style(obj, &binary_styles->pr, LV_PART_INDICATOR | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_SWITCH
    else if(lv_obj_check_type(obj, &lv_switch_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->radius_circle, 0);
        lv_obj_add_style(obj, &binary_styles->pad_zero, 0);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->radius_circle, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_KNOB);
        lv_obj_add_style(obj, &binary_styles->radius_circle, LV_PART_KNOB);
        lv_obj_add_style(obj, &binary_styles->pad_zero, LV_PART_KNOB);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_CHART
    else if(lv_obj_check_type(obj, &lv_chart_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_ITEMS);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_TICKS);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_CURSOR);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
    }
#endif

#if LV_USE_ROLLER
    else if(lv_obj_check_type(obj, &lv_roller_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->large_line_space, 0);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_SELECTED);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_DROPDOWN
    else if(lv_obj_check_type(obj, &lv_dropdown_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->pr, LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
    else if(lv_obj_check_type(obj, &lv_dropdownlist_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->large_line_space, 0);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_SELECTED | LV_STATE_CHECKED);
        lv_obj_add_style(obj, &binary_styles->pr, LV_PART_SELECTED | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_ARC
    else if(lv_obj_check_type(obj, &lv_arc_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->pad_zero, LV_PART_INDICATOR);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_KNOB);
        lv_obj_add_style(obj, &binary_styles->radius_circle, LV_PART_KNOB);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_METER
    else if(lv_obj_check_type(obj, &lv_meter_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
    }
#endif

#if LV_USE_TEXTAREA
    else if(lv_obj_check_type(obj, &lv_textarea_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
        lv_obj_add_style(obj, &binary_styles->ta_cursor, LV_PART_CURSOR | LV_STATE_FOCUSED);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUSED);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif

#if LV_USE_CALENDAR
    else if(lv_obj_check_type(obj, &lv_calendar_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->no_radius, 0);
        lv_obj_add_style(obj, &binary_styles->pr, LV_PART_ITEMS | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->disabled, LV_PART_ITEMS | LV_STATE_DISABLED);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
        lv_obj_add_style(obj, &binary_styles->large_border, LV_PART_ITEMS | LV_STATE_FOCUS_KEY);
    }
#endif

#if LV_USE_KEYBOARD
    else if(lv_obj_check_type(obj, &lv_keyboard_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->card, LV_PART_ITEMS);
        lv_obj_add_style(obj, &binary_styles->pr, LV_PART_ITEMS | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_ITEMS | LV_STATE_CHECKED);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
        lv_obj_add_style(obj, &binary_styles->large_border, LV_PART_ITEMS | LV_STATE_EDITED);
    }
#endif
#if LV_USE_LIST
    // The List itself
    else if(lv_obj_check_type(obj, &lv_list_class)) {
        lv_obj_add_style(obj, &binary_styles->list, 0);
        lv_obj_add_style(obj, &binary_styles->list_scrollbar, LV_PART_SCROLLBAR);
    }
    // List Buttons itself
    else if(lv_obj_check_type(obj, &lv_list_btn_class)) {
        lv_obj_add_style(obj, &binary_styles->list_button, LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &binary_styles->list_button_focus, LV_STATE_FOCUSED | LV_STATE_FOCUS_KEY);
        //lv_obj_add_style(obj, &binary_styles->pr, LV_STATE_PRESSED);        
        //lv_obj_add_style(obj, &binary_styles->large_border, LV_STATE_EDITED);
    }
    // List Buttons Text
    else if(lv_obj_check_type(obj, &lv_label_class) && lv_obj_check_type(parent, &lv_list_btn_class)) {
        lv_obj_add_style(obj, &binary_styles->slow_label, 0);
    }
    // List Text
    else if(lv_obj_check_type(obj, &lv_list_text_class)) {
    }
#endif
#if LV_USE_MSGBOX
    else if(lv_obj_check_type(obj, &lv_msgbox_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        return;
    }
#endif
#if LV_USE_SPINBOX
    else if(lv_obj_check_type(obj, &lv_spinbox_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
        lv_obj_add_style(obj, &binary_styles->inv, LV_PART_CURSOR);
        lv_obj_add_style(obj, &binary_styles->focus, LV_STATE_FOCUS_KEY);
        lv_obj_add_style(obj, &binary_styles->edit, LV_STATE_EDITED);
    }
#endif
#if LV_USE_TILEVIEW
    else if(lv_obj_check_type(obj, &lv_tileview_class)) {
        lv_obj_add_style(obj, &binary_styles->scr, 0);
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
    }
    else if(lv_obj_check_type(obj, &lv_tileview_tile_class)) {
        lv_obj_add_style(obj, &binary_styles->scrollbar, LV_PART_SCROLLBAR);
    }
#endif

#if LV_USE_LED
    else if(lv_obj_check_type(obj, &lv_led_class)) {
        lv_obj_add_style(obj, &binary_styles->card, 0);
    }
#endif
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void style_init_reset(lv_style_t * style)
{
    if(inited) {
        lv_style_reset(style);
    }
    else {
        lv_style_init(style);
    }
}

#endif
