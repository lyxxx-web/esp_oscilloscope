#ifndef _UI_SCREEN_H
#define _UI_SCREEN_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int max;
    int min;
    int init_value;
} slider_range;

typedef struct {
    lv_chart_cursor_t * cursor1;
    lv_chart_cursor_t * cursor2;
} chart_cursor_t;

lv_obj_t * ui_screen_home_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif