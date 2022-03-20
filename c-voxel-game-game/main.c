#include <stdio.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdlib.h>

#include "result.h"

typedef struct Window {
    GLFWwindow* glfw_window;
} Window;

Result window_create_ptr(void) {
    if (!glfwInit()) {
        return result_make_error("Couldn't initialize glfw");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * glfw_window = glfwCreateWindow(640, 480, "Hello World!", 0, 0);
    if (!glfw_window) {
        const char* error;
        uint32_t error_code;
        while((error_code = glfwGetError(&error)) != GLEW_NO_ERROR) {
            printf("GLFW ERROR | %s\n", error);
        }

        return result_make_error("GLFW window creation failed");
    }

    glfwMakeContextCurrent(glfw_window);

    Window* window = malloc(sizeof(Window));
    window->glfw_window = glfw_window;

    return result_make_ok(window);
}

int window_should_window_close(Window* window) {
    return glfwWindowShouldClose(window->glfw_window);
}

void window_destroy(Window* window) {
    glfwDestroyWindow(window->glfw_window);
    glfwTerminate();

    free(window);
}

void window_swap_bffers(Window* window) {
    glfwSwapBuffers(window->glfw_window);
}

int main(void) {
    Result window_result = window_create_ptr();
    Window* window = result_unwrap(&window_result);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("%s", glewGetErrorString(err));

        exit(-1);
    }

    while (!window_should_window_close(window)) {
        glfwPollEvents();

        glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window_swap_bffers(window);
    }

    window_destroy(window);

	return 0;
}