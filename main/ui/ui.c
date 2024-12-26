#include <stdio.h>
#include "esp_log.h"
#include "ui/ui.h"

lv_style_t style_outline;
lv_style_t style_switch;
lv_obj_t * ui_ScreenHome;
lv_obj_t * ui_ScreenHome_PanelDisp;
lv_obj_t * ui_panel_title;
lv_obj_t * ui_ScreenHome_PanelFunc;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelOption;

lv_obj_t * ui_ScreenHome_PanelFunc_LabelTitle;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup;

lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_DropdownMode;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_SliderVsup;

lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelOutput;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_LabelTitle;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_SwitchOp;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_LabelTitle;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle2;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_SliderFreq;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_SliderTs;
lv_obj_t * ui_ScreenHome_PanelDisp_ChartDisp;
lv_chart_series_t * ui_chart_series;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelOption_ButtonStart;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark;
lv_obj_t * ui_ScreenHome_PanelDisp_KbNumpad;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelVsup;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_PanelTs;
lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs;

lv_obj_t * ui_ScreenHome_PanelDisp_PanelData;
lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelWindow;
lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelSelect; 
lv_obj_t * ui_label_window_ave;
lv_obj_t * ui_label_window_currentmax;
lv_obj_t * ui_label_window_currentmin;
lv_obj_t * ui_label_window_time;
lv_obj_t * ui_label_window_power;
lv_obj_t * ui_label_select_ave;
lv_obj_t * ui_label_select_currentmax;
lv_obj_t * ui_label_select_currentmin;
lv_obj_t * ui_label_select_time;
lv_obj_t * ui_label_select_power;
lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[LABEL_ARRAY_SIZE];
lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[LABEL_ARRAY_SIZE];

lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption;
lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelLocky;
lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelRtview;
lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_SwitchRtview;
lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_SwitchLocky;
lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle;
lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview;
lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime;
lv_chart_cursor_t * cursor1;
lv_chart_cursor_t * cursor2;
lv_point_t pos1;
lv_point_t pos2;
static const char *TAG = "ui";

void custom_style_init(void)
{
    lv_style_init(&style_outline);
    lv_style_set_outline_color(&style_outline, lv_color_hex(0xFB7503));
    lv_style_set_outline_width(&style_outline, 4);

    lv_style_set_width(&style_switch, 45);
    lv_style_set_height(&style_switch, 25);
    lv_style_set_bg_opa(&style_switch, 0);
    lv_style_set_border_color(&style_switch, lv_color_hex(0x3C3C3C));
    lv_style_set_border_width(&style_switch, 2);
}
void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    custom_style_init();
    ui_screen_home_init();
    lv_disp_load_scr(ui_ScreenHome);
}
