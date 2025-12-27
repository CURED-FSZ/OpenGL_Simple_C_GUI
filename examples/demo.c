//
// Created by 冯帅真 on 2025/12/20.
//
#include <stdio.h>
#include <oscgui_app.h>
#include <oscgui_types.h>
#include <oscgui_components.h>
#include <oscgui_gui.h>

oscgui_app *app;
oscgui_button *btn1;
oscgui_button *btn2;
oscgui_label *label;
oscgui_checkbox *checkbox;

void click() {
    printf("Clicked!\n");
}

void init_gui(oscgui_gui *gui, const oscgui_font *font) {
    btn1 = oscgui_button_create(10, 10, 100, 50);
    oscgui_button_set_color(btn1,
                            (oscgui_color){0.5f, 0.5f, 0.7f, 1.0f},
                            (oscgui_color){0.2f, 0.3f, 0.4f, 1.0f},
                            (oscgui_color){0.5f, 0.9f, 0.7f, 1.0f}
    );
    oscgui_button_set_on_click(btn1, click);
    oscgui_button_set_font(btn1, font);
    oscgui_button_set_text(btn1, "Click me!");

    oscgui_gui_add(gui, oscgui_button_as_component(btn1));
}

int main(void) {
    app = oscgui_app_create(800, 600, "Hello OpenGL");

    oscgui_app_set_window_background(app, (oscgui_color){0.f, 0.f, 0.f});

    oscgui_app_set_init_gui(app, init_gui);

    oscgui_app_run(app);

    return 0;
}
