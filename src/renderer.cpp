//
// Created by 冯帅真 on 2025/12/20.
//
#include "renderer.h"

// OpenGL / GLFW
#define GLAD_GL_IMPLEMENTATION
#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "gui.h"
#include "linmath.h"

/**
 * @brief 获取文件内容
 *
 * 从给定的路径中读取文件内容，并返回一个字符串
 * @param path 文件路径
 * @return 文件内容字符串
 */
std::string get_file_content(const char *path) {
    const std::ifstream file(path);
    if (!file)
        throw std::runtime_error("failed to open file");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

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

void Renderer::begin_frame() const {
    glViewport(0, 0, width_, height_);
    glClearColor(background_.r, background_.g, background_.b, background_.a);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program_);

    // 1. use_texture（先写死 false / true 都行）
    const GLint useTexLoc = glGetUniformLocation(program_, "use_texture");
    glUniform1i(useTexLoc, 0); // 现在你的 GUI 还没用纹理，先关掉

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
    const std::string vert = get_file_content("shader/vert.vert");
    const std::string frag = get_file_content("shader/frag.frag");
    // 读取顶点着色器文件内容到字符串
    const char *vertex_shader_text = vert.c_str();
    const char *fragment_shader_text = frag.c_str();

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
