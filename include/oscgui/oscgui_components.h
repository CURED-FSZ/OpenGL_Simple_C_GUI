#pragma once
#include <oscgui/oscgui_types.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * 创建按钮
 * @return 按钮指针
 */
oscgui_button *oscgui_button_create(void);

/**
 * 销毁按钮
 * @param btn 按钮指针
 */
void oscgui_button_destroy(const oscgui_button *btn);

/**
 * 设置按钮位置
 * @param btn 按钮指针
 * @param x x轴位置
 * @param y y轴位置
 */
void oscgui_button_set_position(const oscgui_button *btn, float x, float y);

/**
 * 设置按钮大小
 * @param btn 按钮指针
 * @param w 宽度
 * @param h 高度
 */
void oscgui_button_set_size(const oscgui_button *btn, float w, float h);

/**
 * 设置按钮颜色
 * @param btn 按钮指针
 * @param normal 正常颜色
 * @param hover 悬停颜色
 * @param pressed 按下颜色
 */
void oscgui_button_set_color(
    const oscgui_button *btn,
    oscgui_color normal,
    oscgui_color hover,
    oscgui_color pressed
);

/**
 * 设置按钮点击回调
 * @param btn 按钮指针
 * @param cb 点击回调
 */
void oscgui_button_set_on_click(
    const oscgui_button *btn,
    oscgui_click_cb cb
);

/**
 * 获取按钮对应的组件
 * @param btn 按钮指针
 * @return 组件指针
 */
oscgui_component *oscgui_as_component(const oscgui_button *btn);

#ifdef __cplusplus
}
#endif
