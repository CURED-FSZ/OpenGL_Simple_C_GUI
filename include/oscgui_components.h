#pragma once
#include <oscgui_types.h>
#ifdef __cplusplus
extern "C" {
#endif

/* 按钮操作 */

/**
 * 创建按钮
 * @return 按钮指针
 */
oscgui_button *oscgui_button_create(float x, float y, float w, float h);

/**
 * 设置按钮字体
 * @param btn 按钮指针
 * @param font 字体指针
 */
void oscgui_button_set_font(const oscgui_button *btn, const oscgui_font *font);

/**
 * 获取按钮文字
 * @param btn 按钮指针
 * @param text 文本指针
 * @return 文字指针
 */
void oscgui_button_set_text(const oscgui_button *btn, const char *text);

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
    oscgui_click cb
);

/* 标签操作 */

/**
 *  创建标签
 * @param x 横坐标
 * @param y 纵坐标
 * @param w 宽度
 * @param h 高度
 * @return 标签指针
 */
oscgui_label *oscgui_label_create(float x, float y, float w, float h);

/**
 * 设置标签颜色
 * @param label 标签指针
 * @param color 颜色
 */
void oscgui_label_set_color(const oscgui_label *label, oscgui_color color);

/**
* 设置标签字体
* @param label 标签指针
* @param font 字体指针
*/
void oscgui_label_set_font(const oscgui_label *label, const oscgui_font *font);

/**
* 获取标签文字
* @param label 标签指针
* @param text 文本指针
* @return 文本指针
*/
void oscgui_label_set_text(const oscgui_label *label, const char *text);

/* 复选框操作 */

/**
 * 创建复选框
 * @param x 横坐标
 * @param y 纵坐标
 * @param w 宽度
 * @param h 高度
 * @return 复选框指针
 */
oscgui_checkbox *oscgui_checkbox_create(float x, float y, float w, float h);

/**
 * 设置复选框字体
 * @param checkbox 复选框指针
 * @param font 字体指针
 */
void oscgui_checkbox_set_font(const oscgui_checkbox *checkbox, const oscgui_font *font);

/**
 * 设置复选框文字
 * @param checkbox 复选框指针
 * @param text 文本指针
 */
void oscgui_checkbox_set_text(const oscgui_checkbox *checkbox, const char *text);

/**
 * 设置复选框颜色
 * @param checkbox 复选框指针
 * @param color 颜色
 */
void oscgui_checkbox_set_color(const oscgui_checkbox *checkbox, oscgui_color color);

/**
 * 获取复选框选中状态
 * @param checkbox 复选框指针
 * @return 选中状态
 */
int oscgui_checkbox_get_checked(const oscgui_checkbox *checkbox);

/* 组件转换 */

/**
 * 获取按钮对应的组件
 * @param btn 按钮指针
 * @return 组件指针
 */
oscgui_component *oscgui_button_as_component(const oscgui_button *btn);

/**
* 获取标签对应的组件
* @param label 标签指针
* @return 组件指针
*/
oscgui_component *oscgui_label_as_component(const oscgui_label *label);

/**
* 获取复选框对应的组件
* @param checkbox 复选框指针
* @return 组件指针
*/
oscgui_component *oscgui_checkbox_as_component(const oscgui_checkbox *checkbox);


#ifdef __cplusplus
}
#endif
