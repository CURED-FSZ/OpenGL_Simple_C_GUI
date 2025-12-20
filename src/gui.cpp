//
// Created by 冯帅真 on 2025/12/20.
//
#include "gui.h"

namespace gui {

    GUI::GUI(GLFWwindow* window)
        : window_(window) {}

    void GUI::add(components::Component* comp) {
        components_.push_back(comp);
    }

    void GUI::poll_input() {
        double x, y;
        glfwGetCursorPos(window_, &x, &y);
        mouse_pos_ = { static_cast<float>(x), static_cast<float>(y) };

        mouse_down_ =
            glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    }

    void GUI::update() {
        poll_input();

        for (auto* c : components_) {
            if (c->visible) {
                c->update(mouse_pos_, mouse_down_);
            }
        }
    }

    void GUI::draw(std::vector<Vertex>& out) const {
        for (const auto* c : components_) {
            if (c->visible) {
                c->draw(out);
            }
        }
    }

}