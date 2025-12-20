//
// Created by 冯帅真 on 2025/12/20.
//

#ifndef OSCGUI_GUI_H
#define OSCGUI_GUI_H

#include <vector>
#include <GLFW/glfw3.h>

#include "based.h"

namespace gui {

    class GUI {
    public:
        explicit GUI(GLFWwindow* window);

        // 添加组件（GUI 不拥有生命周期，只管理）
        void add(components::Component* comp);

        // 每一帧调用
        void update();
        void draw(std::vector<Vertex>& out) const;

    private:
        GLFWwindow* window_;
        std::vector<components::Component*> components_;

        // 输入状态
        vec2 mouse_pos_{};
        bool mouse_down_ = false;

    private:
        void poll_input();
    };

}

#endif //OSCGUI_GUI_H