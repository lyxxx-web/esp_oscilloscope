#ifndef _UI_H
#define _UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#define LABEL_ARRAY_SIZE    6
void ui_screen_home_init(void);
extern lv_style_t style_outline;
extern lv_style_t style_switch;
extern lv_obj_t * ui_ScreenHome;
extern lv_obj_t * ui_ScreenHome_PanelDisp;
extern lv_obj_t * ui_ScreenHome_PanelFunc;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelOption;

extern lv_obj_t * ui_ScreenHome_PanelFunc_LabelTitle;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_TextareaVsup;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_DropdownMode;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelOutput;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_LabelTitle;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelOutput_SwitchOp;

extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_SliderVsup;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_LabelTitle;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle1;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_LabelSubtitle2;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_SliderFreq;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_SliderTs;
extern lv_obj_t * ui_ScreenHome_PanelDisp_ChartDisp;
extern lv_chart_series_t * ui_chart_series;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelOption_ButtonStart;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelOption_ButtonStart_LabelMark;
extern lv_obj_t * ui_ScreenHome_PanelDisp_KbNumpad;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelVsup;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelMode_PanelVsup_LabelTitle;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_PanelTs;
extern lv_obj_t * ui_ScreenHome_PanelFunc_PanelParam_PanelTs_TextareaTs;

extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelData;
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelWindow;
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelSelect;
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelWindow_LabelContent[6];
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelData_PanelSelect_LabelContent[6];

extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption;
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelLocky;
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelRtview;
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_SwitchRtview;
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_SwitchLocky;
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelLocky_LabelTitle;
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_PanelRtview_LableRtview;
extern lv_obj_t * ui_ScreenHome_PanelDisp_PanelOption_BtnmatrixTime;
extern lv_chart_cursor_t * cursor1;
extern lv_chart_cursor_t * cursor2;
extern lv_point_t pos1;
extern lv_point_t pos2;
// extern lv_chart_cursor_t * cursor2;
void ui_event_screen_home(lv_event_t * e);
void ui_event_slider_voltage(lv_event_t * e);
void ui_event_slider_samp_freq(lv_event_t * e);
void ui_event_slider_samp_time(lv_event_t * e);
void ui_event_numpad_custom(lv_event_t * e);
void ui_event_textarea(lv_event_t * e);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif