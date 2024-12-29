#ifndef _UI_H
#define _UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

enum {
    STYLE_OUTLINE,
    STYLE_SWITCH,
};
typedef uint8_t lv_style_name_t;

/**
 * @brief get custom initialized styles
 * @return pointer to the custom styles
 */
lv_style_t * get_custom_style(lv_style_name_t style_name);

typedef struct
{
    int current_average;
    int current_max;
    int current_min;
    int time;//sec
    int power;
    int energy;
    uint8_t current_average_unit: 1;/*1: unit set to mA; 0: uint set to uA*/
    uint8_t current_max_unit: 1;/*1: unit set to mA; 0: uint set to uA*/
    uint8_t current_min_unit: 1;/*1: unit set to mA; 0: uint set to uA*/
    uint8_t time_unit: 1;/*1: unit set to sec; 0: uint set to ms*/
    uint8_t power_unit: 1;/*1: unit set to W; 0: uint set to mW*/
    uint8_t energy_unit: 1;/*1: unit set to mWh; 0: uint set to uWh*/

} param_packge_t;

/**
 * @param value_init slider vsup value after init
 */
void ui_set_vsup_range(int value_min, int value_max, int value_init);
void ui_set_sample_freq_range(int value_min, int value_max, int value_init);
void ui_set_sample_time_range(int value_min, int value_max, int value_init);

/**
 * @brief set the param data in the display_panel
 * @param windows_param current data caclculate between two cursors
 * @param select_param current data select by one cursor
 */
void ui_set_calc_param(param_packge_t windows_param, param_packge_t select_param);
void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif