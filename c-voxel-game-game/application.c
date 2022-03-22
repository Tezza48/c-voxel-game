#include "application.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

result application_impl_glfw_glew(application_create_info create_info)
{
    if (!glfwInit())
    {
        return result_err("Failed to initialize glfw");
    }

    // TODO WT: Currently my test triangle does not render in 4.6 (though is on the buffer in renderdoc) Investigate this.
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(1);

    const char *title = "c-voxel-game";
    if (create_info.window_title)
    {
        title = create_info.window_title;
    };

    GLFWwindow *window = glfwCreateWindow(640, 480, title, 0, 0);
    if (!window)
    {
        const char *error;
        uint32_t error_code;
        while ((error_code = glfwGetError(&error)) != GLFW_NO_ERROR)
        {
            printf("GLFW ERROR | %s\n", error);
        }

        return result_err("Failed to create glfw window");
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        printf("%s", glewGetErrorString(err));

        exit(-1);
    }

    printf("OPENGL LOADED: %s\n", glfwGetVersionString());

    if (create_info.on_start)
    {
        create_info.on_start(create_info.context);
    }

    while (!glfwWindowShouldClose(window))
    {
        if (create_info.on_updated)
        {
            create_info.on_updated(create_info.context);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return result_ok(0, 0);
}

// #include <Windows.h>
// result application_impl_win32_d3d11(application_create_info create_info) {

//     WNDCLASS wc = {
//         .
//     }

//     return result_ok(0, 0);
// }