//
// Created by 冯帅真 on 2025/12/20.
//

#ifndef OSCGUI_GUI_H
#define OSCGUI_GUI_H

#include <vector>
// OpenGL / GLFW
#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "components.h"
#include "types.h"

namespace gui {

    class GUI {
    public:
        /**
         * @brief 初始化GUI
         * @param width 窗口宽度
         * @param height 窗口高度
         * @param title 窗口标题
         * @param error_callback 错误回调
         */
        explicit GUI(int width, int height, const char* title, void (*error_callback)(int, const char*));

        [[nodiscard]] vec2 get_window_size() const;

        [[nodiscard]] GLFWwindow* get_window() const;

        /**
         * 设置窗口键盘回调
         * @param key_callback 键盘回调
         */
        void set_keyCallback(GLFWkeyfun key_callback) const;

        void set_window_icon(const char* path) const;

        // 添加组件（GUI 不拥有生命周期，只管理）
        void add(components::Component* comp);

        // 每一帧调用
        void update();
        void draw(std::vector<Vertex>& guiOut, std::vector<Vertex>& textOut) const;

        void clear() const;

        [[nodiscard]] bool should_render_loop() const;

    private:
        GLFWwindow* window_;
        std::vector<components::Component*> components_;

        // 输入状态
        vec2 mouse_pos_{};
        bool mouse_down_ = false;

        // 输入处理
        void poll_input();
    };

}

#endif //OSCGUI_GUI_H