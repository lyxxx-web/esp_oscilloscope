#ifndef _UI_H
#define _UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"


enum style_name {
    OUTLINE,
    SWITCH,
};

/**
 * @brief get custom initialized styles
 * @return pointer to the custom styles
 */
lv_style_t * get_custom_style(void);

/**
 * @param value_init slider vsup value after init
 */
void ui_set_vsup_range(int value_min, int value_max, int value_init);

void ui_set_sample_freq_range(int value_min, int value_max, int value_init);

void ui_set_sample_time_range(int value_min, int value_max, int value_init);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif