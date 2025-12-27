//
// Created by 冯帅真 on 2025/12/21.
//

#include <../../include/oscgui_components.h>

#include "../components.h"

struct oscgui_component {
    components::Component* impl;  // C++ 组件
};

struct oscgui_button {
    components::Button* impl;  // C++ 按钮
    oscgui_component* as_component; // C++ 组件的 C 层包装
};

struct oscgui_label {
    components::Label* impl;
    oscgui_component* as_component;
};

struct oscgui_checkbox {
    components::CheckBox* impl;
    oscgui_component* as_component;
};

struct oscgui_font {
    text::Font* impl;
};

/* =========================
   Components 操作
   ========================= */

extern "C" oscgui_component* oscgui_button_as_component(const oscgui_button* btn) {
    if (!btn) return nullptr;
    return btn->as_component;
}

extern "C" oscgui_component *oscgui_label_as_component(const oscgui_label *label) {
    if (!label) return nullptr;
    return label->as_component;
}

extern "C" oscgui_component *oscgui_checkbox_as_component(const oscgui_checkbox *checkbox) {
    if (!checkbox) return nullptr;
    return checkbox->as_component;
}


/* =========================
 * Button 操作
 * ========================= */

extern "C" oscgui_button* oscgui_button_create(const float x, const float y, const float w, const float h) {
    auto *b = new oscgui_button;
    const vec2 position = {x, y};
    const vec2 size = {w, h};
    b -> impl = new components::Button(position, size);

    b->as_component = new oscgui_component;
    b->as_component->impl = b->impl;

    return b;
}

extern "C" void oscgui_button_destroy(const oscgui_button* btn) {
    if (!btn) return;

    delete btn -> as_component;
    delete btn -> impl;
    delete btn;
}

extern "C" void oscgui_button_set_font(const oscgui_button *btn, const oscgui_font *font) {
    btn->impl->set_font(font -> impl);
    dynamic_cast<components::Button*>(btn->as_component->impl)->set_font(font -> impl);
}

extern "C" void oscgui_button_set_text(const oscgui_button *btn, const char *text) {
    btn->impl->set_text(text);
    dynamic_cast<components::Button*>(btn->as_component->impl)->set_text(text);
}

extern "C" void oscgui_button_set_color(const oscgui_button* btn, const oscgui_color normal,
    const oscgui_color hover, const oscgui_color pressed) {
    if (!btn) return;

    btn -> impl -> normal_color = Color{normal.r, normal.g, normal.b, normal.a};
    btn -> impl -> hover_color = Color{hover.r, hover.g, hover.b, hover.a};
    btn -> impl -> pressed_color = Color{pressed.r, pressed.g, pressed.b, pressed.a};

    dynamic_cast<components::Button*>(btn->as_component->impl)->normal_color = Color{normal.r, normal.g, normal.b, normal.a};
    dynamic_cast<components::Button*>(btn->as_component->impl)->hover_color = Color{hover.r, hover.g, hover.b, hover.a};
    dynamic_cast<components::Button*>(btn->as_component->impl)->pressed_color = Color{pressed.r, pressed.g, pressed.b, pressed.a};
}

extern "C" void oscgui_button_set_on_click(const oscgui_button* btn, const oscgui_click cb) {
    if (!btn) return;
    // 保存 C 回调
    btn->impl->OnClick = cb;
    dynamic_cast<components::Button*>(btn->as_component->impl)->OnClick = cb;
}

/* =========================
 * Label 操作
 * ========================= */

extern "C" oscgui_label* oscgui_label_create(const float x, const float y, const float w, const float h) {
    auto *l = new oscgui_label;
    l->impl = new components::Label(vec2{x, y}, vec2{w, h});

    l->as_component = new oscgui_component;
    l->as_component->impl = l->impl;
    return l;
}

extern "C" void oscgui_label_destroy(const oscgui_label *label) {
    if (!label) return;
    delete label->as_component;
    delete label->impl;
    delete label;
}

extern "C" void oscgui_label_set_color(const oscgui_label *label, const oscgui_color color) {
    if (!label) return;
    label->impl->text_color = Color{color.r, color.g, color.b, color.a};
}

extern "C" void oscgui_label_set_font(const oscgui_label *label, const oscgui_font *font) {
    if (!label || !font) return;
    label->impl->set_font(font->impl);
}

extern "C" void oscgui_label_set_text(const oscgui_label *label, const char *text) {
    if (!label || !text) return;
    label->impl->set_text(text);
}

/* =========================
 * CheckBox 操作
 * ========================= */

extern "C" oscgui_checkbox* oscgui_checkbox_create(const float x, const float y, const float w, const float h) {
    auto* c = new oscgui_checkbox;
    c->impl = new components::CheckBox(vec2{x, y}, vec2{w, h});
    c->as_component = new oscgui_component;
    c->as_component->impl = c->impl;
    return c;
}

extern "C" void oscgui_checkbox_destroy(const oscgui_checkbox *checkbox) {
    if (!checkbox) return;
    delete checkbox->impl;
    delete checkbox->as_component;
    delete checkbox;
}

extern "C" void oscgui_checkbox_set_font(const oscgui_checkbox *checkbox, const oscgui_font *font) {
    if (!checkbox || !font) return;
    checkbox->impl->set_font(font->impl);
}

extern "C" void oscgui_checkbox_set_text(const oscgui_checkbox *checkbox, const char *text) {
    if (!checkbox || !text) return;
    checkbox->impl->set_text(text);
}

extern "C" void oscgui_checkbox_set_color(const oscgui_checkbox *checkbox, const oscgui_color color) {
    if (!checkbox) return;
    checkbox->impl->text_color = Color{color.r, color.g, color.b, color.a};
}

extern "C" int oscgui_checkbox_get_checked(const oscgui_checkbox *checkbox) {
    if (!checkbox) return -1;
    return checkbox->impl->is_checked;
}