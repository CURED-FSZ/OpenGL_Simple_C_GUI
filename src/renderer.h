//
// Created by 冯帅真 on 2025/12/20.
//

#ifndef OSCGUI_RENDERER_H
#define OSCGUI_RENDERER_H
#include "types.h"
#include "gui.h"

class Renderer {
public:
    /**
     * 初始化渲染器
     * @param gui
     * @param background 视口背景
     */
    explicit Renderer(const gui::GUI &gui, Color background = colors::black);

    /**
     * 初始化帧
     */
    void begin_frame() const;

    /**
     * 绑定纹理
     * @param tex
     */
    void beginText(unsigned int tex) const;

    /**
     * 绑定GUI
     */
    void beginGui() const;

    /**
     * 绘制帧
     * @param vertices 顶点集合
     * @param count 顶点数量
     */
    void draw(const Vertex* vertices, std::size_t count) const;

    /**
     * 设置背景颜色
     * @param color
     */
    void set_background(Color color);

    /**
     * 帧结束
     */
    void end_frame() const;

private:
    unsigned int program_ = 0;
    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
    int mvp_location_ = -1;

    int width_ = 0;
    int height_ = 0;

    GLFWwindow* window_ = nullptr;
    Color background_ = colors::black;

    void create_program();
};

#endif //OSCGUI_RENDERER_H