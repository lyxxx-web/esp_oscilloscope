#ifndef _UI_EXTEND_H
#define _UI_EXTEND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct{
    lv_btnmatrix_t btnm;
    lv_obj_t * ta;
} lv_numpad_t;

void ui_extend_init(void);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif