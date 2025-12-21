#pragma once
#ifdef __cplusplus
extern "C" {
#endif

typedef struct oscgui_gui oscgui_gui;
typedef struct oscgui_component oscgui_component;
typedef struct oscgui_button oscgui_button;

typedef struct {
    float x, y;
} oscgui_vec2;

typedef struct {
    float r, g, b, a;
} oscgui_color;

typedef void (*oscgui_click_cb)(oscgui_component *self);

#ifdef __cplusplus
}
#endif
