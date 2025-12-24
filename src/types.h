//
// Created by f1779 on 2025/12/18.
//

#ifndef OPENGL_C_GUI_BASED_H
#define OPENGL_C_GUI_BASED_H

#include <vector>

struct vec2 {
    float x;
    float y;
};

struct vec4 {
    float x;
    float y;
    float z;
    float w;
};

// 顶点
struct Vertex {
    vec2 pos{}; // 顶点的二维位置坐标
    vec4 col{}; // 顶点的颜色值（RGB格式）
    vec2 uv{}; // 顶点的二维纹理坐标
};

// 颜色结构体
struct Color {
    float r{}, g{}, b{}, a{};
    constexpr Color() = default;
    constexpr Color(const float red, const float green, const float blue) {
        r = red; g = green; b = blue; a = 1.0f;
    }
    constexpr Color(const float red, const float green, const float blue, const float alpha) {
        r = red; g = green; b = blue; a = alpha;
    }

    constexpr void alpha(const float al) {
        a = al;
    }
};

namespace colors {
    constexpr Color red = {1.0f, 0.0f, 0.0f}; // 红
    constexpr Color green = {0.0f, 1.0f, 0.0f}; // 绿
    constexpr Color blue = {0.0f, 0.0f, 1.0f}; // 蓝
    constexpr Color white = {1.0f, 1.0f, 1.0f}; // 白
    constexpr Color black = {0.0f, 0.0f, 0.0f}; // 黑
    constexpr Color yellow = {1.0f, 1.0f, 0.0f}; // 黄
    constexpr Color purple = {1.0f, 0.0f, 1.0f}; // 紫
    constexpr Color gray = {0.5f, 0.5f, 0.5f}; // 灰
    constexpr Color light_gray = {0.8f, 0.8f, 0.8f}; // 浅灰
    constexpr Color dark_gray = {0.2f, 0.2f, 0.2f}; // 深灰
    constexpr Color orange = {1.0f, 0.5f, 0.0f}; // 橙
    constexpr Color cyan = {0.0f, 1.0f, 1.0f}; // 青
    constexpr Color magenta = {1.0f, 0.0f, 1.0f}; // 品红
    constexpr Color brown = {0.6f, 0.3f, 0.0f}; // 棕
    constexpr Color pink = {1.0f, 0.75f, 0.8f}; // 粉
    constexpr Color lime = {0.0f, 1.0f, 0.0f}; // 酸橙
    constexpr Color navy = {0.0f, 0.0f, 0.5f}; // 海军蓝
    constexpr Color olive = {0.5f, 0.5f, 0.0f}; // 橄榄
    constexpr Color teal = {0.0f, 0.5f, 0.5f}; // 水鸭色
    constexpr Color maroon = {0.5f, 0.0f, 0.0f}; // 栗色
    constexpr Color silver = {0.75f, 0.75f, 0.75f}; // 银
    constexpr Color gold = {1.0f, 0.84f, 0.0f}; // 金
    constexpr Color transparent = {0.0f, 0.0f, 0.0f}; // 透明
}

namespace shapes {
    /**
     * 绘制一个矩形
     * @param out 输出的顶点数据
     * @param x 矩形左上角x坐标
     * @param y 矩形左上角y坐标
     * @param w 矩形的宽度
     * @param h 矩形的高度
     * @param color 矩形的颜色
     */
    void rectangle(std::vector<Vertex> &out, float x, float y, float w, float h, Color color);

    /**
     * 绘制一个三角形
     * @param out 输出的顶点数据
     * @param point_one 三角形第一个顶点坐标
     * @param point_two 三角形第二个顶点坐标
     * @param point_three 三角形第三个顶点坐标
     * @param color 三角形的颜色
     */
    void triangle(std::vector<Vertex> &out, vec2 point_one, vec2 point_two, vec2 point_three, Color color);

    /**
     * 绘制一条线
     * @param out 输出的顶点数据
     * @param point_one 第一个点坐标
     * @param point_two 第二个点坐标
     * @param thickness 线粗细
     * @param color 线的颜色
     */
    void line(std::vector<Vertex> &out, vec2 point_one, vec2 point_two, float thickness, Color color);
}

#endif //OPENGL_C_GUI_BASED_H
