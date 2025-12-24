#version 460

in vec4 color; // 从顶点着色器传入的颜色
in vec2 tex; // 纹理坐标

uniform sampler2D tex_sampler; // 纹理采样器
uniform bool use_texture; // 是否使用纹理

out vec4 fragment; // 输出到屏幕的片段颜色

void main() {
    if(use_texture){
        vec4 tex_color = texture(tex_sampler, tex); // 获取纹理颜色
        fragment = vec4(color.rgb, color.a * tex_color.a); // 混合颜色
    }
    else {
        fragment = color; // 否则直接使用颜色
    }
}