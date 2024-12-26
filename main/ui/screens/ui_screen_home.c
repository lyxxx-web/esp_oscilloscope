#include <stdio.h>
#include "ui/ui.h"
#include "ui_extend.h"
#define ui_panel_left_grow 1
#define ui_panel_disp_grow 4

#define ui_panel_left_mode_grow 3
#define ui_panel_left_param_grow 3
#define ui_panel_left_option_grow 2

#define VSUP_VALUE_INIT 3300
#define SPS_VALUE_INIT  70000
#define ST_VALUE_INIT   3500

#define CHART_HEIGHT    400
#define CHART_WIDTH     760
#define CUSTOM_WIDTH1 150

void ui_screen_home_init(void)
{
    ui_ScreenHome = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ui_ScreenHome, lv_color_hex(0x181818), 0);
    lv_obj_clear_flag(ui_ScreenHome, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_align(ui_ScreenHome, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_ScreenHome, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(ui_ScreenHome, 0, 0);
    // left panel in this screen
    ui_ScreenHome_PanelFunc = lv_obj_create(ui_ScreenHome);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc, 2, 0);
    lv_obj_set_style_border_color(ui_ScreenHome_PanelFunc, lv_color_hex(0x2B2B2B), 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelFunc, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_height(ui_ScreenHome_PanelFunc, LV_VER_RES);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelFunc, ui_panel_left_grow);
    lv_obj_set_flex_align(ui_ScreenHome_PanelFunc, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_ScreenHome_PanelFunc, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_top(ui_ScreenHome_PanelFunc, 0, 0);
    lv_obj_set_style_pad_bottom(ui_ScreenHome_PanelFunc, 0, 0);

    ui_ScreenHome_PanelFunc_PanelMode = lv_obj_create(ui_ScreenHome_PanelFunc);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelMode, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelMode, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelFunc_PanelMode, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelMode, LV_SIZE_CONTENT);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelFunc_PanelMode, ui_panel_left_mode_grow);
    lv_obj_set_flex_align(ui_ScreenHome_PanelFunc_PanelMode, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_ScreenHome_PanelFunc_PanelMode, LV_FLEX_FLOW_COLUMN);

    ui_ScreenHome_PanelFunc_LabelTitle = lv_label_create(ui_ScreenHome_PanelFunc_PanelMode);
    lv_label_set_text(ui_ScreenHome_PanelFunc_LabelTitle, "MODE");
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_LabelTitle, &lv_font_montserrat_20, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_LabelTitle, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    ui_ScreenHome_PanelFunc_PanelMode_DropdownMode = lv_dropdown_create(ui_ScreenHome_PanelFunc_PanelMode);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelMode_DropdownMode, 2, 0);
    lv_obj_set_style_border_color(ui_ScreenHome_PanelFunc_PanelMode_DropdownMode, lv_color_hex(0x3C3C3C), 0);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelFunc_PanelMode_DropdownMode, lv_color_hex(0x313131), 0);
    // lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelMode_DropdownMode, 0, 0);
    lv_obj_t * list = lv_dropdown_get_list(ui_ScreenHome_PanelFunc_PanelMode_DropdownMode);
    lv_obj_set_style_border_color(list, lv_color_hex(0x2B2B2B), 0);
    lv_obj_set_style_text_color(list, lv_color_hex(0XFFFFFF), 0);
    lv_obj_set_style_bg_color(list, lv_color_hex(0x1F1F1F), 0);
    lv_dropdown_set_options(ui_ScreenHome_PanelFunc_PanelMode_DropdownMode, "Mode one\nMode two\nMode three");
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelMode_DropdownMode, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelMode_DropdownMode, CUSTOM_WIDTH1);

    ui_ScreenHome_PanelFunc_PanelMode_PanelVsup = lv_obj_create(ui_ScreenHome_PanelFunc_PanelMode);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, 0, 0);
    // lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, CUSTOM_WIDTH1);

    ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle = lv_label_create(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup);
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle, "Vsup(mv):");
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle, &lv_font_montserrat_14, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle, LV_ALIGN_LEFT_MID);
    
    ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup = lv_textarea_create(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup);
    lv_obj_clear_flag(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, LV_OBJ_FLAG_SCROLLABLE);
    lv_textarea_set_one_line(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, true);
    lv_textarea_set_text(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, "3300");
    lv_textarea_set_cursor_click_pos(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, true);
    lv_textarea_set_max_length(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, 4);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, 0, 0);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, 0, 0);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_pad_bottom(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, 0, 0);
    lv_obj_set_style_pad_top(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, 0, 0);
    lv_obj_set_style_radius(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, 0, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, 70, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, LV_TEXT_DECOR_UNDERLINE, 0);
    // lv_obj_set_style_bg_color(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, lv_color_hex(0xFF0000), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_obj_set_style_border_color(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, lv_color_hex(0xFFFFFF), LV_PART_CURSOR | LV_STATE_FOCUSED);

    ui_ScreenHome_PanelFunc_PanelMode_SliderVsup = lv_slider_create(ui_ScreenHome_PanelFunc_PanelMode);
    lv_slider_set_range(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, 0, 6000);
    lv_slider_set_value(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, VSUP_VALUE_INIT, LV_ANIM_OFF);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, CUSTOM_WIDTH1);
    lv_obj_set_height(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, 10);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, lv_color_hex(0X455A64), LV_PART_KNOB | LV_STATE_DEFAULT);
    ui_ScreenHome_PanelFunc_PanelMode_PanelOutput = lv_obj_create(ui_ScreenHome_PanelFunc_PanelMode);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_left(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_set_style_pad_right(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_set_style_pad_top(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 10, 0);
    lv_obj_set_style_pad_bottom(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_LabelTitle = lv_label_create(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_LabelTitle, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_LabelTitle, "P.O. Output");
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, &lv_font_montserrat_14, 0);
    ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_SwitchOp = lv_switch_create(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput);
    lv_obj_add_style(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_SwitchOp, &style_switch, 0);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_SwitchOp, LV_ALIGN_RIGHT_MID);

    ui_ScreenHome_PanelFunc_PanelParam = lv_obj_create(ui_ScreenHome_PanelFunc);
    lv_obj_set_style_border_side(ui_ScreenHome_PanelFunc_PanelParam, LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_radius(ui_ScreenHome_PanelFunc_PanelParam, 0, 0);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelParam, 2, 0);
    lv_obj_set_style_border_color(ui_ScreenHome_PanelFunc_PanelParam, lv_color_hex(0x2B2B2B), 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelParam, 0, 0);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelParam, LV_SIZE_CONTENT);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelFunc_PanelParam, ui_panel_left_param_grow);
    lv_obj_set_flex_align(ui_ScreenHome_PanelFunc_PanelParam, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_ScreenHome_PanelFunc_PanelParam, LV_FLEX_FLOW_COLUMN);
    
    ui_ScreenHome_PanelFunc_PanelParam_LabelTitle = lv_label_create(ui_ScreenHome_PanelFunc_PanelParam);
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelParam_LabelTitle, "SAMPLING PARAMETERS");
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelParam_LabelTitle, &lv_font_montserrat_20, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelParam_LabelTitle, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1 = lv_label_create(ui_ScreenHome_PanelFunc_PanelParam);
    lv_label_set_text_fmt(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, "SR(Hz):\t\t\t\t%d", SPS_VALUE_INIT);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, &lv_font_montserrat_14, 0);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, LV_ALIGN_TOP_LEFT);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    ui_ScreenHome_PanelFunc_PanelParam_SliderFreq = lv_slider_create(ui_ScreenHome_PanelFunc_PanelParam);
    lv_slider_set_range(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, 50000, 100000);
    lv_slider_set_value(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, SPS_VALUE_INIT, LV_ANIM_OFF);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, CUSTOM_WIDTH1);
    lv_obj_set_height(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, 10);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, lv_color_hex(0X455A64), LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_ScreenHome_PanelFunc_PanelParam_PanelTs = lv_obj_create(ui_ScreenHome_PanelFunc_PanelParam);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, 0, 0);

    ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle2 = lv_label_create(ui_ScreenHome_PanelFunc_PanelParam_PanelTs);
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle2, "Ts(sec):");
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle2, &lv_font_montserrat_14, 0);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle2, LV_ALIGN_LEFT_MID);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle2, CUSTOM_WIDTH1, LV_SIZE_CONTENT);

    ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs = lv_textarea_create(ui_ScreenHome_PanelFunc_PanelParam_PanelTs);
    lv_obj_clear_flag(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, LV_OBJ_FLAG_SCROLLABLE);
    lv_textarea_set_one_line(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, true);
    lv_textarea_set_text(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, "3500");
    lv_textarea_set_cursor_click_pos(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, true);
    lv_textarea_set_max_length(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, 4);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, 0, 0);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, 0, 0);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_pad_bottom(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, 0, 0);
    lv_obj_set_style_pad_top(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, 0, 0);
    lv_obj_set_style_radius(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, 0, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, 70, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_decor(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, LV_TEXT_DECOR_UNDERLINE, 0);
    lv_obj_set_style_border_color(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, lv_color_hex(0xFFFFFF), LV_PART_CURSOR | LV_STATE_FOCUSED);

    ui_ScreenHome_PanelFunc_PanelParam_SliderTs = lv_slider_create(ui_ScreenHome_PanelFunc_PanelParam);
    lv_slider_set_range(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, 0, 4000);
    lv_slider_set_value(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, ST_VALUE_INIT, LV_ANIM_OFF);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, CUSTOM_WIDTH1);
    lv_obj_set_height(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, 10);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, lv_color_hex(0X455A64), LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_ScreenHome_PanelFunc_PanelOption = lv_obj_create(ui_ScreenHome_PanelFunc);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelOption, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelOption, 0, 0);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelOption, LV_SIZE_CONTENT);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelFunc_PanelOption, ui_panel_left_option_grow);

    ui_ScreenHome_PanelFunc_PanelOption_ButtonStart = lv_btn_create(ui_ScreenHome_PanelFunc_PanelOption);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart, CUSTOM_WIDTH1);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart, LV_ALIGN_CENTER);

    ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark = lv_label_create(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart);
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark, "Start");
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark, LV_ALIGN_CENTER);
    lv_obj_set_style_text_align(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark, &lv_font_montserrat_20, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark, CUSTOM_WIDTH1, LV_SIZE_CONTENT);

    // disp area in this screen, in the right
    ui_ScreenHome_PanelDisp = lv_obj_create(ui_ScreenHome);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp, 0, 0);
    lv_obj_set_style_radius(ui_ScreenHome_PanelDisp, 0, 0);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelDisp, lv_color_hex(0x1F1F1F), 0);
    // lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp, 0, 0);
    lv_obj_set_height(ui_ScreenHome_PanelDisp, LV_VER_RES);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelDisp, ui_panel_disp_grow);

    ui_ScreenHome_PanelDisp_ChartDisp = lv_chart_create(ui_ScreenHome_PanelDisp);
    lv_chart_set_update_mode(ui_ScreenHome_PanelDisp_ChartDisp, LV_CHART_UPDATE_MODE_SHIFT );
    // lv_obj_set_scroll_dir(ui_ScreenHome_PanelDisp_ChartDisp, LV_DIR_HOR);
    lv_obj_set_style_radius(ui_ScreenHome_PanelDisp_ChartDisp, 10, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_ChartDisp, 0, 0);
    lv_obj_set_style_line_color(ui_ScreenHome_PanelDisp_ChartDisp, lv_color_make(0x00, 0XFF, 0X00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_ScreenHome_PanelDisp_ChartDisp, LV_OPA_50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_dash_width(ui_ScreenHome_PanelDisp_ChartDisp, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_dash_gap(ui_ScreenHome_PanelDisp_ChartDisp, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_size(ui_ScreenHome_PanelDisp_ChartDisp, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui_ScreenHome_PanelDisp_ChartDisp, lv_color_hex(0xFFFFFF), LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_ChartDisp, CHART_WIDTH, CHART_HEIGHT);
    lv_obj_align(ui_ScreenHome_PanelDisp_ChartDisp, LV_ALIGN_RIGHT_MID, 0, -20);
    lv_chart_set_point_count(ui_ScreenHome_PanelDisp_ChartDisp, 80);
    lv_chart_set_zoom_x(ui_ScreenHome_PanelDisp_ChartDisp, 256 * 2);
    lv_chart_set_div_line_count(ui_ScreenHome_PanelDisp_ChartDisp, 6, 6);
    cursor1 = lv_chart_add_cursor(ui_ScreenHome_PanelDisp_ChartDisp, lv_palette_main(LV_PALETTE_YELLOW), LV_DIR_VER);
    cursor2 = lv_chart_add_cursor(ui_ScreenHome_PanelDisp_ChartDisp, lv_palette_main(LV_PALETTE_YELLOW), LV_DIR_VER);
    pos1.x = 10;
    pos1.y = 65;
    pos2.x = 180;
    pos2.y = 80;
    lv_chart_set_cursor_pos(ui_ScreenHome_PanelDisp_ChartDisp, cursor1, &pos1);
    lv_chart_set_cursor_pos(ui_ScreenHome_PanelDisp_ChartDisp, cursor2, &pos2);
    ui_chart_series = lv_chart_add_series(ui_ScreenHome_PanelDisp_ChartDisp, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_axis_tick(ui_ScreenHome_PanelDisp_ChartDisp, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 50);
    lv_chart_set_axis_tick(ui_ScreenHome_PanelDisp_ChartDisp, LV_CHART_AXIS_PRIMARY_X, 10, 5, 20, 5, true, 50);
    /*Prefill with data*/
    uint32_t i;
    for(i = 0; i < 80; i++) {
        lv_chart_set_next_value(ui_ScreenHome_PanelDisp_ChartDisp, ui_chart_series, lv_rand(10, 90));
    }

    static const char * btnm_map[] = {"1", "2", "3", "\n",
                                      "4", "5", "6", "\n",
                                      "7", "8", "9", "\n",
                                      LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_OK, ""};

    static const lv_btnmatrix_ctrl_t default_kb_ctrl_num_map[] = {
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
    };
    ui_ScreenHome_PanelDisp_KbNumpad = lv_keyboard_create(ui_ScreenHome_PanelDisp);
    lv_keyboard_set_map(ui_ScreenHome_PanelDisp_KbNumpad, LV_KEYBOARD_MODE_NUMBER, btnm_map, default_kb_ctrl_num_map);
    lv_keyboard_set_mode(ui_ScreenHome_PanelDisp_KbNumpad, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_align(ui_ScreenHome_PanelDisp_KbNumpad, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_KbNumpad, 250, 300);
    lv_obj_add_flag(ui_ScreenHome_PanelDisp_KbNumpad, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_radius(ui_ScreenHome_PanelDisp_KbNumpad, 5, 0);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_KbNumpad, 2, 0);
    lv_obj_set_style_border_color(ui_ScreenHome_PanelDisp_KbNumpad, lv_color_hex(0x2B2B2B), 0);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelDisp_KbNumpad, lv_color_hex(0x2B2B2B), 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_KbNumpad, LV_OPA_30, 0);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelDisp_KbNumpad, lv_color_hex(0x333333), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelDisp_KbNumpad, lv_color_hex(0xFFFFFF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_KbNumpad, LV_OPA_80, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelDisp_KbNumpad, &lv_font_montserrat_18, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // disp data show area
    ui_ScreenHome_PanelDisp_PanelData = lv_obj_create(ui_ScreenHome_PanelDisp);
    ui_ScreenHome_PanelDisp_PanelData_PanelWindow = lv_obj_create(ui_ScreenHome_PanelDisp_PanelData);
    ui_ScreenHome_PanelDisp_PanelData_PanelSelect = lv_obj_create(ui_ScreenHome_PanelDisp_PanelData);
    // disp data panel
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelData, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_PanelData, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp_PanelData, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelDisp_PanelData, 0, 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelData, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelData, CHART_WIDTH, LV_SIZE_CONTENT);
    lv_obj_set_flex_align(ui_ScreenHome_PanelDisp_PanelData, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_ScreenHome_PanelDisp_PanelData, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(ui_ScreenHome_PanelDisp_PanelData, 0, 5);

    // disp windows data panel
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, 2, 0);
    lv_obj_set_style_border_color(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, 4, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, 1);
    lv_obj_set_height(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, 70);
    lv_obj_set_flex_align(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, 0, 0);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelDisp_PanelData_PanelWindow, 0, 0);
    // disp select data panel
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, 2, 0);
    lv_obj_set_style_border_color(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_radius(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, 4, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, 1);
    lv_obj_set_height(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, 70);
    lv_obj_set_flex_align(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, 0, 0);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelDisp_PanelData_PanelSelect, 0, 0);
    for (size_t i = 0; i < LABEL_ARRAY_SIZE; i++) {
        ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[i] = lv_label_create(ui_ScreenHome_PanelDisp_PanelData_PanelWindow);
        lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[i], "test");
        lv_obj_set_style_text_font(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[i], &lv_font_montserrat_12, 0);
        lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[i], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_flex_grow(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[i], 1);
        lv_obj_set_style_text_color(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[i], lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_align(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[i], LV_TEXT_ALIGN_CENTER, 0);
        if (i < LABEL_ARRAY_SIZE - 1) {//add dividing line
            lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[i], 2, 0);
            lv_obj_set_style_border_color(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[i], lv_color_hex(0xFFFFFF), 0);
            lv_obj_set_style_border_side(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[i], LV_BORDER_SIDE_RIGHT, 0);
        }
    }
    for (size_t i = 0; i < LABEL_ARRAY_SIZE; i++) {
        ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[i] = lv_label_create(ui_ScreenHome_PanelDisp_PanelData_PanelSelect);
        lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[i], "test");
        lv_obj_set_style_text_font(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[i], &lv_font_montserrat_12, 0);
        lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[i], LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_flex_grow(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[i], 1);
        lv_obj_set_style_text_color(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[i], lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_align(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[i], LV_TEXT_ALIGN_CENTER, 0);
        if (i < LABEL_ARRAY_SIZE - 1) {//add dividing line    
            lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[i], 2, 0);
            lv_obj_set_style_border_color(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[i], lv_color_hex(0xFFFFFF), 0);
            lv_obj_set_style_border_side(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[i], LV_BORDER_SIDE_RIGHT, 0);
        }   
    }
    //disp top option area
    ui_ScreenHome_PanelDisp_PanelOption = lv_obj_create(ui_ScreenHome_PanelDisp);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelOption, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_PanelOption, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp_PanelOption, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelDisp_PanelOption, 0, 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption, CHART_WIDTH, LV_SIZE_CONTENT);
    // lv_obj_set_flex_align(ui_ScreenHome_PanelDisp_PanelOption, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    // lv_obj_set_flex_flow(ui_ScreenHome_PanelDisp_PanelOption, LV_FLEX_FLOW_ROW);
    // lv_obj_set_style_pad_column(ui_ScreenHome_PanelDisp_PanelOption, 0, 5);

    ui_ScreenHome_PanelDisp_PanelOption_PanelLocky = lv_obj_create(ui_ScreenHome_PanelDisp_PanelOption);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, 0, 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, LV_ALIGN_LEFT_MID);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, 135, LV_SIZE_CONTENT);

    ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_SwitchLocky = lv_switch_create(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky);
    lv_obj_add_style(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_SwitchLocky, &style_switch, 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_SwitchLocky, LV_ALIGN_LEFT_MID);

    ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle = lv_label_create(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky);
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle, "Lock axis-y");
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle, &lv_font_montserrat_14, 0);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle, lv_color_hex(0xFFFFFF), 0);

    ui_ScreenHome_PanelDisp_PanelOption_PanelRtview = lv_obj_create(ui_ScreenHome_PanelDisp_PanelOption);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, 0, 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, LV_ALIGN_RIGHT_MID);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, 160, LV_SIZE_CONTENT);

    ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_SwitchRtview = lv_switch_create(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview);
    lv_obj_add_style(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_SwitchRtview, &style_switch, 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_SwitchRtview, LV_ALIGN_RIGHT_MID);

    ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview = lv_label_create(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview);
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview, "Real-time view");
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview, &lv_font_montserrat_14, 0);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview, lv_color_hex(0xFFFFFF), 0);

    static const char * option_map[] = {"10 ms", "100 ms", "1 s", "3 s", "10 s", "1 min", ""};
    ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime = lv_btnmatrix_create(ui_ScreenHome_PanelDisp_PanelOption);
    lv_btnmatrix_set_map(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, option_map);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, 0, 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, 0, 0);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, 400, 40);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, 0, 0);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, lv_color_hex(0x313131), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, lv_color_hex(0xFFFFFF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, 6, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, 2, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime, lv_color_hex(0x3C3C3C), LV_PART_ITEMS | LV_STATE_DEFAULT);

    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[0], "--\nmA\nAverage");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[1], "--\nmA\nMax");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[2], "--\nuA\nMin");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[3], "--\nsec\nTime");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[4], "--\nmW\nPower");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[5], "--\nuWh\nEnergy");

    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[0], "--\nmA\nAverage");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[1], "--\nmA\nMax");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[2], "--\nuA\nMin");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[3], "--\ns\nTime");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[4], "--\nmW\nPower");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[5], "--\nuWh\nEnergy");
    // set font color
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_LabelTitle, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelParam_LabelTitle, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle2, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_LabelTitle, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelMode_DropdownMode, lv_color_hex(0xFFFFFF), 0);
}