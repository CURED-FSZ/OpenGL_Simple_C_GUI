#include <iostream>

#include "app.h"

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

App app(800, 600, "Hello OpenGL", error_callback, key_callback);

components::Button btn({100.f, 100.f}, {200.f, 80.f});
components::Button btn2({300.f, 300.f}, {300.f, 80.f});

void click([[maybe_unused]] components::Component* e) {
    btn2.set_text("I was clicked!");
}

void click2([[maybe_unused]] components::Component* e) {
    //btn.normal_color = colors::purple;
    dynamic_cast<components::Button*>(e)->set_text("");
}

void init_gui(gui::GUI& ui, text::Font& font) {
    btn.normal_color = colors::light_gray;
    btn.hover_color = colors::gray;
    btn.pressed_color = colors::dark_gray;
    btn.text_color = colors::black;
    btn.OnClick = click;
    btn.set_font(&font);
    btn.set_text("Click me!");

    btn2.normal_color = colors::light_gray;
    btn2.hover_color = colors::gray;
    btn2.pressed_color = colors::dark_gray;
    btn2.text_color = colors::magenta;
    btn2.OnClick = click2;
    btn2.set_font(&font);

    ui.add(&btn);
    ui.add(&btn2);
}

int main() {
    app.set_gui(init_gui);
    app.set_window_background(colors::black);

    app.run();

    // 正常退出程序
    exit(EXIT_SUCCESS);
}