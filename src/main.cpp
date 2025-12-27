#include <iostream>

#include "app.h"

App app(800, 600, "Hello OpenGL");

components::Button btn({100.f, 100.f}, {200.f, 80.f});
components::Button btn2({300.f, 300.f}, {300.f, 80.f});
components::Label label({100.f, 300.f}, {200.f, 80.f});
components::CheckBox checkbox({370.f, 100.f}, {350.f, 150.f});

void click() {
    if (checkbox.is_checked)
        btn2.set_text("checkbox save you!");
    else
        btn2.set_text("I was clicked!");
}

void click2() {
    btn2.set_text("");
}

void init_gui(gui::GUI* ui, text::Font* font) {
    btn.normal_color = colors::light_gray;
    btn.hover_color = colors::gray;
    btn.pressed_color = colors::dark_gray;
    btn.text_color = colors::black;
    btn.OnClick = click;
    btn.set_font(font);
    btn.set_text("Click me!");

    btn2.normal_color = colors::light_gray;
    btn2.hover_color = colors::gray;
    btn2.pressed_color = colors::dark_gray;
    btn2.text_color = colors::magenta;
    btn2.OnClick = click2;
    btn2.set_font(font);

    label.text_color = colors::light_gray;
    label.set_font(font);
    label.set_text("I'm a label!");

    checkbox.text_color = colors::light_gray;
    checkbox.set_font(font);
    checkbox.set_text("I'm a checkbox!");

    ui->add(&btn);
    ui->add(&btn2);
    ui->add(&label);
    ui->add(&checkbox);
}

int main() {
    // 设置GUI初始化函数
    app.set_gui(init_gui);

    app.set_window_icon("img/oscgui_64.jpg");

    // 设置窗口背景颜色
    app.set_window_background(colors::black);

    // 运行程序
    app.run();

    // 正常退出程序
    exit(EXIT_SUCCESS);
}