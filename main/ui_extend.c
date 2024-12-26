#include <stdio.h>
#include "esp_log.h"
#include "ui/ui.h"

lv_timer_t * timer_update;
// just for test the chart show
static void add_data(lv_timer_t * t)
{
    lv_obj_t * chart = (lv_obj_t *)t->user_data;
    lv_chart_series_t * ser = lv_chart_get_series_next(chart, NULL);

    lv_chart_set_next_value(chart, ser, lv_rand(10, 90));

    // uint16_t p = lv_chart_get_point_count(chart);
    // uint16_t s = lv_chart_get_x_start_point(chart, ser);
    // printf("s:%d\n", s);
    // int32_t * a = lv_chart_get_y_array(chart, ser);

    // a[(s + 1) % p] = LV_CHART_POINT_NONE;
    // a[(s + 2) % p] = LV_CHART_POINT_NONE;

    lv_chart_refresh(chart);
}
// event callback
void ui_event_textarea(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_PRESSED) {
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_pos(kb, 0, 0);
    }
    if(code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED) {
        /*Focus on the clicked text area*/
        lv_keyboard_set_textarea(kb, ta);
        // printf("focus on this pressed textarea\n");
    } else if(code == LV_EVENT_READY) {
        LV_LOG_USER("Ready, current text: %s", lv_textarea_get_text(ta));
    }
}
void ui_event_numpad_custom(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        uint32_t id = lv_keyboard_get_selected_btn(obj);
        const char * txt = lv_keyboard_get_btn_text(obj, id);
        if(strcmp(txt, LV_SYMBOL_OK) == 0) {
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_state(obj, LV_STATE_FOCUSED);
        }
    }
    if(code == LV_EVENT_PRESSING) {
        lv_indev_t * indev = lv_indev_get_act();
        if(indev == NULL)  return;
        lv_point_t vect;
        lv_indev_get_vect(indev, &vect);

        // lv_obj_t * ta = lv_keyboard_get_textarea(obj);
        // if(ta == NULL) return;
        // else {
        //     int32_t index = lv_textarea_get_cursor_pos(ta);
        //     if(vect.y > 3){
        //         lv_textarea_set_cursor_pos(ta, (index + 1) > 4 ? 4 : index ++);
        //     }else if (vect.y < -3){
        //         lv_textarea_set_cursor_pos(ta, (index - 1) < 0 ? 0 : index --);
        //     }
        // }
        // int32_t x = lv_obj_get_x_aligned(obj) + vect.x;
        // int32_t y = lv_obj_get_y_aligned(obj) + vect.y;
        // lv_obj_set_pos(obj, x, y);
    }
}
void ui_event_screen_home(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_SCREEN_LOAD_START) {
        timer_update = lv_timer_create(add_data, 300, ui_ScreenHome_PanelDisp_ChartDisp);
    }
}
void ui_event_slider_voltage(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * slider = lv_event_get_target(e);
    char buf[20];
    snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(slider));
    lv_textarea_set_text(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, buf);
}
void ui_event_slider_samp_freq(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * slider = lv_event_get_target(e);
    char buf[20];
    snprintf(buf, sizeof(buf), "SR(Hz):\t\t\t\t%d", (int)lv_slider_get_value(slider));
    lv_label_set_text(ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1, buf);
}
void ui_event_slider_samp_time(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * slider = lv_event_get_target(e);
    char buf[20];
    snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(slider));
    lv_textarea_set_text(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, buf);
}
void ui_extend_init(void)
{
    lv_obj_add_event_cb(ui_ScreenHome, ui_event_screen_home, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelMode_SliderVsup, ui_event_slider_voltage, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelParam_SliderFreq, ui_event_slider_samp_freq, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelParam_SliderTs, ui_event_slider_samp_time, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_ScreenHome_PanelDisp_KbNumpad, ui_event_numpad_custom, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup, ui_event_textarea, LV_EVENT_ALL, ui_ScreenHome_PanelDisp_KbNumpad);
    lv_obj_add_event_cb(ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs, ui_event_textarea, LV_EVENT_ALL, ui_ScreenHome_PanelDisp_KbNumpad);
    lv_event_send(ui_ScreenHome, LV_EVENT_SCREEN_LOAD_START, NULL);//send event manually after register ui_event_screen_home
}
