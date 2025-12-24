//
// Created by f1779 on 2025/12/24.
//

#include "components.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

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
            OnClick(this);
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
        float scale  = std::min(scaleX, scaleY);

        // 缩小到最大值
        scale = std::min(scale, 1.5f);

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

    // 按钮更新
    void Button::update(const vec2& mouse_pos, const bool mouse_down) {
        Component::update(mouse_pos, mouse_down);

    }
}

std::string get_file_content(const char *path) {
    const std::ifstream file(path);
    if (!file)
        throw std::runtime_error("failed to open file");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}