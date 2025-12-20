//
// Created by 冯帅真 on 2025/12/20.
//
#include <stdio.h>
#include <oscgui/api.h>

void click(oscgui_component* e) {
    printf("Clicked!");
}

int main() {
    printf("Hello World!");
    oscgui_button *btn = oscgui_button_create();
    oscgui_button_set_position(btn, 10, 10);
    oscgui_button_set_size(btn, 100, 50);
    oscgui_button_set_color(
        btn,
        (oscgui_color){1, 0, 0, 1},
        (oscgui_color){0, 1, 0, 1},
        (oscgui_color){0, 0, 1, 1}
    );
    oscgui_button_set_on_click(btn, click);
    oscgui_gui *gui = oscgui_create();
    oscgui_gui_add(gui, oscgui_as_component(btn));

}