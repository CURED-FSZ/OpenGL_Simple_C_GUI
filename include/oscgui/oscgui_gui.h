#pragma once
#include <oscgui/oscgui_types.h>
#ifdef __cplusplus
extern "C" {
#endif
/**
* 创建 GUI
* @param native_window 窗口指针
* @return GUI 指针
*/
oscgui_gui *oscgui_gui_create(void *native_window);

/**
* 销毁 GUI
* @param gui GUI 指针
*/
void oscgui_gui_destroy(const oscgui_gui *gui);

/**
* 添加组件
* @param gui GUI 指针
* @param comp 组件指针
*/
void oscgui_gui_add(const oscgui_gui *gui, oscgui_component *comp);

/**
* 更新 GUI
* @param gui GUI 指针
*/
void oscgui_gui_update(const oscgui_gui *gui);

/**
* 绘制 GUI
* @param gui GUI 指针
*/
void oscgui_gui_draw(oscgui_gui *gui);

#ifdef __cplusplus
}
#endif
