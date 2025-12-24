//
// Created by f1779 on 2025/12/23.
//

#ifndef OSCGUI_TEXT_H
#define OSCGUI_TEXT_H
#include <string>

#include "types.h"

namespace text {
    // 文本范围
    struct TextMetrics {
        float width;
        float height;
    };

    // 字符 glyph
    struct Glyph {
        int id; // ASCII / Unicode code
        float u0, v0; // 左上 UV
        float u1, v1; // 右下 UV

        float width; // glyph 宽度（像素）
        float height; // glyph 高度（像素）

        float x_offset; // 从当前 pen 到 glyph 的偏移
        float y_offset;
        float x_advance; // pen 前进量
    };

    // 字体类
    class Font {
    public:
        /**
         * @brief 构造函数
         *
         * @param fntPath 字体描述文件路径
         * @param pngPath 字体贴图路径
         */
        explicit Font(const std::string &fntPath,
                      const std::string &pngPath);

        /**
         * @brief 获取字符 glyph
         *
         * @param c 字符
         * @return const Glyph * 字符 glyph
         */
        [[nodiscard]] const Glyph *getGlyph(char c) const;

        /**
         * @brief 获取 OpenGL texture id
         *
         * @return unsigned int OpenGL texture id
         */
        [[nodiscard]] unsigned int texture() const; // OpenGL texture id

        /**
         * @brief 获取行高
         *
         * @return float 行高
         */
        [[nodiscard]] float lineHeight() const;

    private:
        static constexpr int FIRST = 32;
        static constexpr int LAST  = 126;
        static constexpr int COUNT = LAST - FIRST + 1;

        unsigned int texture_; // OpenGL texture id
        float atlasW_, atlasH_; // atlas 的宽高
        float lineHeight_; // 行高

        Glyph glyphs[COUNT]{}; // 字符 glyph
        bool  hasGlyph[COUNT]{}; // 是否有 glyph

        /**
         * @brief 加载字体描述文件
         *
         * @param path 字体描述文件路径
         */
        void loadFnt(const std::string &path);

        /**
         * @brief 加载字体贴图
         *
         * @param path 字体贴图路径
         */
        void loadTexture(const std::string &path);
    };

    // 文本类
    class Text {
    public:
        /**
         * @brief 构造函数
         *
         * @param font 字体
         */
        explicit Text(Font *font);

        /**
         * @brief 设置文本内容
         *
         * @param text 文本内容
         */
        void setString(const std::string &text);

        /**
         * @brief 设置文本位置
         *
         * @param x x 坐标
         * @param y y 坐标
         */
        void setPosition(float x, float y);

        /**
         * @brief 设置文本颜色
         *
         * @param c 颜色
         */
        void setColor(Color c);

        /**
         * @brief 设置文本缩放
         *
         * @param s 缩放比例
         */
        void setScale(float s);

        /**
         * @brief 绘制文本
         *
         * @param out 输出的顶点数组
         */
        void draw(std::vector<Vertex> &out) const;

        /**
         * @brief 测量文本范围
         *
         * @return TextMetrics 文本范围
         */
        [[nodiscard]] TextMetrics measure() const;

    private:
        Font *font_; // 不拥有
        std::string text_; // 文本内容

        vec2 pos_; // 位置
        float scale_ = 1.0f; // 缩放比例
        Color color_ = colors::white; // 颜色
    };
}

#endif //OSCGUI_TEXT_H
