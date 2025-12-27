//
// Created by f1779 on 2025/12/24.
//

#ifndef OSCGUI_APP_H
#define OSCGUI_APP_H
#include "gui.h"
#include "renderer.h"
#include <functional>

class App {
public:
    App(int w, int h, const char* title);

    ~App() =  default;

    /**
     * @brief 获取GUI对象
     * @return GUI对象
     */
    gui::GUI& ui();

    /**
     * @brief 获取渲染器对象
     * @return 渲染器对象
     */
    Renderer& renderer();

    /**
     * @brief 设置窗口背景颜色
     * @param color 颜色
     */
    void set_window_background(Color color);

    /**
     * @brief 设置窗口图标
     * @param path 图标路径
     */
    void set_window_icon(const char* path) const;

    /**
     * @brief 设置GUI初始化函数
     * @param init_gui GUI初始化函数
     */
    void set_gui(const std::function<void(gui::GUI*, text::Font*)> &init_gui);

    void *c_handle = nullptr; // C bridge 用的初始化函数句柄

    /**
     * @brief 运行程序
     */
    void run();

private:
    gui::GUI gui_;
    Renderer renderer_;

    std::function<void(gui::GUI*, text::Font*)> init_gui_;

    std::vector<Vertex> guiVertices_;
    std::vector<Vertex> textVertices_;

    text::Font font_;
};
#endif //OSCGUI_APP_H