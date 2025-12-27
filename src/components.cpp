//
// Created by f1779 on 2025/12/24.
//

#include "components.h"

#include <fstream>
#include <sstream>

#include "gl.h"
#include "gui.h"
#include "stb/stb_image.h"

void general_text_draw(std::vector<Vertex> &textOut, text::Text *text_, const vec2& position, const vec2& size, const Color& text_color) {
    if (!text_) return;

    // 原始大小的文本
    const auto [width, height] = text_->measure();

    // 计算可用的空间
    const float paddingX = size.x * 0.1f;
    const float paddingY = size.y * 0.2f;

    const float availW = size.x - paddingX * 2.0f;
    const float availH = size.y - paddingY * 2.0f;

    // 缩放
    const float scaleX = availW / width;
    const float scaleY = availH / height;
    const float scale  = std::min(scaleX, scaleY);

    // 设置文本属性
    text_->setScale(scale);
    text_->setColor(text_color);

    // 计算居中位置
    const float textW = width  * scale;
    const float textH = height * scale;

    const float x = position.x + (size.x - textW) * 0.5f;
    const float y = position.y + (size.y - textH) * 0.5f;

    text_->setPosition(x, y);

    text_->draw(textOut);
}

namespace components {
    void Component::update(const vec2& mouse_pos, const bool mouse_down){
        // 上一帧状态
        prev_state = state;

        if (!enabled) {
            state = ComponentState::Disabled;
            return;
        }

        // 鼠标是否在组件内
        if (!contains(mouse_pos)) {
            state = ComponentState::Normal;
            return;
        }

        // 鼠标按下
        if (mouse_down) {
            state = ComponentState::Pressed;
        } else {
            state = ComponentState::Hovered;
        }

        // click 条件：按下 → 松开，并且还在按钮里
        if (prev_state == ComponentState::Pressed &&
            state == ComponentState::Hovered) {
            on_click();
            }
    }

    [[nodiscard]] bool Component::contains(const vec2& p) const{
        return p.x >= position.x &&
               p.y >= position.y &&
               p.x <= position.x + size.x &&
               p.y <= position.y + size.y;
    }

    void Component::on_click() {
        if (OnClick) {
            OnClick();
        }
    }

    void Button::set_text(const std::string &text) const {
        if (!text_) {
            perror("font isn't be defined!");
            return;
        }
        text_->setString(text);
    }

    void Button::set_font(text::Font* font) {
        text_ = new text::Text(font);
    }

    void Button::drawGUI(std::vector<Vertex>& guiOut) const {
        Color c = normal_color;
        if (state == ComponentState::Hovered)  c = hover_color;
        if (state == ComponentState::Pressed)  c = pressed_color;

        shapes::rectangle(
            guiOut,
            position.x,
            position.y,
            size.x,
            size.y,
            c
        );
    }

    void Button::drawText(std::vector<Vertex>& textOut) const {
        general_text_draw(textOut, text_, position, size, text_color);
    }

    // 按钮更新
    void Button::update(const vec2& mouse_pos, const bool mouse_down) {
        Component::update(mouse_pos, mouse_down);
    }

    void Label::set_text(const std::string &text) const {
        if (!text_) {
            perror("font isn't be defined!");
            return;
        }
        text_->setString(text);
    }

    void Label::set_font(text::Font *font) {
        text_ = new text::Text(font);
    }

    void Label::drawGUI([[maybe_unused]] std::vector<Vertex> &guiOut) const {}

    void Label::update([[maybe_unused]] const vec2& mouse_pos, [[maybe_unused]] const bool mouse_down) {}

    void Label::drawText(std::vector<Vertex> &textOut) const {
        general_text_draw(textOut, text_, position, size, text_color);
    }

    void CheckBox::drawGUI(std::vector<Vertex> &guiOut) const {
        shapes::rectangle(
            guiOut,
            position.x + size.x - 20,
            position.y + size.y / 2 - 10,
            20,
            20,
            colors::white
        );

        if (!is_checked)
            return;

        shapes::rectangle(
            guiOut,
            position.x + size.x - 18,
            position.y + size.y / 2 - 8,
            16,
            16,
            colors::black
            );
    }

    void CheckBox::drawText(std::vector<Vertex> &textOut) const {
        if (!text_) return;

        // 原始大小的文本
        const auto [width, height] = text_->measure();

        const float tmp_x = size.x - 30;

        // 计算可用的空间
        const float paddingX = tmp_x * 0.1f;
        const float paddingY = size.y * 0.2f;

        const float availW = tmp_x - paddingX * 2.0f;
        const float availH = size.y - paddingY * 2.0f;

        // 缩放
        const float scaleX = availW / width;
        const float scaleY = availH / height;
        const float scale  = std::min(scaleX, scaleY);

        // 设置文本属性
        text_->setScale(scale);
        text_->setColor(text_color);

        // 计算居中位置
        const float textW = width  * scale;
        const float textH = height * scale;

        const float x = position.x + (tmp_x - textW) * 0.5f;
        const float y = position.y + (size.y - textH) * 0.5f;

        text_->setPosition(x, y);

        text_->draw(textOut);
    }

    void CheckBox::update(const vec2 &mouse_pos, const bool mouse_down) {
        Component::update(mouse_pos, mouse_down);
    }

    void CheckBox::set_font(text::Font *font) {
        text_ = new text::Text(font);
    }

    void CheckBox::set_text(const std::string &text) const {
        if (!text_) {
            perror("font isn't be defined!");
            return;
        }
        text_->setString(text);
    }

    void CheckBox::on_click() {
        is_checked = !is_checked;
    }
}

std::string get_file_content(const char *path) {
    const std::ifstream file(path);
    if (!file)
        perror("failed to open file");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}