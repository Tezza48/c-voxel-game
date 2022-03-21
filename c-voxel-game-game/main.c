#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "assets.h"

typedef struct result_uint32_t result_uint32_t;

typedef struct window_info
{
    GLFWwindow *glfw_window;
} window_info;

typedef enum
{
    WINDOW_RESULT_OK,
    WINDOW_RESULT_ERROR_GLFW,
} WINDOW_RESULT;

WINDOW_RESULT window_info_new(window_info *out_window_info)
{
    if (!glfwInit())
    {
        return WINDOW_RESULT_ERROR_GLFW;
    }

    // TODO WT: Currently my test triangle does not render in 4.6 (though is on the buffer in renderdoc) Investigate this.
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(1);

    GLFWwindow *glfw_window = glfwCreateWindow(640, 480, "Hello World!", 0, 0);
    if (!glfw_window)
    {
        const char *error;
        uint32_t error_code;
        while ((error_code = glfwGetError(&error)) != GLEW_NO_ERROR)
        {
            printf("GLFW ERROR | %s\n", error);
        }

        return WINDOW_RESULT_ERROR_GLFW;
    }

    glfwMakeContextCurrent(glfw_window);

    *out_window_info = (window_info){
        .glfw_window = glfw_window,
    };

    return WINDOW_RESULT_OK;
}

int window_info_should_window_close(window_info *window)
{
    return glfwWindowShouldClose(window->glfw_window);
}

void window_info_destroy(window_info *window)
{
    glfwDestroyWindow(window->glfw_window);
    glfwTerminate();
}

void window_info_swap_bffers(window_info* window) {
    glfwSwapBuffers(window->glfw_window);
}

void window_info_poll_events(window_info* _window) {
    glfwPollEvents();
}

int main(void)
{
    window_info window;
    WINDOW_RESULT window_result = window_info_new(&window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        printf("%s", glewGetErrorString(err));

        exit(-1);
    }

    printf("OPENGL LOADED: %s\n", glfwGetVersionString());

    glCullFace(GL_FALSE);

    // Loading test shaders for displaying a triangle on screen.
    GLint program = glCreateProgram();
    GLint vertex_shader;
    ASSETS_RESULT vertex_shader_result = assets_load_gl_shader(
        "assets/shader/shader_test_triangle_vertex.glsl",
        GL_VERTEX_SHADER,
        &vertex_shader);

    GLint fragment_shader;
    ASSETS_RESULT fragment_shader_result = assets_load_gl_shader(
        "assets/shader/shader_test_triangle_fragment.glsl",
        GL_FRAGMENT_SHADER,
        &fragment_shader);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glClearColor(0.39f, 0.58f, 0.92f, 1.0f);

    while (!window_info_should_window_close(&window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // game loop logic
        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window_info_swap_bffers(&window);
        window_info_poll_events(&window);
    }

    window_info_destroy(&window);

    return 0;
}