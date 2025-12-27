//
// Created by f1779 on 2025/12/27.
//

/* ==========================
 * 库引用
 * ========================== */

#include <oscgui_app.h>
#include <oscgui_types.h>
#include <oscgui_components.h>
#include <oscgui_gui.h>

/* ==========================
 * 声明页面组件
 * ========================== */
oscgui_app *app;
oscgui_button *btn1;
oscgui_button *btn2;
oscgui_label *label;
oscgui_checkbox *checkbox;

/* ==========================
 * 页面逻辑
 * ========================== */

void click1() {
    if (oscgui_checkbox_get_checked(checkbox))
        oscgui_label_set_text(label , "The button one be clicked and checkbox be checked!");
    else
        oscgui_label_set_text(label , "The button one be clicked!");
}

void click2() {
    oscgui_label_set_text(label , "I'm here~");
}

/* ==========================
 * GUI 初始化
 * ========================== */

void init_gui(const oscgui_gui *gui, const oscgui_font *font) {
    // 按钮1
    btn1 = oscgui_button_create(125, 380, 250, 100);
    oscgui_button_set_color(btn1,
                            (oscgui_color){0.5f, 0.5f, 0.7f, 1.0f},
                            (oscgui_color){0.2f, 0.3f, 0.4f, 1.0f},
                            (oscgui_color){0.5f, 0.9f, 0.7f, 1.0f}
    );
    oscgui_button_set_on_click(btn1, click1);
    oscgui_button_set_font(btn1, font);
    oscgui_button_set_text(btn1, "Click me");
    oscgui_gui_add(gui, oscgui_button_as_component(btn1));

    // 按钮2
    btn2 = oscgui_button_create(425, 380, 250, 100);
    oscgui_button_set_color(btn2,
                             (oscgui_color){0.5f, 0.5f, 0.7f, 1.0f},
                             (oscgui_color){0.2f, 0.3f, 0.4f, 1.0f},
                             (oscgui_color){0.5f, 0.9f, 0.7f, 1.0f}
    );
    oscgui_button_set_on_click(btn2, click2);
    oscgui_button_set_font(btn2, font);
    oscgui_button_set_text(btn2, "reset the label");
    oscgui_gui_add(gui, oscgui_button_as_component(btn2));

    // 标签
    label = oscgui_label_create(0, 10, 800, 200);
    oscgui_label_set_color(label, (oscgui_color){0.5f, 0.5f, 0.7f, 1.0f});
    oscgui_label_set_font(label, font);
    oscgui_label_set_text(label, "I'm here~");
    oscgui_gui_add(gui, oscgui_label_as_component(label));

    // 复选框
    checkbox = oscgui_checkbox_create(220, 250, 300, 100);
    oscgui_checkbox_set_color(checkbox, (oscgui_color){0.5f, 0.5f, 0.7f, 1.0f});
    oscgui_checkbox_set_font(checkbox, font);
    oscgui_checkbox_set_text(checkbox, "Check me");
    oscgui_gui_add(gui, oscgui_checkbox_as_component(checkbox));

}

/* ==========================
 * 主函数
 * ========================== */

int main(void) {
    app = oscgui_app_create(800, 600, "Hello OpenGL");

    oscgui_app_set_window_background(app, (oscgui_color){0.f, 0.f, 0.f});

    oscgui_app_set_window_icon(app, "img/oscgui_64.jpg");

    oscgui_app_set_init_gui(app, init_gui);

    oscgui_app_run(app);

    return 0;
}