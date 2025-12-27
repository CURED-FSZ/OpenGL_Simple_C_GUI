//
// Created by f1779 on 2025/12/26.
//

#pragma once
#include <oscgui_types.h>

#ifdef __cplusplus
extern "C" {
#endif

    oscgui_app* oscgui_app_create(int w, int h, const char* title);

    void oscgui_app_run(const oscgui_app* app);

    void oscgui_app_set_window_icon(const oscgui_app* app, const char* path);

    void oscgui_app_set_window_background(const oscgui_app* app, oscgui_color color);

    /* 注册 init_gui */
    void oscgui_app_set_init_gui(oscgui_app* app, oscgui_init_gui fn);


#ifdef __cplusplus
}
#endif