//
// Created by f1779 on 2025/12/23.
//

#include <stdexcept>

#include "types.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <../third_party/glad/include/gl.h>
#include <sstream>

#include "components.h"
#include "Text.h"

text::Font::Font(const std::string& fntPath, const std::string& pngPath)
    : texture_(0),
      atlasW_(0.0f),
      atlasH_(0.0f),
      lineHeight_(0){
    // 创建所有字符的 glyph
    std::fill(std::begin(hasGlyph), std::end(hasGlyph), false);
    loadFnt(fntPath);
    loadTexture(pngPath);
}

void text::Font::loadTexture(const std::string& path) {
    int w, h, channels;

    // 加载字体贴图
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels =
        stbi_load(path.c_str(), &w, &h, &channels, 4);

    if (!pixels) {
        throw std::runtime_error("failed to load font atlas png");
    }

    // 获取字体贴图的宽高
    atlasW_ = static_cast<float>(w);
    atlasH_ = static_cast<float>(h);

    // 创建字体贴图
    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);

    // 设置像素对齐
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // 设置字体贴图的参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // 上传字体贴图
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        w,
        h,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        pixels
    );

    // 释放内存
    stbi_image_free(pixels);
}

[[nodiscard]] const text::Glyph* text::Font::getGlyph(const char c) const {
    const int idx = c - FIRST;
    if (idx < 0 || idx >= COUNT) return nullptr;
    return hasGlyph[idx] ? &glyphs[idx] : nullptr;
}

[[nodiscard]] unsigned int text::Font::texture() const {
    return texture_;
}

[[nodiscard]] float text::Font::lineHeight() const {
    return lineHeight_;
}

void text::Font::loadFnt(const std::string& path) {
    // 读取字体描述文件
    std::string content = get_file_content(path.c_str());
    std::istringstream iss(content);
    std::string line;

    // 解析字体描述文件
    while (std::getline(iss, line)) {
        // 解析 common line
        if (line.rfind("common", 0) == 0) {
            std::istringstream ls(line);
            std::string token;
            while (ls >> token) {
                if (token.rfind("lineHeight=", 0) == 0)
                    lineHeight_ = static_cast<float>(std::stoi(token.substr(11)));
                else if (token.rfind("scaleW=", 0) == 0)
                    atlasW_ = std::stof(token.substr(7));
                else if (token.rfind("scaleH=", 0) == 0)
                    atlasH_ = std::stof(token.substr(7));
            }
        }

        // 解析 char line
        if (line.rfind("char ", 0) == 0) {
            Glyph g{};
            int x = 0, y = 0, w = 0, h = 0;

            std::istringstream ls(line);
            std::string token;

            while (ls >> token) {
                if (token.rfind("id=", 0) == 0)
                    g.id = std::stoi(token.substr(3));
                else if (token.rfind("x=", 0) == 0)
                    x = std::stoi(token.substr(2));
                else if (token.rfind("y=", 0) == 0)
                    y = std::stoi(token.substr(2));
                else if (token.rfind("width=", 0) == 0)
                    w = std::stoi(token.substr(6));
                else if (token.rfind("height=", 0) == 0)
                    h = std::stoi(token.substr(7));
                else if (token.rfind("xoffset=", 0) == 0)
                    g.x_offset = std::stof(token.substr(8));
                else if (token.rfind("yoffset=", 0) == 0)
                    g.y_offset = std::stof(token.substr(8));
                else if (token.rfind("xadvance=", 0) == 0)
                    g.x_advance = std::stof(token.substr(9));
            }

            // UV（注意 Y 翻转）
            g.u0 = static_cast<float>(x) / atlasW_;
            g.u1 = static_cast<float>(x + w) / atlasW_;
            g.v0 = 1.0f - static_cast<float>(y + h) / atlasH_;
            g.v1 = 1.0f - static_cast<float>(y) / atlasH_;

            // 宽高
            g.width  = static_cast<float>(w);
            g.height = static_cast<float>(h);

            // 添加 glyph
            if (int idx = g.id - FIRST; idx >= 0 && idx < COUNT) {
                glyphs[idx] = g;
                hasGlyph[idx] = true;
            }
        }
    }
}

text::Text::Text(Font* font)
    : font_(font),
      pos_{0.0f, 0.0f},
      color_(colors::white) {}

void text::Text::setString(const std::string& text) {
    text_ = text;
}

void text::Text::setPosition(const float x, const float y) {
    pos_ = {x, y};
}

void text::Text::setColor(const Color c) {
    color_ = c;
}

void text::Text::setScale(const float s) {
    scale_ = s;
}

void text::Text::draw(std::vector<Vertex>& out) const {
    if (!font_) return;

    float penX = pos_.x;
    float penY = pos_.y;

    for (const char c : text_) {
        if (c == '\n') {
            penX = pos_.x;
            penY += font_-> lineHeight() * scale_;
            continue;
        }

        const Glyph* g = font_->getGlyph(c);
        if (!g) continue;

        const float x = penX + g->x_offset * scale_;
        const float y = penY + g->y_offset * scale_;
        const float w = g->width  * scale_;
        const float h = g->height * scale_;

        // 四个顶点（左上开始，顺时针）
        Vertex v0{{x,     y},     {color_.r, color_.g, color_.b, color_.a}, {g->u0, g->v1}};
        Vertex v1{{x + w, y},     {color_.r, color_.g, color_.b, color_.a}, {g->u1, g->v1}};
        Vertex v2{{x + w, y + h}, {color_.r, color_.g, color_.b, color_.a}, {g->u1, g->v0}};
        Vertex v3{{x,     y + h}, {color_.r, color_.g, color_.b, color_.a}, {g->u0, g->v0}};

        // 两个三角形
        out.push_back(v0);
        out.push_back(v1);
        out.push_back(v2);

        out.push_back(v0);
        out.push_back(v2);
        out.push_back(v3);

        penX += g->x_advance * scale_;
    }
}

text::TextMetrics text::Text::measure() const {
    TextMetrics m{0.0f, 0.0f};

    if (!font_) return m;

    float lineWidth = 0.0f;
    float maxWidth = 0.0f;
    float totalHeight = font_->lineHeight();

    for (const char c : text_) {
        if (c == '\n') {
            maxWidth = std::max(maxWidth, lineWidth);
            lineWidth = 0.0f;
            totalHeight += font_->lineHeight();
            continue;
        }

        const Glyph* g = font_->getGlyph(c);
        if (!g) continue;

        lineWidth += g->x_advance;
    }

    maxWidth = std::max(maxWidth, lineWidth);

    m.width  = maxWidth;
    m.height = totalHeight;
    return m;
}