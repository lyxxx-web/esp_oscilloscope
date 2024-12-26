#include <stdio.h>
#include "esp_log.h"
#include "ui/ui.h"
#include "ui_screen.h"

#define STYLE_ARRAY_SIZE 2
static const char *TAG = "ui";
static lv_style_t g_style_array[STYLE_ARRAY_SIZE];

static void custom_style_init(void);

//////////////// GLOBAL FUNCTION ////////////////
lv_style_t * get_custom_style(void)
{
    return g_style_array;
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
//////////////// STATIC FUNCTION ////////////////
static void custom_style_init(void)
{
    lv_style_init(&g_style_array[OUTLINE]);
    lv_style_set_outline_color(&g_style_array[OUTLINE], lv_color_hex(0xFB7503));
    lv_style_set_outline_width(&g_style_array[OUTLINE], 4);

    lv_style_set_width(&g_style_array[SWITCH], 45);
    lv_style_set_height(&g_style_array[SWITCH], 25);
    lv_style_set_bg_opa(&g_style_array[SWITCH], 0);
    lv_style_set_border_color(&g_style_array[SWITCH], lv_color_hex(0x3C3C3C));
    lv_style_set_border_width(&g_style_array[SWITCH], 2);
}