// 定义GLAD实现，用于加载OpenGL函数指针
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

// 确保GLFW不会包含OpenGL头文件，因为我们使用的是glad
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// 包含标准输入输出流库，用于打印信息到控制台
#include <iostream>

// 包含线性数学库，提供矩阵和向量运算功能
#include <linmath.h>

#include <fstream>
#include <sstream>

/**
 * @brief 顶点结构体，定义了一个顶点的数据格式
 * 
 * 每个顶点包含两个属性：
 * - pos: 二维位置坐标 (x, y)
 * - col: RGB颜色值 (r, g, b)
 */
struct Vertex {
    vec2 pos;  // 顶点的二维位置坐标
    vec3 col;  // 顶点的颜色值（RGB格式）
};

// 定义三角形的三个顶点数据，使用constexpr表示这些数据在编译时就确定
// 每个顶点包含位置和颜色信息：
static constexpr Vertex vertices[6] =
{
    { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
    { {  0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
    { {  0.6f,  0.4f }, { 1.f, 0.f, 0.f } },

    { { -0.6f,  0.4f }, { 0.f, 0.f, 1.f } },
    { { -0.6f, -0.4f }, { 0.f, 0.f, 1.f } },
    { {  0.6f,  0.4f }, { 0.f, 0.f, 1.f } }
};

/*
static constexpr unsigned int indices[] = {
    0, 1, 2,   // 第一个三角形
    2, 3, 0    // 第二个三角形
};
*/


/**
 * @brief GLFW错误回调函数
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
 * 
 * @param window 发生事件的窗口对象
 * @param key 被按下的键
 * @param scancode 平台特定的扫描码
 * @param action 按键动作（按下、释放或重复）
 * @param mods 修饰键状态（如SHIFT、CTRL等）
 */
static void key_callback(GLFWwindow *window, const int key, int scancode, const int action, int mods) {
    // 检查是否按下了ESC键且动作为按下（而非释放）
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        // 输出提示信息到控制台
        std::cout << "ESC key pressed";

        // 设置窗口应该关闭的标志，这将在渲染循环中被检查
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

/**
 * @brief 程序主函数
 * 
 * 初始化OpenGL环境，创建窗口，设置渲染管线，并进入渲染循环
 * 
 * @return 程序退出状态码
 */
int main() {
    std::fstream file1("shader/vert.vert");
    if (!file1.is_open()) {
        std::cerr << "Failed to open vertex shader file." << std::endl;
        return -1;
    }
    std::fstream file2("shader/frag.frag");
    if (!file2.is_open()) {
        std::cerr << "Failed to open fragment shader file." << std::endl;
        return -1;
    }
    std::stringstream buffer1;
    std::stringstream buffer2;
    buffer1 << file1.rdbuf();
    buffer2 << file2.rdbuf();
    std::string source1 = buffer1.str();
    std::string source2 = buffer2.str();

    // 读取顶点着色器文件内容到字符串
    static const char *vertex_shader_text = source1.c_str();
    static const char* fragment_shader_text = source2.c_str();


    // 初始化GLFW库
    if (!glfwInit())
        return -1;

    // 设置GLFW的错误回调函数，这样当GLFW内部发生错误时会调用我们定义的error_callback函数
    glfwSetErrorCallback(error_callback);

    // 配置GLFW，指定我们要使用的OpenGL版本和配置
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);      // 主版本号为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);      // 次版本号为3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 使用OpenGL核心配置文件


    GLFWwindow* window = glfwCreateWindow(
        800, 600,
        "Hello OpenGL",
        nullptr,
        nullptr);

    // 检查窗口是否创建成功
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // 设置窗口的键盘按键回调函数
    glfwSetKeyCallback(window, key_callback);

    // 设置当前OpenGL上下文为该窗口的上下文
    glfwMakeContextCurrent(window);
    
    // 加载OpenGL函数指针（通过glad库）
    gladLoadGL(glfwGetProcAddress);
    
    // 启用垂直同步（V-Sync）
    glfwSwapInterval(1);

    // 创建一个OpenGL缓冲区对象来存储顶点数据
    GLuint vertex_buffer;                              // 声明缓冲区对象ID
    glGenBuffers(1, &vertex_buffer);                   // 生成一个缓冲区对象
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);      // 绑定缓冲区对象为目标（顶点数组缓冲区）
    // 将顶点数据上传到GPU显存中
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW);

    // 编译顶点着色器
    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);          // 创建顶点着色器对象
    glShaderSource(vertex_shader,
        1,
        &vertex_shader_text,
        nullptr);         // 设置着色器源代码
    glCompileShader(vertex_shader);    // 编译着色器

    // 编译片元着色器
    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);      // 创建片元着色器对象
    glShaderSource(fragment_shader,
        1,
        &fragment_shader_text,
        nullptr);     // 设置着色器源代码
    glCompileShader(fragment_shader);   // 编译着色器

    // 创建着色器程序并链接着色器
    const GLuint program = glCreateProgram();   // 创建程序对象
    glAttachShader(program, vertex_shader);     // 将顶点着色器附加到程序
    glAttachShader(program, fragment_shader);   // 将片元着色器附加到程序
    glLinkProgram(program);                     // 链接着色器程序

    // 获取着色器程序中各个变量的位置（句柄），以便后续可以设置它们的值
    const GLint mvp_location = glGetUniformLocation(program, "MVP");        // MVP矩阵统一变量位置
    const GLint vpos_location = glGetAttribLocation(program, "vPos");       // 顶点位置属性位置
    const GLint vcol_location = glGetAttribLocation(program, "vCol");       // 顶点颜色属性位置

    // 创建并设置顶点数组对象（VAO）
    GLuint vertex_array;     // 声明VAO对象ID
    glGenVertexArrays(1, &vertex_array);  // 生成一个VAO对象
    glBindVertexArray(vertex_array);       // 绑定VAO对象
    
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
        const float ratio = static_cast<float>(width) / static_cast<float>(height);            // 计算宽高比

        // 设置视口，告诉OpenGL如何将标准化设备坐标映射到屏幕像素
        glViewport(0, 0, width, height);
        
        // 清除颜色缓冲区，为新的一帧做准备
        glClear(GL_COLOR_BUFFER_BIT);

        // 创建和设置变换矩阵
        mat4x4 m, p, mvp;                                                  // 模型、投影和最终的MVP矩阵
        
        // 初始化模型矩阵为单位矩阵
        mat4x4_identity(m);
        
        // 创建正交投影矩阵，参数分别为左右上下远近裁剪面
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        
        // 计算最终的MVP矩阵（投影矩阵 × 模型矩阵）
        mat4x4_mul(mvp, p, m);

        // 使用我们编译好的着色器程序
        glUseProgram(program);
        
        // 将计算好的MVP矩阵传递给着色器程序中的统一变量
        glUniformMatrix4fv(mvp_location,
                           1,
                           GL_FALSE,
                           reinterpret_cast<const GLfloat *>(&mvp));

        // 绑定VAO，准备绘制
        glDrawArrays(GL_TRIANGLES,
                     0,
                     6);

        // 交换前后缓冲区，显示新绘制的帧
        glfwSwapBuffers(window);
        
        // 处理事件队列中的所有事件（如键盘输入、鼠标移动等）
        glfwPollEvents();
    }

    // 渲染循环结束后清理资源
    glfwDestroyWindow(window); // 销毁窗口

    // 清理并关闭GLFW
    glfwTerminate();

    // 正常退出程序
    exit(EXIT_SUCCESS);
}