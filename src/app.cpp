//
// Created by f1779 on 2025/12/24.
//

#include "app.h"

App::App(const int w, const int h, const char *title,
         void (*error_callback)(int, const char *),
         void (*key_callback)(GLFWwindow *, int, int, int, int))
    : gui_(w, h, title, error_callback),
      renderer_(gui_),
      font_("font/fon.fnt",
            "font/fon.png")
{
    gui_.set_keyCallback(key_callback);

    renderer_.set_background(colors::white);

    guiVertices_.reserve(1024);
    textVertices_.reserve(1024);
}

gui::GUI& App::ui() {
    return gui_;
}

Renderer& App::renderer() {
    return renderer_;
}

void App::set_window_background(const Color color) {
    renderer_.set_background(color);
}

void App::set_window_icon(const char* path) const {
    gui_.set_window_icon(path);
}

void App::set_gui(void (*init_gui)(gui::GUI& ui, text::Font& font)) {
    init_gui_ = init_gui;
}

void App::run() {
    if (init_gui_)
        init_gui_(gui_, font_);
    else {
        perror("none init gui!");
        return;
    }

    while (gui_.should_render_loop()) {
        guiVertices_.clear();
        textVertices_.clear();

        gui_.update();
        gui_.draw(guiVertices_, textVertices_);

        renderer_.begin_frame();

        renderer_.beginGui();
        renderer_.draw(guiVertices_.data(), guiVertices_.size());

        renderer_.beginText(font_.texture());
        renderer_.draw(textVertices_.data(), textVertices_.size());

        renderer_.end_frame();
    }
}