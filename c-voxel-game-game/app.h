#pragma once
#include <stdint.h>
// ! Have to include glew first even though it's not used here.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct app_t {
    GLFWwindow* _window;
} app_t;

typedef struct app_create_info_t {
    char* window_title;
} app_create_info_t;

app_t* app_create(app_create_info_t create_info);
uint8_t app_is_running(app_t* app);
void app_check_events(app_t* app);
void app_destroy(app_t* app_ptr);


