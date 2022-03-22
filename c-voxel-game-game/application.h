#pragma once

#include "result.h"

typedef void (*application_game_callback)(void* game_context);

typedef struct application_create_info {
    void* context;
    application_game_callback on_start;
    application_game_callback on_updated;
    char* window_title;
} application_create_info;

#if defined APPLICATION_GLFW_GLEW

result application_impl_glfw_glew(application_create_info create_info);
#define application application_impl_glfw_glew

#elif defined APPLICATION_WIN32_GLEW
// TODO WT: implement other backends

// result application_impl_win32_d3d11(application_create_info create_info);
// #define application application_impl_win32_d3d11

#endif
