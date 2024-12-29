/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <math.h>
#include "ui/ui.h"
#include "ui_screen.h"
#include "esp_log.h"
#define NUMPAD_CTRL_BTN_FLAGS (LV_BTNMATRIX_CTRL_NO_REPEAT | LV_BTNMATRIX_CTRL_CLICK_TRIG)
#define LABEL_ARRAY_SIZE    6
#define ui_panel_left_grow  1
#define ui_panel_disp_grow  4

#define ui_panel_left_mode_grow 3
#define ui_panel_left_param_grow 3
#define ui_panel_left_option_grow 2
#define PI 3.1415926535897932384626433832795f
#define CHART_HEIGHT    400
#define CHART_WIDTH     760
#define CUSTOM_WIDTH1   150
#define NUM_SAMPLES     1000 

/**********************
 *  STATIC VARIABLES
 **********************/
static const char *TAG = "ui_screen_home";
static lv_obj_t * ui_ScreenHome_PanelDisp_KbNumpad;
static lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[LABEL_ARRAY_SIZE];
static lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[LABEL_ARRAY_SIZE];
static lv_timer_t * g_timer_update;
static lv_coord_t y_points[NUM_SAMPLES];
static slider_range g_slider_vsup = {
    .max = 5000,
    .min = 0,
    .init_value = 3300,
};
static slider_range g_slider_ts = {
    .max = 6000,
    .min = 0,
    .init_value = 5000,
};
static slider_range g_slider_freq = {
    .max = 100000,
    .min = 50000,
    .init_value = 80000,
};
static const char * btnm_map[] = {"1", "2", "3", "\n",
                                    "4", "5", "6", "\n",
                                    "7", "8", "9", "\n",
                                    LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_OK, ""};

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void generate_sine_wave(lv_coord_t *y_points);
static void format_textarea_string(int min_value, int max_value, char * input_str, size_t buf_size);
static uint8_t detect_touch_cursor(int32_t pos_id, lv_chart_cursor_t * cursor1, lv_chart_cursor_t * cursor2);
static void add_chart_data_cb(lv_timer_t * t);

static void ui_event_chart_cb(lv_event_t * e);
static void ui_event_textarea_cb(lv_event_t * e);
static void ui_event_kbnumpad_cb(lv_event_t * e);
static void ui_event_screen_home_cb(lv_event_t * e);
static void ui_event_slider_voltage_cb(lv_event_t * e);
static void ui_event_slider_samp_freq_cb(lv_event_t * e);
static void ui_event_slider_samp_time_cb(lv_event_t * e);
static void ui_event_button_start_cb(lv_event_t * e);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void ui_set_vsup_range(int value_min, int value_max, int value_init) 
{
    g_slider_vsup.min = value_min;
    g_slider_vsup.max = value_max;
    g_slider_vsup.init_value = value_init;
}

void ui_set_sample_freq_range(int value_min, int value_max, int value_init) 
{
    g_slider_freq.min = value_min;
    g_slider_freq.max = value_max;
    g_slider_freq.init_value = value_init;
}

void ui_set_sample_time_range(int value_min, int value_max, int value_init) 
{
    g_slider_ts.min = value_min;
    g_slider_ts.max = value_max;
    g_slider_ts.init_value = value_init;
}

void ui_set_calc_param(param_packge_t windows_param, param_packge_t select_param)
{
    if (windows_param.current_average_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[0], "%d\nmA\nAverage", windows_param.current_average);
    else lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[0], "%d\nuA\nAverage", windows_param.current_average);
    if (windows_param.current_max_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[1], "%d\nmA\nMax", windows_param.current_max);
    else lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[1], "%d\nuA\nMax", windows_param.current_max);
    if (windows_param.current_min_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[2], "%d\nmA\nMin", windows_param.current_min);
    else lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[2], "%d\nuA\nMin", windows_param.current_min);
    if (windows_param.time_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[3], "%d\nsec\nTime", windows_param.time);
    else lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[3], "%d\nms\nTime", windows_param.time); 
    if (windows_param.power_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[4], "%d\nW\nPower", windows_param.power);
    else lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[4], "%d\nmW\nPower", windows_param.power);
    if (windows_param.energy_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[5], "%d\nmWh\nEnergy", windows_param.energy);
    else  lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[5], "%d\nuWh\nEnergy", windows_param.energy);

    if (select_param.current_average_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[0], "%d\nmA\nAverage", select_param.current_average);
    else lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[0], "%d\nuA\nAverage", select_param.current_average);
    if (select_param.current_max_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[1], "%d\nmA\nMax", select_param.current_max);
    else lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[1], "%d\nuA\nMax", select_param.current_max);
    if (select_param.current_min_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[2], "%d\nmA\nMin", select_param.current_min);
    else lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[2], "%d\nuA\nMin", select_param.current_min);
    if (select_param.time_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[3], "%d\nsec\nTime", select_param.time);
    else lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[3], "%d\nms\nTime", select_param.time); 
    if (select_param.power_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[4], "%d\nW\nPower", select_param.time);
    else lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[4], "%d\nmW\nPower", select_param.time);
    if (select_param.energy_unit)
        lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[5], "%d\nmWh\nEnergy", select_param.energy);
    else  lv_label_set_text_fmt(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[5], "%d\nuWh\nEnergy", select_param.energy);

}
/* Screen init */
lv_obj_t * ui_screen_home_init(void)
{
    lv_obj_t * ui_ScreenHome = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ui_ScreenHome, lv_color_hex(0x181818), 0);
    lv_obj_clear_flag(ui_ScreenHome, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_align(ui_ScreenHome, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_ScreenHome, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_column(ui_ScreenHome, 0, 0);
    // left panel in this screen
    lv_obj_t * ui_ScreenHome_PanelFunc = lv_obj_create(ui_ScreenHome);
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

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode = lv_obj_create(ui_ScreenHome_PanelFunc);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelMode, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelMode, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelFunc_PanelMode, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelMode, LV_SIZE_CONTENT);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelFunc_PanelMode, ui_panel_left_mode_grow);
    lv_obj_set_flex_align(ui_ScreenHome_PanelFunc_PanelMode, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_ScreenHome_PanelFunc_PanelMode, LV_FLEX_FLOW_COLUMN);

    lv_obj_t * ui_ScreenHome_PanelFunc_LabelTitle = lv_label_create(ui_ScreenHome_PanelFunc_PanelMode);
    lv_label_set_text(ui_ScreenHome_PanelFunc_LabelTitle, "MODE");
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_LabelTitle, &lv_font_montserrat_20, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_LabelTitle, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_DropdownMode = lv_dropdown_create(ui_ScreenHome_PanelFunc_PanelMode);
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

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelVsup = lv_obj_create(ui_ScreenHome_PanelFunc_PanelMode);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_hor(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, 0, 0);
    lv_obj_set_style_pad_ver(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, 7, 0);
    // lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup, CUSTOM_WIDTH1);

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle = lv_label_create(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup);
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle, "Vsup(mv):");
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle, &lv_font_montserrat_14, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle, LV_ALIGN_LEFT_MID);
    
    lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup = lv_textarea_create(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup);
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

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_SliderVsup = lv_slider_create(ui_ScreenHome_PanelFunc_PanelMode);
    lv_slider_set_range(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, g_slider_vsup.min, g_slider_vsup.max);
    lv_slider_set_value(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, g_slider_vsup.init_value, LV_ANIM_OFF);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, CUSTOM_WIDTH1);
    lv_obj_set_height(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, 10);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, lv_color_hex(0X455A64), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelOutput = lv_obj_create(ui_ScreenHome_PanelFunc_PanelMode);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_left(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_set_style_pad_right(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_set_style_pad_top(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 10, 0);
    lv_obj_set_style_pad_bottom(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput, 0, 0);
    lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_LabelTitle = lv_label_create(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_LabelTitle, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_LabelTitle, "P.O. Output");
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, &lv_font_montserrat_14, 0);
    lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_SwitchOp = lv_switch_create(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput);
    lv_obj_add_style(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_SwitchOp, get_custom_style(STYLE_SWITCH), 0);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_SwitchOp, LV_ALIGN_RIGHT_MID);

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam = lv_obj_create(ui_ScreenHome_PanelFunc);
    lv_obj_set_style_border_side(ui_ScreenHome_PanelFunc_PanelParam, LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_radius(ui_ScreenHome_PanelFunc_PanelParam, 0, 0);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelParam, 2, 0);
    lv_obj_set_style_border_color(ui_ScreenHome_PanelFunc_PanelParam, lv_color_hex(0x2B2B2B), 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelParam, 0, 0);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelParam, LV_SIZE_CONTENT);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelFunc_PanelParam, ui_panel_left_param_grow);
    lv_obj_set_flex_align(ui_ScreenHome_PanelFunc_PanelParam, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_ScreenHome_PanelFunc_PanelParam, LV_FLEX_FLOW_COLUMN);
    
    lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_LabelTitle = lv_label_create(ui_ScreenHome_PanelFunc_PanelParam);
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelParam_LabelTitle, "SAMPLING PARAMETERS");
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelParam_LabelTitle, &lv_font_montserrat_20, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelParam_LabelTitle, CUSTOM_WIDTH1, LV_SIZE_CONTENT);

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1 = lv_label_create(ui_ScreenHome_PanelFunc_PanelParam);
    lv_label_set_text_fmt(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, "SR(Hz):\t\t\t\t%d", g_slider_freq.init_value);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, &lv_font_montserrat_14, 0);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, LV_ALIGN_TOP_LEFT);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_hor(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, 0, 0);
    lv_obj_set_style_pad_ver(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, 7, 0);

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_SliderFreq = lv_slider_create(ui_ScreenHome_PanelFunc_PanelParam);
    lv_slider_set_range(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, g_slider_freq.min, g_slider_freq.max);
    lv_slider_set_value(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, g_slider_freq.init_value, LV_ANIM_OFF);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, CUSTOM_WIDTH1);
    lv_obj_set_height(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, 10);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, lv_color_hex(0X455A64), LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_PanelTs = lv_obj_create(ui_ScreenHome_PanelFunc_PanelParam);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, CUSTOM_WIDTH1, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_hor(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, 0, 0);
    lv_obj_set_style_pad_ver(ui_ScreenHome_PanelFunc_PanelParam_PanelTs, 7, 0);

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_PanelTs_LabelTitle = lv_label_create(ui_ScreenHome_PanelFunc_PanelParam_PanelTs);
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_LabelTitle, "Ts(sec):");
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_LabelTitle, &lv_font_montserrat_14, 0);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_LabelTitle, LV_ALIGN_LEFT_MID);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_LabelTitle, CUSTOM_WIDTH1, LV_SIZE_CONTENT);

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs = lv_textarea_create(ui_ScreenHome_PanelFunc_PanelParam_PanelTs);
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

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_SliderTs = lv_slider_create(ui_ScreenHome_PanelFunc_PanelParam);
    lv_slider_set_range(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, g_slider_ts.min, g_slider_ts.max);
    lv_slider_set_value(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, g_slider_ts.init_value, LV_ANIM_OFF);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, CUSTOM_WIDTH1);
    lv_obj_set_height(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, 10);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, lv_color_hex(0X455A64), LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelOption = lv_obj_create(ui_ScreenHome_PanelFunc);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelFunc_PanelOption, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelFunc_PanelOption, 0, 0);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelOption, LV_SIZE_CONTENT);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelFunc_PanelOption, ui_panel_left_option_grow);

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelOption_ButtonStart = lv_btn_create(ui_ScreenHome_PanelFunc_PanelOption);
    lv_obj_set_width(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart, CUSTOM_WIDTH1);
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_flag(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_style_shadow_width(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart, 0, 0);
    lv_obj_set_style_shadow_width(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    lv_obj_t * ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark = lv_label_create(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart);
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark, "START");
    lv_obj_set_align(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark, LV_ALIGN_CENTER);
    lv_obj_set_style_text_align(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark, &lv_font_montserrat_20, 0);
    lv_obj_set_size(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark, CUSTOM_WIDTH1, LV_SIZE_CONTENT);

    // disp area in this screen, in the right
    lv_obj_t * ui_ScreenHome_PanelDisp = lv_obj_create(ui_ScreenHome);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp, 0, 0);
    lv_obj_set_style_radius(ui_ScreenHome_PanelDisp, 0, 0);
    lv_obj_set_style_bg_color(ui_ScreenHome_PanelDisp, lv_color_hex(0x1F1F1F), 0);
    // lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp, 0, 0);
    lv_obj_set_height(ui_ScreenHome_PanelDisp, LV_VER_RES);
    lv_obj_set_flex_grow(ui_ScreenHome_PanelDisp, ui_panel_disp_grow);

    lv_obj_t * ui_ScreenHome_PanelDisp_ChartDisp = lv_chart_create(ui_ScreenHome_PanelDisp);
    lv_chart_set_update_mode(ui_ScreenHome_PanelDisp_ChartDisp, LV_CHART_UPDATE_MODE_SHIFT);
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
    lv_chart_set_point_count(ui_ScreenHome_PanelDisp_ChartDisp, NUM_SAMPLES);
    // lv_chart_set_zoom_x(ui_ScreenHome_PanelDisp_ChartDisp, 256 * 2);
    lv_chart_set_div_line_count(ui_ScreenHome_PanelDisp_ChartDisp, 6, 6);
    lv_chart_set_range(ui_ScreenHome_PanelDisp_ChartDisp, LV_CHART_AXIS_PRIMARY_Y, -120, 120);
    static chart_cursor_t chart_cusor;
    chart_cusor.cursor1 = lv_chart_add_cursor(ui_ScreenHome_PanelDisp_ChartDisp, lv_palette_main(LV_PALETTE_YELLOW), LV_DIR_LEFT | LV_DIR_BOTTOM);
    chart_cusor.cursor2 = lv_chart_add_cursor(ui_ScreenHome_PanelDisp_ChartDisp, lv_palette_main(LV_PALETTE_YELLOW), LV_DIR_LEFT | LV_DIR_BOTTOM);

    /*Prefill with data*/
    generate_sine_wave(y_points);
    lv_chart_series_t * ui_chart_series = lv_chart_add_series(ui_ScreenHome_PanelDisp_ChartDisp, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    for(size_t i = 0; i < NUM_SAMPLES; i++) {
        lv_chart_set_next_value(ui_ScreenHome_PanelDisp_ChartDisp, ui_chart_series, y_points[i]);
    }
    lv_chart_set_cursor_point(ui_ScreenHome_PanelDisp_ChartDisp, chart_cusor.cursor1, ui_chart_series, 200);
    lv_chart_set_cursor_point(ui_ScreenHome_PanelDisp_ChartDisp, chart_cusor.cursor2, ui_chart_series, 600);

    lv_chart_set_axis_tick(ui_ScreenHome_PanelDisp_ChartDisp, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 50);
    lv_chart_set_axis_tick(ui_ScreenHome_PanelDisp_ChartDisp, LV_CHART_AXIS_PRIMARY_X, 10, 5, 20, 5, true, 50);

    static lv_btnmatrix_ctrl_t default_kb_ctrl_num_map[] = {
        NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS,
        NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS,
        NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS,
        LV_BTNMATRIX_CTRL_CLICK_TRIG, NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS,
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
    lv_obj_t * ui_ScreenHome_PanelDisp_PanelData = lv_obj_create(ui_ScreenHome_PanelDisp);
    lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelWindow = lv_obj_create(ui_ScreenHome_PanelDisp_PanelData);
    lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelSelect = lv_obj_create(ui_ScreenHome_PanelDisp_PanelData);
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
    lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption = lv_obj_create(ui_ScreenHome_PanelDisp);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelOption, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_PanelOption, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp_PanelOption, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelDisp_PanelOption, 0, 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption, CHART_WIDTH, LV_SIZE_CONTENT);

    lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelLocky = lv_obj_create(ui_ScreenHome_PanelDisp_PanelOption);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, 0, 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, LV_ALIGN_LEFT_MID);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky, 135, LV_SIZE_CONTENT);

    lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_SwitchLocky = lv_switch_create(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky);
    lv_obj_add_style(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_SwitchLocky, get_custom_style(STYLE_SWITCH), 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_SwitchLocky, LV_ALIGN_LEFT_MID);

    lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle = lv_label_create(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky);
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle, "Lock axis-y");
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle, &lv_font_montserrat_14, 0);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle, lv_color_hex(0xFFFFFF), 0);

    lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelRtview = lv_obj_create(ui_ScreenHome_PanelDisp_PanelOption);
    lv_obj_set_style_border_width(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, 0, 0);
    lv_obj_set_style_bg_opa(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, 0, 0);
    lv_obj_clear_flag(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, 0, 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, LV_ALIGN_RIGHT_MID);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview, 160, LV_SIZE_CONTENT);

    lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_SwitchRtview = lv_switch_create(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview);
    lv_obj_add_style(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_SwitchRtview, get_custom_style(STYLE_SWITCH), 0);
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_SwitchRtview, LV_ALIGN_RIGHT_MID);

    lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview = lv_label_create(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview);
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview, "Real-time view");
    lv_obj_set_align(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_text_font(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview, &lv_font_montserrat_14, 0);
    lv_obj_set_size(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview, lv_color_hex(0xFFFFFF), 0);

    static const char * option_map[] = {"10 ms", "100 ms", "1 s", "3 s", "10 s", "1 min", ""};
    lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime = lv_btnmatrix_create(ui_ScreenHome_PanelDisp_PanelOption);
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
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[3], "--\nsec\nTime");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[4], "--\nmW\nPower");
    lv_label_set_text(ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[5], "--\nuWh\nEnergy");
    // set font color
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_LabelTitle, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelParam_LabelTitle, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_LabelTitle, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_LabelTitle, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(ui_ScreenHome_PanelFunc_PanelMode_DropdownMode, lv_color_hex(0xFFFFFF), 0);

    lv_obj_add_event_cb(ui_ScreenHome, ui_event_screen_home_cb, LV_EVENT_ALL, ui_ScreenHome_PanelDisp_ChartDisp);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, ui_event_slider_voltage_cb, LV_EVENT_VALUE_CHANGED, ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, ui_event_slider_samp_freq_cb, LV_EVENT_VALUE_CHANGED, ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, ui_event_slider_samp_time_cb, LV_EVENT_VALUE_CHANGED, ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs);
    lv_obj_add_event_cb(ui_ScreenHome_PanelDisp_KbNumpad, ui_event_kbnumpad_cb, LV_EVENT_ALL, ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, ui_event_textarea_cb, LV_EVENT_ALL, ui_ScreenHome_PanelFunc_PanelMode_SliderVsup);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelOption_ButtonStart, ui_event_button_start_cb, LV_EVENT_VALUE_CHANGED, ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, ui_event_textarea_cb, LV_EVENT_ALL, ui_ScreenHome_PanelFunc_PanelParam_SliderTs);
    lv_obj_add_event_cb(ui_ScreenHome_PanelDisp_ChartDisp, ui_event_chart_cb, LV_EVENT_ALL, &chart_cusor);

    return ui_ScreenHome;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void generate_sine_wave(lv_coord_t *y_points) 
{
    for (int i = 0; i < NUM_SAMPLES; i++) {
        y_points[i] = (lv_coord_t)(100 * sin(2 * PI * i / NUM_SAMPLES));
    }
}

static void add_chart_data_cb(lv_timer_t * t)
{
    lv_obj_t * chart = (lv_obj_t *)t->user_data;
    lv_chart_series_t * ser = lv_chart_get_series_next(chart, NULL);
    static int i = 0;
    lv_chart_set_next_value(chart, ser, y_points[i]);
    i++;
    if (i >= NUM_SAMPLES)
        i = 0;
    lv_chart_refresh(chart);
}

static void format_textarea_string(int min_value, int max_value, char * input_str, size_t buf_size)
{
    int i = 0;
    if (min_value > max_value) {
        ESP_LOGE(TAG, "format string variables: min_value more than max_value");
    }
    if (min_value < 0 || max_value < 0) {
        ESP_LOGE(TAG, "format string variables: min_value or max_value less than zero");
    }
    if (((int)log10(max_value) + 1) > buf_size) {
        ESP_LOGE(TAG, "format string input buf size not enough");
    }
    while (input_str[i] == '0') {
        i++;
    }
    if (input_str[i] == '\0') {
        snprintf(input_str, buf_size, "%d", min_value);
        return;
    }
    char * formatted_str = input_str + i;
    int value = atoi(formatted_str);
    if (value > max_value) {
        value = max_value;
    } else if (value < min_value) {
        value = min_value;
    }
    snprintf(input_str, buf_size, "%d", value);
}

static uint8_t detect_touch_cursor(int32_t pos_id, lv_chart_cursor_t * cursor1, lv_chart_cursor_t * cursor2)
{
    int32_t interval1 = abs(pos_id - cursor1->point_id);
    int32_t interval2 = abs(pos_id - cursor2->point_id);
    if (interval2 <=  10) {
        return 2;
    } else if (interval1 <=  10) {
        return 1;
    }
    return 0;
}

static void ui_event_chart_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * chart = lv_event_get_target(e);
    chart_cursor_t * chart_cursor = lv_event_get_user_data(e);
    static int id1 = -1;
    static int id2 = -1;
    static uint8_t set_cursor_flag = 0;
    static bool press_flag = 0;
    if (code == LV_EVENT_PRESSING) {
        // Detect which cursor is touched when first press
        if (!press_flag) {
            int32_t touch_id = lv_chart_get_pressed_point(chart);
            set_cursor_flag = detect_touch_cursor(touch_id, chart_cursor->cursor1, chart_cursor->cursor2);
            press_flag = true;
        }
        // Set the cursor position via param set_cursor_flag
        if (set_cursor_flag) {
            lv_indev_t * indev = lv_indev_get_act();
            if(indev == NULL)  return;
            lv_point_t vect;
            lv_indev_get_vect(indev, &vect);

            uint16_t point_count = lv_chart_get_point_count(chart);
            lv_coord_t width = lv_obj_get_width(chart);
            if (set_cursor_flag == 1) {
                int32_t last_id = chart_cursor->cursor1->point_id + vect.x * point_count / width;
                lv_chart_set_cursor_point(chart, chart_cursor->cursor1, NULL, last_id);
            } else {
                int32_t last_id = chart_cursor->cursor2->point_id + vect.x * point_count / width;
                lv_chart_set_cursor_point(chart, chart_cursor->cursor2, NULL, last_id);
            }     
        }
    }
    if (code == LV_EVENT_RELEASED) {
        // printf("released\n");
        press_flag = false;
    }
    if (code == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
        if(!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_CURSOR)) return;

        lv_chart_series_t * ser = lv_chart_get_series_next(chart, NULL);
        lv_coord_t * data_array = lv_chart_get_y_array(chart, ser);

        static int index = 0;//mark which cursor being painted
        // Adjust the data point_id based on the start_id
        id1 = chart_cursor->cursor1->point_id;
        id2 = chart_cursor->cursor2->point_id;
        uint16_t start_id = lv_chart_get_x_start_point(chart, ser);
        uint16_t point_count = lv_chart_get_point_count(chart);
        id1 = (id1 + start_id) %  point_count;
        id2 = (id2 + start_id) %  point_count;

        if(dsc->p1 == NULL || dsc->p2 == NULL || dsc->p1->y != dsc->p2->y || id1 < 0 || id2 < 0) return;

        lv_coord_t v1 = data_array[id1];
        lv_coord_t v2 = data_array[id2];

        char buf1[10], buf2[10];
        lv_snprintf(buf1, sizeof(buf1), "%d", v1);
        lv_snprintf(buf2, sizeof(buf2), "%d", v2);

        lv_point_t size1, size2;
        lv_txt_get_size(&size1, buf1, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);
        lv_txt_get_size(&size2, buf2, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

        lv_area_t a1,a2;
        a1.y2 = dsc->p1->y - 5;
        a1.y1 = a1.y2 - size1.y - 10;
        a1.x1 = dsc->p1->x + 10;
        a1.x2 = a1.x1 + size1.x + 10;
        a2.y2 = dsc->p1->y - 5;
        a2.y1 = a2.y2 - size2.y - 10;
        a2.x1 = dsc->p1->x + 10;
        a2.x2 = a2.x1 + size2.x + 10;

        lv_draw_rect_dsc_t draw_rect_dsc;
        lv_draw_rect_dsc_init(&draw_rect_dsc);
        draw_rect_dsc.bg_color = lv_palette_main(LV_PALETTE_BLUE);
        draw_rect_dsc.radius = 3;

        lv_area_t *cursor_area = (index == 0) ? &a1 : &a2;
        const char *cursor_text = (index == 0) ? buf1 : buf2;
        // Draw the rectangle for the cursor
        lv_draw_rect(dsc->draw_ctx, &draw_rect_dsc, cursor_area);

        lv_draw_label_dsc_t draw_label_dsc;
        lv_draw_label_dsc_init(&draw_label_dsc);
        draw_label_dsc.color = lv_color_white();
        cursor_area->x1 += 5;
        cursor_area->x2 -= 5;
        cursor_area->y1 += 5;
        cursor_area->y2 -= 5;
        // Draw the label for the cursor
        lv_draw_label(dsc->draw_ctx, &draw_label_dsc, cursor_area, cursor_text, NULL);

        // Update the index for the next cursor
        index = (index + 1) % 2;
    }
}

static void ui_event_textarea_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * slider = lv_event_get_user_data(e);
    if (code == LV_EVENT_PRESSED) {
        lv_obj_clear_flag(ui_ScreenHome_PanelDisp_KbNumpad, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_pos(ui_ScreenHome_PanelDisp_KbNumpad, 0, 0);
    }
    if(code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED) {
        // Focus on the clicked text area
        lv_keyboard_set_textarea(ui_ScreenHome_PanelDisp_KbNumpad, ta);
    } else if(code == LV_EVENT_READY) {
        const char *text = lv_textarea_get_text(ta);
        int value = atoi(text);
        lv_slider_set_value(slider, value, LV_ANIM_ON);
    }
}

static void ui_event_kbnumpad_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * kb = lv_event_get_target(e);
    lv_obj_t * ta_ts = lv_event_get_user_data(e);
    lv_obj_t * ta = lv_keyboard_get_textarea(kb);
    if(code == LV_EVENT_VALUE_CHANGED) {
        uint32_t id = lv_keyboard_get_selected_btn(kb);
        const char * txt = lv_keyboard_get_btn_text(kb, id);
        if(strcmp(txt, LV_SYMBOL_OK) == 0) {
            // Hidden numpad
            lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_state(kb, LV_STATE_FOCUSED);
            // Format string in the focused textarea
            size_t buf_size = 10;
            char buf[buf_size];
            const char * text = lv_textarea_get_text(ta);
            strncpy(buf, text, buf_size - 1);
            buf[buf_size - 1] = '\0';
            if (ta == ta_ts)
                format_textarea_string(g_slider_ts.min, g_slider_ts.max, buf, buf_size);
            else    format_textarea_string(g_slider_ts.min, g_slider_ts.max, buf, buf_size);
            lv_textarea_set_text(ta, buf);
            // Update slider value related
            lv_event_send(ta, LV_EVENT_READY, NULL);
        }
    }
    if(code == LV_EVENT_PRESSING) {
        lv_indev_t * indev = lv_indev_get_act();
        if(indev == NULL)  return;
        lv_point_t vect;
        lv_indev_get_vect(indev, &vect);
        // Move cursor when gesture in the area of numpad
        if (abs(vect.x) > 5){
            if(vect.x < -15)
                lv_textarea_cursor_left(ta);
            else if(vect.x > 15)
                lv_textarea_cursor_right(ta);
            lv_btnmatrix_ctrl_t new_kb_ctrl_num_map[] = {
                LV_BTNMATRIX_CTRL_DISABLED, LV_BTNMATRIX_CTRL_DISABLED, LV_BTNMATRIX_CTRL_DISABLED,
                LV_BTNMATRIX_CTRL_DISABLED, LV_BTNMATRIX_CTRL_DISABLED, LV_BTNMATRIX_CTRL_DISABLED,
                LV_BTNMATRIX_CTRL_DISABLED, LV_BTNMATRIX_CTRL_DISABLED, LV_BTNMATRIX_CTRL_DISABLED,
                LV_BTNMATRIX_CTRL_CLICK_TRIG, LV_BTNMATRIX_CTRL_DISABLED, NUMPAD_CTRL_BTN_FLAGS,
            };
            lv_keyboard_set_map(ui_ScreenHome_PanelDisp_KbNumpad, LV_KEYBOARD_MODE_NUMBER, btnm_map, new_kb_ctrl_num_map);
        }
    }
    if(code == LV_EVENT_RELEASED) {
        // Disable the button of numpad unless to accidental touch when gesture in the numpad
        lv_btnmatrix_ctrl_t new_kb_ctrl_num_map[] = {
            NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS,
            NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS,
            NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS,
            LV_BTNMATRIX_CTRL_CLICK_TRIG, NUMPAD_CTRL_BTN_FLAGS, NUMPAD_CTRL_BTN_FLAGS,
        };
        lv_keyboard_set_map(ui_ScreenHome_PanelDisp_KbNumpad, LV_KEYBOARD_MODE_NUMBER, btnm_map, new_kb_ctrl_num_map);
    }
}

static void ui_event_screen_home_cb(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * chart = lv_event_get_user_data(e);
    if (event_code == LV_EVENT_SCREEN_LOAD_START) {
        g_timer_update = lv_timer_create(add_chart_data_cb, 1, chart);
    }
}

static void ui_event_slider_voltage_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    lv_obj_t * ta = lv_event_get_user_data(e);
    char buf[20];
    snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(slider));
    lv_textarea_set_text(ta, buf);
}

static void ui_event_slider_samp_freq_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    lv_obj_t * ta = lv_event_get_user_data(e);
    char buf[20];
    snprintf(buf, sizeof(buf), "SR(Hz):\t\t\t\t%d", (int)lv_slider_get_value(slider));
    lv_label_set_text(ta, buf);
}

static void ui_event_slider_samp_time_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    lv_obj_t * ta = lv_event_get_user_data(e);
    char buf[20];
    snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(slider));
    lv_textarea_set_text(ta, buf);
}

static void ui_event_button_start_cb(lv_event_t * e)
{
    lv_obj_t * button = lv_event_get_target(e);
    lv_obj_t * button_mark = lv_event_get_user_data(e);
    printf("current state is %d\n", lv_obj_get_state(button));
    if (lv_obj_has_state(button, LV_STATE_CHECKED))
        lv_label_set_text(button_mark, "STOP");
    else lv_label_set_text(button_mark, "START");
}