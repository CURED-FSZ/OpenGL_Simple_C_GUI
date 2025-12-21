#version 460
in vec4 color; // 从顶点着色器传入的颜色
out vec4 fragment; // 输出到屏幕的片段颜色

void main() {
    fragment = color; // 设置片段颜色
}