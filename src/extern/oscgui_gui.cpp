//
// Created by f1779 on 2025/12/26.
//
#include <../../include/oscgui_gui.h>
#include <../../include/oscgui_types.h>

#include "gui.h"

struct oscgui_component {
    components::Component* impl;  // C++ 组件
};

struct oscgui_gui {
    gui::GUI* impl;
};

extern "C" void oscgui_gui_add(const oscgui_gui* ui, const oscgui_component* component) {
    if (!ui || !component) return;
    ui->impl->add(component->impl);
}