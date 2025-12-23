// C / C++ Standard Library
#include <iostream>

// Project Internal
#include "based.h"
#include "gui.h"
#include "renderer.h"

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

/**
* @brief GLFW错误回调函数
*
* 当GLFW发生错误时会被调用，将错误信息打印到标准错误输出
* @param error 错误代码
* @param description 错误描述字符串
*/
static void error_callback(const int error, const char* description)
{
    // 将错误信息输出到标准错误流
    fprintf(stderr, "Error[%d]: %s\n", error, description);
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
    std::vector<Vertex> vertices;
    vertices.reserve(1024);

    init_gui();

    gui::GUI ui(800, 600, "Hello OpenGL", error_callback);
    ui.add(&btn);
    ui.add(&btn2);

    // 创建图标
    GLFWimage image{};
    static unsigned char pixels[32 * 32 * 4];
    image.width = 32;
    image.height = 32;
    image.pixels = pixels;

    const Renderer renderer(ui);

    // 设置窗口的键盘按键回调函数
    ui.set_keyCallback(key_callback);

    // 设置窗口图标
    ui.set_window_icon(1, &image);

    // 主渲染循环 - 持续运行直到窗口被要求关闭
    while (ui.should_render_loop()) {
        // 处理事件队列中的所有事件（如键盘输入、鼠标移动等）
        glfwPollEvents();

        vertices.clear();
        ui.update();
        ui.draw(vertices);

        renderer.begin_frame();
        renderer.draw(vertices.data(), vertices.size());
        renderer.end_frame();
    }

    ui.clear();

    // 正常退出程序
    exit(EXIT_SUCCESS);
}