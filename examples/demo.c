//
// Created by 冯帅真 on 2025/12/20.
//
#include <stdio.h>
#include <oscgui/oscgui.h>

void click(oscgui_component* e) {
    printf("Clicked!\n");
}

int main(void) {
    oscgui_gui* gui = oscgui_create();

    oscgui_button* btn = oscgui_button_create();
    oscgui_button_set_position(btn, 10, 10);
    oscgui_button_set_size(btn, 100, 50);
    oscgui_button_set_color(
        btn,
        (oscgui_color){1, 0, 0, 1},
        (oscgui_color){0, 1, 0, 1},
        (oscgui_color){0, 0, 1, 1}
    );
    oscgui_button_set_on_click(btn, click);

    oscgui_gui_add(gui, oscgui_as_component(btn));

    /* ===== 主循环（由用户驱动）===== */
    while (1) {
        const oscgui_vec2 mouse = get_mouse_position();   // 用户自己实现
        const int mouse_down = is_mouse_down();            // 用户自己实现

        oscgui_update(gui, mouse, mouse_down);
        oscgui_draw(gui);

        /* swap buffers / sleep / etc */
    }

    oscgui_button_destroy(btn);
    oscgui_destroy(gui);
    return 0;
}