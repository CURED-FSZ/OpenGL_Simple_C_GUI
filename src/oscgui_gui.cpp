//
// Created by 冯帅真 on 2025/12/20.
//

#include <oscgui/oscgui_gui.h>

#include <gui.h>
#include <types.h>

#include <GLFW/glfw3.h>

/* =========================
   不透明结构体定义
   ========================= */

struct oscgui_gui {
    gui::GUI *impl;
};

/* =========================
   GUI 生命周期
   ========================= */
/*
oscgui_gui *oscgui_gui_create(void *native_window) {
    if (!native_window) return nullptr;

    auto *g = new oscgui_gui;
    g->impl = new gui::GUI(
        static_cast<GLFWwindow *>(native_window)
    );
    return g;
}
*/

void oscgui_gui_destroy(const oscgui_gui *gui) {
    if (!gui) return;

    delete gui->impl;
    delete gui;
}

/* =========================
   GUI 操作
   ========================= */


void oscgui_gui_add(const oscgui_gui *gui, components::Component *comp) {
    if (!gui || !comp) return;

    gui->impl->add(
        comp
    );
}


void oscgui_gui_update(const oscgui_gui *gui) {
    if (!gui) return;

    gui->impl->update();
}


void oscgui_gui_draw(const oscgui_gui *gui, Vertex * /*unused*/) {
    (void) gui;
}
