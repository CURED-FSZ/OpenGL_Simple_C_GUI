//
// Created by 冯帅真 on 2025/12/20.
//
#include "renderer.h"

// OpenGL / GLFW
#include <../third_party/glad/include/gl.h>
#include <../third_party/glfw/include/GLFW/glfw3.h>
#include <fstream>

#include "gui.h"
#include <../third_party/linmath/linmath.h>
#include "types.h"

const char* vertex_shader_text = R"(#version 460
uniform mat4 MVP;

layout(location = 0) in vec2 vPos;
layout(location = 1) in vec4 vCol;
layout(location = 2) in vec2 vTex;

out vec4 color;
out vec2 tex;

void main() {
    gl_Position = MVP * vec4(vPos, 0.0, 1.0);
    color = vCol;
    tex = vTex;
})";
const char* fragment_shader_text = R"(#version 460

in vec4 color;
in vec2 tex;

uniform sampler2D tex_sampler;
uniform bool use_texture;

out vec4 fragment;

void main() {
    if(use_texture){
        vec4 tex_color = texture(tex_sampler, tex);
        fragment = vec4(color.rgb, color.a * tex_color.a);
    }
    else {
        fragment = color;
    }
})";


Renderer::Renderer(const gui::GUI &gui, const Color background) {
    const auto [x, y] = gui.get_window_size();
    width_ = static_cast<int>(x);
    height_ = static_cast<int>(y);
    background_ = background;
    window_ = gui.get_window();

    create_program();

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    // pos (XY)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void *>(offsetof(Vertex, pos))
    );

    // color (RGBA)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void *>(offsetof(Vertex, col))
    );

    // uv (XY)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,                  // location = 2
        2,                  // vec2
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void *>(offsetof(Vertex, uv))
    );

    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::set_background(const Color color) {
    background_ = color;
}

void Renderer::begin_frame() const {
    glViewport(0, 0, width_, height_);
    glClearColor(background_.r, background_.g, background_.b, background_.a);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program_);

    // 2. sampler2D 绑定到 0 号纹理单元
    const GLint samplerLoc = glGetUniformLocation(program_, "tex_sampler");
    glUniform1i(samplerLoc, 0);

    // 正交投影
    linmath::mat4x4 mvp;
    linmath::mat4x4 proj;
    linmath::mat4x4_identity(mvp);

    linmath::mat4x4_ortho(
        proj,
        0.f, static_cast<float>(width_),
        static_cast<float>(height_), 0.f,
        -1.f, 1.f
    );

    linmath::mat4x4_mul(mvp, proj, mvp);

    glUniformMatrix4fv(
        mvp_location_,
        1,
        GL_FALSE,
        reinterpret_cast<float *>(mvp));

    GLint linked = 0;
    glGetProgramiv(program_, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint len = 0; glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &len);
        std::string log(len, '\0');
        glGetProgramInfoLog(program_, len, nullptr, log.data());
        printf("Program link failed:\n%s\n", log.c_str());
    }
}

void Renderer::beginText(const unsigned int tex) const {
    glUseProgram(program_);

    glUniform1i(glGetUniformLocation(program_, "use_texture"), 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    glUniform1i(glGetUniformLocation(program_, "tex_sampler"), 0);
}

void Renderer::beginGui() const {
    glUseProgram(program_);
    glUniform1i(glGetUniformLocation(program_, "use_texture"), 0);
}

void Renderer::beginGuiTextured(const unsigned int tex) const {
    glUseProgram(program_);
    glUniform1i(glGetUniformLocation(program_, "use_texture"), 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(glGetUniformLocation(program_, "tex_sampler"), 0);
}

void Renderer::draw(const Vertex *vertices, const std::size_t count) const {
    if (count == 0) return;

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(count * sizeof(Vertex)),
        vertices,
        GL_DYNAMIC_DRAW
    );

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(count));
}

void Renderer::end_frame() const {
    glBindVertexArray(0);
    if (window_ == nullptr) {
        printf("windows is null!\n");
    }
    glfwSwapBuffers(window_);
}

void Renderer::create_program() {
    auto compile = [](const GLenum type, const char *src) {
        const GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &src, nullptr);
        glCompileShader(s);
        return s;
    };

    const GLuint v = compile(GL_VERTEX_SHADER, vertex_shader_text);
    const GLuint f = compile(GL_FRAGMENT_SHADER, fragment_shader_text);

    program_ = glCreateProgram();
    glAttachShader(program_, v);
    glAttachShader(program_, f);
    glLinkProgram(program_);

    glDeleteShader(v);
    glDeleteShader(f);

    mvp_location_ = glGetUniformLocation(program_, "MVP");
}
