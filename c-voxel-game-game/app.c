#include "app.h"
#include <stdio.h>
#include <stdlib.h>

app_t* app_create(app_create_info_t create_info)
{
    app_t* app = calloc(1, sizeof(app_t));
    if (!glfwInit())
    {
        puts("Failed to initialize glfw");
        exit(-1);
    }

    // TODO WT: Currently my test triangle does not render in 4.6 (though is on the buffer in renderdoc) Investigate this.
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(1);

    GLFWwindow *window = glfwCreateWindow(640, 480, create_info.window_title, 0, 0);
    if (!window)
    {
        const char *error;
        uint32_t error_code;
        while ((error_code = glfwGetError(&error)) != GLFW_NO_ERROR)
        {
            printf("GLFW ERROR | %s\n", error);
        }

        puts("Failed to create glfw window");
        exit(-1);
    }

    app->_window = window;

    return app;
}

uint8_t app_is_running(app_t* app)
{
    return !glfwWindowShouldClose(app->_window);
}

void app_check_events(app_t* app)
{
    glfwPollEvents();
}

void app_destroy(app_t* app)
{
    glfwDestroyWindow(app->_window);
    glfwTerminate();

    free(app);
}

// #include <Windows.h>
// result application_impl_win32_d3d11(application_create_info create_info) {

//     WNDCLASS wc = {
//         .
//     }

//     return result_ok(0, 0);
// }