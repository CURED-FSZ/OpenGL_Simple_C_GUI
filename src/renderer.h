//
// Created by 冯帅真 on 2025/12/20.
//

#ifndef OSCGUI_RENDERER_H
#define OSCGUI_RENDERER_H
#include "based.h"

class Renderer {
public:
    /**
     * 初始化渲染器
     * @param width 视口宽度
     * @param height 视口高度
     */
    void init(int width, int height);

    /**
     * 初始化帧
     */
    void begin_frame() const;

    /**
     * 绘制帧
     * @param vertices 顶点集合
     * @param count 顶点数量
     */
    void draw(const Vertex* vertices, std::size_t count) const;

    /**
     * 帧结束
     */
    void end_frame();

private:
    unsigned int program_ = 0;
    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
    int mvp_location_ = -1;

    int width_ = 0;
    int height_ = 0;

    void create_program();
};

#endif //OSCGUI_RENDERER_H