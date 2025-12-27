//
// Created by f1779 on 2025/12/26.
//
#include <../../include/oscgui_app.h>

#include "app.h"
#include "GLFW/glfw3.h"

typedef void (*oscgui_init_gui)(const oscgui_gui* gui, const oscgui_font* font);

struct oscgui_app {
    App* impl;
    oscgui_init_gui c_init_gui;
};

struct oscgui_window {
    GLFWwindow* impl;
};

struct oscgui_gui {
    gui::GUI* impl;
};

struct oscgui_font {
    text::Font* impl;
};

extern "C" oscgui_app* oscgui_app_create(const int w, const int h, const char* title) {
    return new oscgui_app{new App(w, h, title), nullptr};
}

extern "C" void oscgui_app_destroy(const oscgui_app* app) {
    delete app->impl;
    delete app;
}

extern "C" void oscgui_app_run(const oscgui_app* app) {
    app->impl->run();
}


extern "C" void oscgui_app_set_init_gui(oscgui_app* app, const oscgui_init_gui fn) {
    if (!app) {
        perror("app is empty!");
        return;
    }

    app->c_init_gui = fn;

    // 把 C 回调桥接成 C++ init_gui
    app->impl->set_gui(
        [app](gui::GUI* gui, text::Font* font) {
        if (!app->c_init_gui) return;

        oscgui_gui  c_gui  { gui };
        oscgui_font c_font { font };

        // 转调到 C
        app->c_init_gui(&c_gui, &c_font);
    });
}

extern "C" void oscgui_app_set_window_icon(const oscgui_app* app, const char* path) {
    app->impl->set_window_icon(path);
}

extern "C" void oscgui_app_set_window_background(const oscgui_app* app, const oscgui_color color) {
    const Color c_color = {color.r, color.g, color.b, color.a};
    app->impl->set_window_background(c_color);
}