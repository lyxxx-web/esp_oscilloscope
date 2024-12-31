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

} current_data_t;

typedef struct
{
    lv_coord_t cursor_start;
    lv_coord_t cursor_end;

} chart_cursor_interval_t;

/**
 * @param value_init slider vsup value after init
 */
void ui_set_vsup_range(int value_min, int value_max, int value_init);
void ui_set_sample_freq_range(int value_min, int value_max, int value_init);
void ui_set_sample_time_range(int value_min, int value_max, int value_init);

/**
 * @brief set the param data in the display_panel
 * @param windows_data current data caclculate between two cursors
 * @param select_data current data select by one cursor
 */
void ui_set_current_data(current_data_t windows_data, current_data_t select_data);

/**
 * @brief update the y_points buffer of chart then refresh chart
 */
void ui_chart_send_y_points(lv_coord_t * data_buffer, size_t buffer_size);

/**
 * @brief use external buffer as the y_points buffer
 */
void ui_chart_set_ext_y_array(lv_coord_t * ext_y_buffer, size_t buffer_size);

/**
 * @brief refresh chart data
 * @attention refresh data regularly if set external y array buffer
 */
void ui_chart_data_refresh(void);

/**
 * @brief get cursor point_id both start and end
 */
chart_cursor_interval_t ui_get_chart_window_start_end(void);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif