//
// Created by f1779 on 2025/12/18.
//
#include "based.h"

#include <cmath>

namespace shapes {
    void rectangle(std::vector<Vertex> &out, const float x, const float y, const float w, const float h,
                   const Color color) {
        const Vertex v0{{x, y}, {color.r, color.g, color.b, color.a}};
        const Vertex v1{{x + w, y}, {color.r, color.g, color.b, color.a}};
        const Vertex v2{{x + w, y + h}, {color.r, color.g, color.b, color.a}};
        const Vertex v3{{x, y + h}, {color.r, color.g, color.b, color.a}};

        out.push_back(v0);
        out.push_back(v1);
        out.push_back(v2);

        out.push_back(v0);
        out.push_back(v2);
        out.push_back(v3);
    }

    void triangle(std::vector<Vertex> &out, const vec2 point_one, const vec2 point_two, const vec2 point_three,
                  const Color color) {
        const Vertex v0{{point_one.x, point_one.y}, {color.r, color.g, color.b, color.a}};
        const Vertex v1{{point_two.x, point_two.y}, {color.r, color.g, color.b, color.a}};
        const Vertex v2{{point_three.x, point_three.y}, {color.r, color.g, color.b, color.a}};

        out.push_back(v0);
        out.push_back(v1);
        out.push_back(v2);
    }

    void line(std::vector<Vertex> &out, const vec2 point_one, const vec2 point_two, const float thickness,
              const Color color) {
        // 方向向量 d = p2 - p1
        const float dx = point_two.x - point_one.x;
        const float dy = point_two.y - point_one.y;

        // 计算长度
        const float len = std::sqrt(dx * dx + dy * dy);
        if (len == 0.0f) return; // 防止除零

        // 单位法线向量 n = (-dy, dx) / len
        const float nx = -dy / len;
        const float ny = dx / len;

        // 半厚度偏移
        const float hx = nx * (thickness * 0.5f);
        const float hy = ny * (thickness * 0.5f);

        // 四个顶点
        const Vertex v0{{point_one.x + hx, point_one.y + hy}, {color.r, color.g, color.b, color.a}};
        const Vertex v1{{point_one.x - hx, point_one.y - hy}, {color.r, color.g, color.b, color.a}};
        const Vertex v2{{point_two.x + hx, point_two.y + hy}, {color.r, color.g, color.b, color.a}};
        const Vertex v3{{point_two.x - hx, point_two.y - hy}, {color.r, color.g, color.b, color.a}};

        // 两个三角形
        out.push_back(v0);
        out.push_back(v1);
        out.push_back(v2);

        out.push_back(v2);
        out.push_back(v1);
        out.push_back(v3);
    }
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
    // 鼠标是否在组件内
    [[nodiscard]] bool Component::contains(const vec2& p) const{
        return p.x >= position.x &&
               p.y >= position.y &&
               p.x <= position.x + size.x &&
               p.y <= position.y + size.y;
    }

    // 点击事件
    void Component::on_click() {
        if (OnClick) {
            OnClick(this);
        }
    }

    // 按钮绘制
    void Button::draw(std::vector<Vertex>& out) const {
        if (!visible) return;

        Color color{};
        switch (state) {
            case ComponentState::Hovered:
                color = hover_color;
                break;
            case ComponentState::Pressed:
                color = pressed_color;
                break;
            default:
                color = normal_color;
                break;
        }

        shapes::rectangle(
            out,
            position.x,
            position.y,
            size.x,
            size.y,
            color
        );
    }

    // 按钮更新
    void Button::update(const vec2& mouse_pos, const bool mouse_down) {
        Component::update(mouse_pos, mouse_down);

    }
}
