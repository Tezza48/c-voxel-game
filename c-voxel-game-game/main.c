#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "result.h"
#include "assets.h"

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

// void window_swap_bffers(Window* window) {
//     glfwSwapBuffers(window->glfw_window);
// }

int main(void) {
    Result window_result = window_create_ptr();
    Window* window = result_unwrap(&window_result);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("%s", glewGetErrorString(err));

        exit(-1);
    }

    glCullFace(GL_FALSE);

    // Loading test shaders for displaying a triangle on screen.
    GLint program = glCreateProgram();
    Result vertex_shader_result = assets_load_gl_shader(
        "assets/shader/shader_test_triangle_vertex.glsl",
        GL_VERTEX_SHADER
    );
    GLint vertex_shader = result_unwrap_int32(&vertex_shader_result);

    Result fragment_shader_result = assets_load_gl_shader(
        "assets/shader/shader_test_triangle_fragment.glsl",
        GL_FRAGMENT_SHADER
    );
    GLint fragment_shader = result_unwrap_int32(&fragment_shader_result);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glClearColor(0.39f, 0.58f, 0.92f, 1.0f);

    while (!window_should_window_close(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // game loop logic
        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window->glfw_window);
        glfwPollEvents();
    }

    window_destroy(window);

	return 0;
}