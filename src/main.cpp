// ========================
// OpenGL / GLFW
// ========================
#define GLAD_GL_IMPLEMENTATION
#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// ========================
// C / C++ Standard Library
// ========================
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// ========================
// Math
// ========================
#include <linmath.h>

// ========================
// Project Internal
// ========================
#include "based.h"
#include "gui.h"

/**
 * @brief GLFW错误回调函数
 *
 * 当GLFW发生错误时会被调用，将错误信息打印到标准错误输出
 * @param error 错误代码
 * @param description 错误描述字符串
 */
static void error_callback(int error, const char* description)
{
    // 将错误信息输出到标准错误流
    fprintf(stderr, "Error: %s\n", description);
}

/**
 * @brief 键盘按键回调函数
 *
 * 处理键盘输入事件，当用户按下ESC键时关闭窗口
 * @param window 发生事件的窗口对象
 * @param key 被按下的键
 * @param scancode 平台特定的扫描码
 * @param action 按键动作（按下、释放或重复）
 * @param mods 修饰键状态（如SHIFT、CTRL等）
 */
static void key_callback(GLFWwindow* window, const int key, int scancode, const int action, int mods)
{
    // 检查是否按下了ESC键且动作为按下（而非释放）
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        // 输出提示信息到控制台
        std::cout << "ESC key pressed\n";

        // 设置窗口应该关闭的标志，这将在渲染循环中被检查
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// 初始化GLFW库并设置相关选项
void init_GLFW()
{
    // 初始化GLFW库
    if (!glfwInit())
        return;

    // 设置GLFW的错误回调函数
    glfwSetErrorCallback(error_callback);

    // 配置GLFW，指定使用的OpenGL版本和配置
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

/**
 * @brief 创建窗口
 *
 * 创建一个窗口，并设置其标题和初始大小
 * @param w 窗口宽度
 * @param h 窗口高度
 * @param title 窗口标题
 * @return 创建的窗口对象指针
 */
GLFWwindow* create_window(const int w, const int h, const char* title)
{
    init_GLFW();

    // 创建窗口前：告诉 GLFW，窗口先别显示
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (!window)
        return nullptr;

    // 获取主显示器
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // 计算窗口居中位置
    glfwSetWindowPos(
        window,
        (mode->width  - w) / 2,
        (mode->height - h) / 2
    );

    // 固定窗口大小
    glfwSetWindowSizeLimits(window, w, h, w, h);

    // 设置当前OpenGL上下文
    glfwMakeContextCurrent(window);

    // 启用垂直同步（V-Sync）
    glfwSwapInterval(1);

    // 显示窗口
    glfwShowWindow(window);

    return window;
}

/**
 * @brief 获取文件内容
 *
 * 从给定的路径中读取文件内容，并返回一个字符串
 * @param path 文件路径
 * @return 文件内容字符串
 */
std::string get_file_content(const char* path)
{
    const std::ifstream file(path);
    if (!file)
        throw std::runtime_error("failed to open file");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/**
 * @brief 创建着色器程序
 *
 * 创建一个着色器程序，并链接顶点着色器和片元着色器
 * @param vs_src 顶点着色器源代码
 * @param fs_src 片元着色器源代码
 * @return 创建的着色器程序对象ID
 */
GLuint create_program(const char* vs_src, const char* fs_src)
{
    // 创建顶点着色器
    const GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_src, nullptr);
    glCompileShader(vs);

    // 创建片元着色器
    const GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_src, nullptr);
    glCompileShader(fs);

    // 创建程序对象
    const GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    // 删除中间着色器对象
    glDeleteShader(vs);
    glDeleteShader(fs);

    return prog;
}

/**
 * @brief 计算投影矩阵和模型视图矩阵
 *
 * 计算投影矩阵和模型视图矩阵，并设置给定的矩阵
 * @param mvp 输出的矩阵
 * @param w 窗口宽度
 * @param h 窗口高度
 */
void calc_ortho_mvp(linmath::mat4x4 mvp, const int w, const int h)
{
    linmath::mat4x4 model, proj;
    linmath::mat4x4_identity(model);
    linmath::mat4x4_ortho(
        proj,
        0.0f, static_cast<float>(w),
        static_cast<float>(h), 0.0f,
        -1.0f, 1.0f
    );
    linmath::mat4x4_mul(mvp, proj, model);
}

components::Button btn;
components::Button btn2;

void click(components::Component* e) {
    std::cout << "click" << std::endl;
}

void click2(components::Component* e) {
    btn.normal_color = Colors::purple;
}

void init_gui() {
    btn.position = {300.f, 300.f};
    btn.size = {100.f, 50.f};
    btn.normal_color = Colors::white;
    btn.hover_color = Colors::red;
    btn.pressed_color = Colors::blue;
    btn.OnClick = click;

    btn2.position = {400.f, 300.f};
    btn2.size = {100.f, 50.f};
    btn2.normal_color = Colors::white;
    btn2.hover_color = Colors::red;
    btn2.pressed_color = Colors::blue;
    btn2.OnClick = click2;
}
int main() {
    const std::string vert = get_file_content("shader/vert.vert");
    const std::string frag = get_file_content("shader/frag.frag");
    // 读取顶点着色器文件内容到字符串
    const char *vertex_shader_text = vert.c_str();
    const char* fragment_shader_text = frag.c_str();

    std::vector<Vertex> vertices;
    vertices.reserve(1024); // 给 GUI 用，避免频繁扩容

    // 创建窗口
    GLFWwindow* window = create_window(800, 600, "Hello OpenGL");

    init_gui();
    gui::GUI ui(window);
    ui.add(&btn);
    ui.add(&btn2);

    // 创建图标
    GLFWimage image{};
    static unsigned char pixels[32 * 32 * 4];
    image.width = 32;
    image.height = 32;
    image.pixels = pixels;

    // 设置窗口的键盘按键回调函数
    glfwSetKeyCallback(window, key_callback);

    // 设置窗口图标
    glfwSetWindowIcon(window, 1, &image);

    // 加载OpenGL函数指针（通过glad库）
    gladLoadGL(glfwGetProcAddress);

    // 创建着色器程序并链接着色器
    const GLuint program = create_program(vertex_shader_text, fragment_shader_text);

    // 获取着色器程序中各个变量的位置（句柄），以便后续可以设置它们的值
    const GLint mvp_location = glGetUniformLocation(program, "MVP");        // MVP矩阵统一变量位置
    const GLint vpos_location = glGetAttribLocation(program, "vPos");       // 顶点位置属性位置
    const GLint vcol_location = glGetAttribLocation(program, "vCol");       // 顶点颜色属性位置

    // 创建并设置顶点数组对象（VAO）
    GLuint vertex_array;     // 声明VAO对象ID
    glGenVertexArrays(1, &vertex_array);  // 生成一个VAO对象
    glBindVertexArray(vertex_array);       // 绑定VAO对象

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    
    // 启用顶点属性数组并设置其格式
    glEnableVertexAttribArray(vpos_location); // 启用位置属性数组
    // 设置位置属性的格式和来源
    glVertexAttribPointer(vpos_location,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, pos)));
    
    // 颜色属性设置
    glEnableVertexAttribArray(vcol_location); // 启用颜色属性数组
    // 设置颜色属性的格式和来源
    glVertexAttribPointer(vcol_location,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, col)));

    // 主渲染循环 - 持续运行直到窗口被要求关闭
    while (!glfwWindowShouldClose(window)) {
        // 获取帧缓冲区的尺寸，用于处理窗口大小变化和计算宽高比
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // 设置视口，告诉OpenGL如何将标准化设备坐标映射到屏幕像素
        glViewport(0, 0, width, height);
        
        // 清除颜色缓冲区，为新的一帧做准备
        glClear(GL_COLOR_BUFFER_BIT);
        vertices.clear();

        // 处理事件队列中的所有事件（如键盘输入、鼠标移动等）
        glfwPollEvents();

        ui.update();
        ui.draw(vertices);

        // 2️⃣ 上传到 GPU
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)),
            vertices.data(),
            GL_DYNAMIC_DRAW
        );

        // 创建和设置变换矩阵
        linmath::mat4x4 mvp;  // 模型、投影和最终的MVP矩阵

        calc_ortho_mvp(mvp, width, height);

        // 3️⃣ 设置变换 & 画
        glUseProgram(program);
        glUniformMatrix4fv(
            mvp_location,
            1,
            GL_FALSE,
            reinterpret_cast<const GLfloat*>(&mvp)
        );

        glBindVertexArray(vertex_array);
        glDrawArrays(
            GL_TRIANGLES,
            0,
            static_cast<GLsizei>(vertices.size())
        );

        // 交换前后缓冲区，显示新绘制的帧
        glfwSwapBuffers(window);
    }

    // 渲染循环结束后清理资源
    glfwDestroyWindow(window); // 销毁窗口

    // 清理并关闭GLFW
    glfwTerminate();

    // 正常退出程序
    exit(EXIT_SUCCESS);
}