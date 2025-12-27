#pragma once
#ifdef __cplusplus
extern "C" {
#endif

// 组件
typedef struct oscgui_component oscgui_component;

// 按钮
typedef struct oscgui_button oscgui_button;

// 标签
typedef struct oscgui_label oscgui_label;

// 复选框
typedef struct oscgui_checkbox oscgui_checkbox;

// 窗口
typedef struct oscgui_window oscgui_window;

// 应用
typedef struct oscgui_app oscgui_app;

// GUI
typedef struct oscgui_gui oscgui_gui;

// 字体
typedef struct oscgui_font oscgui_font;

// 点击回调
typedef void (*oscgui_click)();

// 初始化 GUI 回掉
typedef void (*oscgui_init_gui)(const oscgui_gui *gui, const oscgui_font *font);

// 二维向量
typedef struct {
    float x, y;
} oscgui_vec2;

// 颜色
typedef struct {
    float r, g, b, a;
} oscgui_color;

#ifdef __cplusplus
}
#endif
