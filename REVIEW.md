# oscgui 项目代码评审

## 项目亮点

1. **架构分层清晰** — C++ 内核 + C bridge + 公共头文件，三层分离干净
2. **CMake 构建规范** — 使用 PUBLIC/PRIVATE include、关闭第三方库无关选项、有 install target
3. **组件状态机设计合理** — Normal → Hovered → Pressed 状态转换逻辑正确
4. **README 文档完善** — 有路线图、功能表、构建说明，体现了项目管理意识
5. **C++20 + 严格编译警告** — `-Wall -Wextra -Wpedantic`，好习惯
6. **第三方库管理得当** — 全部 bundled，构建零依赖外部安装

作为大一项目，能做到这个程度很优秀。

---

## 需要改进的问题（按优先级排序）

### P0: 内存泄漏（必须修复）

**文件:** `src/components.cpp`, `src/components.h`

- `Button`、`Label`、`CheckBox` 在构造时 `new Text::Text(...)`，但没有析构函数来 `delete`
- `Component` 基类缺少虚析构函数（`virtual ~Component() = default;`）
- C bridge 层 `oscgui_*_create()` 分配的内存也没有对应的 `_destroy()` 函数

**修复方案：**
1. 给 `Component` 添加 `virtual ~Component()`
2. 将 `Text::Text*` 改为 `std::unique_ptr<Text::Text>`（推荐）
3. C API 添加 `oscgui_button_destroy()` 等释放函数

### P1: C Bridge 层的设计问题

**文件:** `src/extern/oscgui_components.cpp`

1. **结构体重复定义** — `oscgui_font` 在 `oscgui_app.cpp:24` 和 `oscgui_components.cpp:28` 各定义了一次，应提取到共用的内部头文件
2. **冗余的 dynamic_cast** — `oscgui_button_set_font()` 等函数中对同一个对象做了两次 cast
3. **const 正确性问题** — 一些函数签名接受 `const` 指针但实际修改了对象内部状态

### P2: 错误处理不足

- 字体加载失败时直接 `throw`，但 `App` 层没有 `catch`
- 很多函数假设指针非空但不做检查
- 建议至少在公共 C API 入口做 null 检查

### P3: 渲染性能可优化

**文件:** `src/renderer.cpp`, `src/app.cpp`

- 每帧清空并重建所有顶点数据（`guiVertices_.clear()`）
- 对于静态 UI，可缓存顶点数据，只在组件状态变化时重建

### P4: 小问题

- `src/extern/oscgui_components.cpp:140` — `oscgui_label_set_text_color()` 缺少 `extern "C"` 声明（bug）
- Shader 文件各 ~500 行，对当前功能来说偏长，可精简
- 只支持 ASCII 字符（硬编码 32-126），后续可扩展 Unicode
