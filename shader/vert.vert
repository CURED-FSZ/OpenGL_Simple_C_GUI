#version 460
uniform mat4 MVP; // 模型-视图-投影矩阵

layout(location = 0) in vec2 vPos; // 顶点位置
layout(location = 1) in vec4 vCol; // 顶点颜色
layout(location = 2) in vec2 vTex; // 顶点纹理坐标

out vec4 color; // 传递给片段着色器的颜色
out vec2 tex; // 顶点纹理坐标

void main() {
    gl_Position = MVP * vec4(vPos, 0.0, 1.0); // 计算顶点位置
    color = vCol; // 传递颜色到片段着色器
    tex = vTex;
}