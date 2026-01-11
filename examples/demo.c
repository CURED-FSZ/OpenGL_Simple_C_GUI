//
// Created by 冯帅真 on 2025/12/20.
//
#include <oscgui_app.h>
#include <oscgui_types.h>
#include <oscgui_components.h>
#include <oscgui_gui.h>

oscgui_app *app; // 创建App对象
oscgui_button *btn1; // 创建按钮对象1
oscgui_button *btn2; // 创建按钮对象2
oscgui_label *label; // 创建标签对象
oscgui_checkbox *checkbox; // 创建复选框对象

// 按钮点击事件处理函数
void click() {
    if (checkbox && oscgui_checkbox_get_checked(checkbox)) oscgui_button_set_text(btn2, "checkbox save you!");
    else oscgui_button_set_text(btn2, "I was clicked!");
}
void click2() {
    oscgui_button_set_text(btn2, "");
}
void init_gui(const oscgui_gui *gui, const oscgui_font *font) {
    // 创建按钮1 - 位置(100, 100), 尺寸(200, 80)
    btn1 = oscgui_button_create(100, 100, 200, 80);
    oscgui_button_set_color(btn1,
                            (oscgui_color){0.8f, 0.8f, 0.8f, 1.0f}, // light_gray
                            (oscgui_color){0.5f, 0.5f, 0.5f, 1.0f}, // gray
                            (oscgui_color){0.3f, 0.3f, 0.3f, 1.0f}  // dark_gray
    );
    oscgui_button_set_text_color(btn1, (oscgui_color){0.0f, 0.0f, 0.0f, 1.0f}); // black
    oscgui_button_set_on_click(btn1, click);
    oscgui_button_set_font(btn1, font);
    oscgui_button_set_text(btn1, "Click me!");
    // 创建按钮2 - 位置(300, 300), 尺寸(300, 80)
    btn2 = oscgui_button_create(300, 300, 300, 80);
    oscgui_button_set_color(btn2,
                            (oscgui_color){0.8f, 0.8f, 0.8f, 1.0f}, // light_gray
                            (oscgui_color){0.5f, 0.5f, 0.5f, 1.0f}, // gray
                            (oscgui_color){0.3f, 0.3f, 0.3f, 1.0f}  // dark_gray
    );
    oscgui_button_set_text_color(btn2, (oscgui_color){1.0f, 0.0f, 1.0f, 1.0f}); // magenta
    oscgui_button_set_on_click(btn2, click2);
    oscgui_button_set_font(btn2, font);
    // 创建标签 - 位置(100, 300), 尺寸(200, 80)
    label = oscgui_label_create(100, 300, 200, 80);
    oscgui_label_set_text_color(label, (oscgui_color){0.8f, 0.8f, 0.8f, 1.0f}); // light_gray
    oscgui_label_set_font(label, font);
    oscgui_label_set_text(label, "I'm a label!");
    // 创建复选框 - 位置(370, 100), 尺寸(350, 150)
    checkbox = oscgui_checkbox_create(370, 100, 350, 150);
    oscgui_checkbox_set_text_color(checkbox, (oscgui_color){0.8f, 0.8f, 0.8f, 1.0f}); // light_gray
    oscgui_checkbox_set_font(checkbox, font);
    oscgui_checkbox_set_text(checkbox, "I'm a checkbox!");
    // 将组件添加到GUI中
    oscgui_gui_add(gui, oscgui_button_as_component(btn1));
    oscgui_gui_add(gui, oscgui_button_as_component(btn2));
    oscgui_gui_add(gui, oscgui_label_as_component(label));
    oscgui_gui_add(gui, oscgui_checkbox_as_component(checkbox));
}

int main(void) {
    app = oscgui_app_create(800, 600, "Hello OpenGL");

    oscgui_app_set_window_background(app, (oscgui_color){0.f, 0.f, 0.f});
    oscgui_app_set_init_gui(app, init_gui);
    oscgui_app_run(app);
    return 0;
}
