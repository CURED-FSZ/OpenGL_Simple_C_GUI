//
// Created by 冯帅真 on 2025/12/20.
//
#include "gui.h"

#include <glad/include/gl.h>

#include <stb/stb_image.h>

namespace gui {
    GUI::GUI(const int width, const int height, const char* title, void (*error_callback)(int error, const char* description)) {
        // 初始化GLFW库
        if (!glfwInit())
            return;

        // 设置GLFW的错误回调函数
        glfwSetErrorCallback(error_callback);

        // 配置GLFW，指定使用的OpenGL版本和配置
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // 启用多重采样抗锯齿
        glfwWindowHint(GLFW_SAMPLES, 4);

        // 创建窗口前：告诉 GLFW，窗口先别显示
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        printf("create window\n");
        // 创建窗口
        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            printf("failed create window!\n");
            return;
        }


        // 获取主显示器
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        // 计算窗口居中位置
        glfwSetWindowPos(
            window,
            (mode->width  - width) / 2,
            (mode->height - height) / 2
        );

        // 固定窗口大小
        glfwSetWindowSizeLimits(window, width, height, width, height);

        // 设置当前OpenGL上下文
        glfwMakeContextCurrent(window);

        // 加载OpenGL函数指针（通过glad库）
        gladLoadGL(glfwGetProcAddress);

        // 启用垂直同步（V-Sync）
        glfwSwapInterval(1);

        // 显示窗口
        glfwShowWindow(window);

        window_ = window;
    }

    vec2 GUI::get_window_size() const {
        int width, height;
        glfwGetWindowSize(window_, &width, &height);
        return vec2{static_cast<float>(width), static_cast<float>(height)};
    }

    GLFWwindow* GUI::get_window() const {
        return window_;
    }

    void GUI::set_keyCallback(const GLFWkeyfun key_callback) const {
        // 设置窗口的键盘按键回调函数
        glfwSetKeyCallback(window_, key_callback);
    }

    void GUI::set_window_icon(const char* path) const {
        int w, h, channels;

        // stb_image 默认是左上角为原点，GLFW 也是 OK 的
        unsigned char* pixels = stbi_load(path, &w, &h, &channels, 4);
        if (!pixels) {
            printf("Failed to load icon: %s\n", path);
            return;
        }

        GLFWimage image{};
        image.width  = w;
        image.height = h;
        image.pixels = pixels;

        glfwSetWindowIcon(window_, 1, &image);

        stbi_image_free(pixels);
    }

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
        glfwPollEvents();
        poll_input();

        for (auto* c : components_) {
            if (c->visible) {
                c->update(mouse_pos_, mouse_down_);
            }
        }
    }

    void GUI::draw(std::vector<Vertex>& guiOut, std::vector<Vertex>& textOut) const {
        for (const auto* c : components_) {
            if (!c->visible) continue;
            c->drawGUI(guiOut);
            c->drawText(textOut);
        }
    }

    bool GUI::should_render_loop() const {
        return !glfwWindowShouldClose(window_);
    }

    void GUI::clear() const {
        // 渲染循环结束后清理资源
        glfwDestroyWindow(window_); // 销毁窗口

        // 清理并关闭GLFW
        glfwTerminate();
    }

}
