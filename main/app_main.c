#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_check.h"

#include "bsp/esp-bsp.h"
#include "bsp/display.h"
#include "ui/ui.h"

static const char *TAG = "main";

#define CUSTOM_CONFIG() \
    {                               \
        .task_priority = 4,       \
        .task_stack = 6144,       \
        .task_affinity = -1,      \
        .task_max_sleep_ms = 500, \
        .timer_period_ms = 5,     \
    }

esp_err_t app_animation_start(void)
{
    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = CUSTOM_CONFIG(),
        .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags = {
            .buff_dma = true,
            .buff_spiram = false,
            .sw_rotate = true,
        }
    };
    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();

    /* Add and show objects on display*/
    bsp_display_lock(0);
    ui_init();
    bsp_display_unlock();
    return ESP_OK;
}
void app_main(void)
{
    app_animation_start();
    //test show
    param_packge_t data_window ={
        .current_average = 200,
        .current_max = 400,
        .current_min = 100,
        .time = 20,
        .power = 34,
        .energy = 55,
        .current_average_unit = 1,
        .current_max_unit = 1,
        .current_min_unit = 0,
        .energy_unit = 1,
        .power_unit = 0,
        .time_unit = 1
    };
    param_packge_t data_select ={
        .current_average = 200,
        .current_max = 400,
        .current_min = 100,
        .time = 20,
        .power = 34,
        .energy = 55,
        .current_average_unit = 1,
        .current_max_unit = 1,
        .current_min_unit = 0,
        .energy_unit = 1,
        .power_unit = 0,
        .time_unit = 1
    };
    ui_set_calc_param(data_window, data_select);
}
