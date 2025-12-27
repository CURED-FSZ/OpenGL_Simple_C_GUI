//
// Created by f1779 on 2025/12/24.
//

#ifndef OSCGUI_COMPONENTS_H
#define OSCGUI_COMPONENTS_H
#include <string>
#include "Text.h"
#include "types.h"

namespace components {
    // 组件状态
    enum class ComponentState {
        Normal, // 默认
        Hovered, // 鼠标在上面（你叫 enter）
        Pressed, // 鼠标按下
        Disabled // 可选，后期再加
    };

    // 组件基类
    class Component {
    public:
        virtual ~Component() = default;

        std::string id;

        // ===== 几何属性 =====
        vec2 position{}; // 左上角
        vec2 size{}; // 宽高

        // ===== 状态 =====
        ComponentState state = ComponentState::Normal;

        // ===== 可见性 / 可用性 =====
        bool visible = true;
        bool enabled = true;

        // ===== 点击事件 =====
        void (*OnClick)() = nullptr;

        // ===== 核心接口 =====

        /**
         * 绘制 GUI
         * @param guiOut 输出缓冲区
         */
        virtual void drawGUI(std::vector<Vertex> &guiOut) const = 0;

        /**
         * 绘制文字
         * @param textOut 输出缓冲区
         */
        virtual void drawText(std::vector<Vertex> &textOut) const = 0;

        /**
         * 更新组件状态
         * @param mouse_pos 鼠标位置
         * @param mouse_down 鼠标是否按下
         */
        virtual void update(const vec2 &mouse_pos, bool mouse_down) = 0;

    protected:
        /**
         * @brief 鼠标是否在组件内
         *
         * 检查鼠标是否在组件内
         * @param p 鼠标位置
         * @return 鼠标是否在组件内
         */
        [[nodiscard]] bool contains(const vec2 &p) const;

        // 上一帧状态
        ComponentState prev_state = ComponentState::Normal;

        /**
        * @brief 点击事件
        *
        * 当组件被点击时调用
        */
        virtual void on_click();
    };

    // 按钮
    class Button : public Component {
    public:
        Button(const vec2 pos, const vec2 sz) {
            position = pos;
            size = sz;
        }

        // 按钮颜色（默认时）
        Color normal_color = colors::light_gray;
        // 按钮颜色（鼠标悬停时）
        Color hover_color = colors::gray;
        // 按钮颜色（鼠标按下时）
        Color pressed_color = colors::dark_gray;
        // 按钮文字颜色
        Color text_color = colors::black;

        /**
         * @brief 绘制按钮
         *
         * 绘制按钮的图形和文字
         * @param guiOut 输出缓冲区
         */
        void drawGUI(std::vector<Vertex> &guiOut) const override;

        /**
         * @brief 绘制按钮文字
         *
         * 绘制按钮的文字
         * @param textOut 输出缓冲区
         */
        void drawText(std::vector<Vertex> &textOut) const override;

        /**
         * @brief 更新按钮状态
         *
         * 更新按钮的状态，包括鼠标悬停、按下和点击事件
         * @param mouse_pos 鼠标位置
         * @param mouse_down 鼠标是否按下
         */
        void update(const vec2 &mouse_pos, bool mouse_down) override;

        /**
         * @brief 设置按钮字体
         *
         * @param font 按钮字体
         */
        void set_font(text::Font *font);

        /**
         * 设置按钮文字
         * @param text 按钮文字
         */
        void set_text(const std::string &text) const;

    private:
        text::Text *text_ = nullptr;
    };

    class Label : public Component {
    public:
        Label(const vec2 pos, const vec2 sz) {
            position = pos;
            size = sz;
        }

        // 标签文字颜色
        Color text_color = colors::black;

        /**
         * @brief 设置标签字体
         *
         * @param font 标签字体
         */
        void set_font(text::Font *font);

        void drawGUI(std::vector<Vertex> &guiOut) const override;

        void update(const vec2 &mouse_pos, bool mouse_down) override;

        /**
         * @brief 绘制标签文字
         *
         * 绘制标签的文字
         * @param textOut 输出缓冲区
         */
        void drawText(std::vector<Vertex> &textOut) const override;

        /**
         * 设置标签文字
         * @param text 标签文字
         */
        void set_text(const std::string &text) const;
    private:
        text::Text *text_ = nullptr;
    };

    class CheckBox : public Component {
    public:
        CheckBox(const vec2 pos, const vec2 sz) {
            position = pos;
            size = sz;
        }

        // 选框文字颜色
        Color text_color = colors::black;

        bool is_checked = false;

        /**
         * 绘制 GUI
         * @param guiOut 输出缓冲区
         */
        void drawGUI(std::vector<Vertex> &guiOut) const override;

        /**
         * 绘制文字
         * @param textOut 输出缓冲区
         */
        void drawText(std::vector<Vertex> &textOut) const override;

        /**
         * 更新组件状态
         * @param mouse_pos 鼠标位置
         * @param mouse_down 鼠标是否按下
         */
        void update(const vec2 &mouse_pos, bool mouse_down) override;

        /**
         * @brief 设置选框字体
         *
         * @param font 选框字体
         */
        void set_font(text::Font *font);

        /**
         * 设置选框文字
         * @param text 选框文字
         */
        void set_text(const std::string &text) const;

        void on_click() override;

    private:
        text::Text *text_ = nullptr;

    };
}

/**
 * @brief 获取文件内容
 *
 * 从给定的路径中读取文件内容，并返回一个字符串
 * @param path 文件路径
 * @return 文件内容字符串
 */
std::string get_file_content(const char *path);

#endif //OSCGUI_COMPONENTS_H

