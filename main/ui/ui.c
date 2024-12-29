/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "esp_log.h"
#include "ui/ui.h"
#include "ui_screen.h"

/*********************
 *      DEFINES
 *********************/
#define STYLE_ARRAY_SIZE 2

/**********************
 *  STATIC VARIABLES
 **********************/
static const char *TAG = "ui";
static lv_style_t g_style_array[STYLE_ARRAY_SIZE];

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void custom_style_init(void);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
lv_style_t * get_custom_style(lv_style_name_t style_name)
{
    return g_style_array + style_name;
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    custom_style_init();
    lv_obj_t * screen_home = ui_screen_home_init();
    lv_disp_load_scr(screen_home);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void custom_style_init(void)
{
    lv_style_init(get_custom_style(STYLE_OUTLINE));
    lv_style_set_outline_color(get_custom_style(STYLE_OUTLINE), lv_color_hex(0xFB7503));
    lv_style_set_outline_width(get_custom_style(STYLE_OUTLINE), 4);

    lv_style_set_width(get_custom_style(STYLE_SWITCH), 45);
    lv_style_set_height(get_custom_style(STYLE_SWITCH), 25);
    lv_style_set_bg_opa(get_custom_style(STYLE_SWITCH), 0);
    lv_style_set_border_color(get_custom_style(STYLE_SWITCH), lv_color_hex(0x3C3C3C));
    lv_style_set_border_width(get_custom_style(STYLE_SWITCH), 2);
}