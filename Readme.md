<div align="center">

<img src="img/oscgui_256.png" width="256" height="256" alt="oscgui logo">

### OpenGL - Simple C GUI Library
一个 **简单、可控、可学习** 的 OpenGL GUI 库  

---

</div>

## oscgui 是什么？

**oscgui** 是一个 **学习导向的 OpenGL GUI 实验项目**，
主要用于探索：**一个 GUI 库从零是如何被设计和实现的**。

它不是一个生产级 GUI 框架，也不试图成为其中之一，它是 ：

- 帮助你理解 GUI 系统是如何从零搭建的
- 展示一个 GUI 库在工程层面应该如何拆分模块
- 作为 C / C++ / OpenGL 学习者的参考实现

> ⚠️ 重要提示  
> 如果你在找一个“能直接用在项目里的成熟 GUI 框架”，  
> 请直接使用 ImGui / Qt / GTK。  
> oscgui 更适合 **阅读、修改、重构和学习**。

由于作者仍在学习阶段， oscgui 的内部实现仅代表个人理解，并不声称是最佳实践。

当前版本 v0.1.0，支持基本的 UI 组件，如按钮、标签和复选框。库使用 GLFW 作为窗口管理器，并内置了所有依赖，便于快速上手。

## 特性
- C / C++ 双 API（通过 C 桥接）
- 基于 OpenGL 4.4 + GLFW
- 内置字体与基础资源，开箱即用
- 以可读性优先的实现风格

## 依赖
- GLFW（已包含在 third_party/glfw 中）。
- OpenGL 4.4+（运行时需要）。
- CMake 3.1+（构建工具）。

## 功能支持计划
会随项目条件而变化，且功能也会随着版本更新而完善。

| 版本\功能 | 静态组件 | z-Order支持 | Unicode 支持 | 动态组件 | 圆角支持 | 动态布局支持 | 多窗口支持 | 动画支持 | 自定义样式支持 | 自定义控件支持 | 插件支持 |
|:-----:|:----:|:---------:|:----------:|:----:|:----:|:------:|:-----:|:----:|:-------:|:-------:|:----:|
| v 0.1 |  √   |     x     |     x      |  x   |  x   |   x    |   x   |  x   |    x    |    x    |  x   |
| v 0.2 |  √   |     √     |     √      |  √   |  √   |   x    |   x   |  x   |    x    |    x    |  x   |
| v 0.3 |  √   |     √     |     √      |  √   |  √   |   √    |   √   |  x   |    x    |    x    |  x   |
| v 0.4 |  √   |     √     |     √      |  √   |  √   |   √    |   √   |  √   |    √    |    √    |  √   |

## 原生组件支持计划
会随项目条件而变化，且组件功能也会随着版本更新而完善。

| 版本\组件 | 按钮 | 标签 | 复选框 | 输入框 | 图片 | 下拉菜单 | 滚动栏 | 滑块 | 消息弹窗 | 工具栏 | 画板 |
|:-----:|:--:|:--:|:---:|:---:|:--:|:----:|:---:|:--:|:----:|:---:|:--:|
| v 0.1 | √  | √  |  √  |  x  | x  |  x   |  x  | x  |  x   |  x  | x  |
| v 0.2 | √  | √  |  √  |  √  | √  |  x   |  x  | x  |  x   |  x  | x  |
| v 0.3 | √  | √  |  √  |  √  | √  |  √   |  √  | √  |  √   |  x  | x  |
| v 0.4 | √  | √  |  √  |  √  | √  |  √   |  √  | √  |  √   |  √  | √  |

## oscgui v 1.0 构想
### 1. 资源内置策略
用户可以自行添加字体、图标以及其他种类的资源，并支持动态加载卸载。
### 2. 控件树结构
支持组件树结构，用户可以自定义控件的层级关系。

## 构建和安装
1. 克隆仓库：
   ```
   git clone https://github.com/CURED-FSZ/OpenGL_Simple_C_GUI.git
   cd oscgui
   ```
2. 使用 CMake 构建：
   ```
   mkdir build && cd build
   cmake ..
   cmake --build .
   cmake --install .
   ```
    - 这会生成静态库 `liboscgui.a`（或 Windows 的 .lib），并安装到当前目录（可自定义 `CMAKE_INSTALL_PREFIX`）。
    - 安装后，库文件在 `lib/`，头文件在 `include/`，字体和图标在 `font/` 和 `img/`。

如果只想使用库，推荐直接拉取示例项目：
```
git clone https://github.com/CURED-FSZ/OpenGL_Simple_C_GUI/oscgui_example.git
cd oscgui_example
mkdir build && cd build
cmake ..
cmake --build .
```
- 示例项目已包含 CMake 配置，直接运行可看到 demo。

如果你的目标是学习或体验 oscgui，
推荐直接从示例项目开始，而不是直接链接库。

## 使用示例
### C 示例（使用桥接）
```c++
#include <oscgui_app.h>
#include <oscgui_types.h>
#include <oscgui_components.h>
#include <oscgui_gui.h>

void on_button_click() {
    // 点击回调逻辑
}

void init_gui(const oscgui_gui* gui, const oscgui_font* font) {
    oscgui_button* btn = oscgui_button_create(100, 100, 200, 80);
    oscgui_button_set_font(btn, font);
    oscgui_button_set_text(btn, "Click me!");
    oscgui_button_set_on_click(btn, on_button_click);
    oscgui_gui_add(gui, oscgui_button_as_component(btn));
    // 添加其他组件...
}

int main() {
    oscgui_app* app = oscgui_app_create(800, 600, "Hello OSCGUI");
    oscgui_app_set_init_gui(app, init_gui);
    oscgui_app_set_window_icon(app, "img/oscgui_64.jpg");
    oscgui_app_set_window_background(app, (oscgui_color){0, 0, 0, 1});
    oscgui_app_run(app);
    return 0;
}
```

### C++ 示例（main.cpp）
```c++
#include "app.h"

App app(800, 600, "Hello OpenGL");

components::Button btn({100.f, 100.f}, {200.f, 80.f});
components::Button btn2({300.f, 300.f}, {300.f, 80.f});
components::Label label({100.f, 300.f}, {200.f, 80.f});
components::CheckBox checkbox({370.f, 100.f}, {350.f, 150.f});

void click() {
    if (checkbox.is_checked)
        btn2.set_text("checkbox save you!");
    else
        btn2.set_text("I was clicked!");
}

void click2() {
    btn2.set_text("");
}

void init_gui(gui::GUI* ui, text::Font* font) {
    btn.normal_color = colors::light_gray;
    btn.hover_color = colors::gray;
    btn.pressed_color = colors::dark_gray;
    btn.text_color = colors::black;
    btn.OnClick = click;
    btn.set_font(font);
    btn.set_text("Click me!");

    btn2.normal_color = colors::light_gray;
    btn2.hover_color = colors::gray;
    btn2.pressed_color = colors::dark_gray;
    btn2.text_color = colors::magenta;
    btn2.OnClick = click2;
    btn2.set_font(font);

    label.text_color = colors::light_gray;
    label.set_font(font);
    label.set_text("I'm a label!");

    checkbox.text_color = colors::light_gray;
    checkbox.set_font(font);
    checkbox.set_text("I'm a checkbox!");

    ui->add(&btn);
    ui->add(&btn2);
    ui->add(&label);
    ui->add(&checkbox);
}

int main() {
    app.set_gui(init_gui);
    app.set_window_icon("img/oscgui_64.jpg");
    app.set_window_background(colors::black);
    app.run();
    exit(EXIT_SUCCESS);
}
```

## 贡献
欢迎 PR！项目主要是学习用途，issue 请描述清楚问题。未来计划：添加更多组件（如 Slider、TextInput）、改进渲染性能。

## 许可证
MIT License