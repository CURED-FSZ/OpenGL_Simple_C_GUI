//
// Created by 冯帅真 on 2025/12/21.
//

#include <oscgui/oscgui_components.h>
#include <based.h>

/* =========================
   不透明结构体定义
   ========================= */

struct oscgui_component {
    components::Component* impl;  // C++ 组件
    oscgui_click_cb c_on_click;   // C 用户的回调
};

struct oscgui_button {
    components::Button* impl;  // C++ 按钮
    oscgui_component* as_component; // C++ 组件的 C 层包装
};

/* =========================
   Components 操作
   ========================= */

oscgui_component* oscgui_as_component(const oscgui_button* btn) {
    if (!btn) return nullptr;
    return btn->as_component;
}

oscgui_button* oscgui_button_create() {
    auto *b = new oscgui_button;
    b -> impl = new components::Button;

    b->as_component = new oscgui_component;
    b->as_component->impl = b->impl;
    b->as_component->c_on_click = nullptr;

    b->impl->c_handle = b->as_component;
    return b;
}

void oscgui_button_destroy(const oscgui_button* btn) {
    if (!btn) return;

    delete btn -> as_component;
    delete btn -> impl;
    delete btn;
}

void oscgui_button_set_position(const oscgui_button* btn, const float x, const float y) {
    if (!btn) return;

    btn -> impl -> position = vec2{x, y};
}

void oscgui_button_set_size(const oscgui_button* btn, const float w, const float h) {
    if (!btn) return;

    btn -> impl -> size = vec2{w, h};
}

void oscgui_button_set_color(const oscgui_button* btn, const oscgui_color normal,
    const oscgui_color hover, const oscgui_color pressed) {
    if (!btn) return;

    btn -> impl -> normal_color = Color{normal.r, normal.g, normal.b};
    btn -> impl -> hover_color = Color{hover.r, hover.g, hover.b};
    btn -> impl -> pressed_color = Color{pressed.r, pressed.g, pressed.b};
}

// C++ → C 的桥接函数
static void oscgui_click_trampoline(components::Component* cpp_self) {
    auto* c_wrapper =
        static_cast<oscgui_component*>(cpp_self->c_handle);

    if (c_wrapper && c_wrapper->c_on_click) {
        c_wrapper->c_on_click(c_wrapper);
    }
}

void oscgui_button_set_on_click(const oscgui_button* btn, const oscgui_click_cb cb) {
    if (!btn) return;
    // 保存 C 回调
    btn->as_component->c_on_click = cb;

    // 让 C++ Component 调 trampoline
    btn->impl->OnClick = oscgui_click_trampoline;
}