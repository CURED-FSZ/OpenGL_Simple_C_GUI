//
// Created by 冯帅真 on 2025/12/20.
//

#ifndef OPENGL_C_GUI_API_H
#define OPENGL_C_GUI_API_H

/* scGUI/api.h */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* =====================
       基础类型
       ===================== */

typedef struct {
    float x, y;
} oscgui_vec2;

typedef struct {
    float r, g, b, a;
} oscgui_color;

/* =====================
   前向声明（不透明）
   ===================== */

typedef struct oscgui_gui oscgui_gui;
typedef struct oscgui_component oscgui_component;
typedef struct oscgui_button oscgui_button;

/* =====================
   回调
   ===================== */

typedef void (*oscgui_click_cb)(oscgui_component *self);

/* =====================
   GUI
   ===================== */

oscgui_gui *oscgui_create(void);

void oscgui_destroy(oscgui_gui *gui);

void oscgui_update(oscgui_gui *gui,
                   oscgui_vec2 mouse_pos,
                   int mouse_down);

void oscgui_draw(oscgui_gui *gui);

/* =====================
   Button
   ===================== */

oscgui_button *oscgui_button_create(void);

void oscgui_button_destroy(oscgui_button *btn);

void oscgui_button_set_position(oscgui_button *btn, float x, float y);

void oscgui_button_set_size(oscgui_button *btn, float w, float h);

void oscgui_button_set_color(
    oscgui_button *btn,
    oscgui_color normal,
    oscgui_color hover,
    oscgui_color pressed
);

void oscgui_button_set_on_click(
    oscgui_button *btn,
    oscgui_click_cb cb
);

/* =====================
   Component（通用）
   ===================== */

oscgui_component *oscgui_as_component(oscgui_button *btn);

void oscgui_gui_add(oscgui_gui *gui, oscgui_component *c);

#ifdef __cplusplus
}
#endif


#endif //OPENGL_C_GUI_API_H
