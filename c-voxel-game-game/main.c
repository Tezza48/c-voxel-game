#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "assets.h"

#include "result.h"

#define APPLICATION_GLFW_GLEW
#include "application.h"

typedef struct game_context
{
    GLuint triangle_shader_program;
} game_context;

void on_start(game_context *game)
{
    glClearColor(0.39f, 0.58f, 0.92f, 1.0f);

    // Loading test shaders for displaying a triangle on screen.
    GLuint program = glCreateProgram();
    GLuint vertex_shader;
    result vertex_shader_result = assets_load_gl_shader_GLuint(
        "assets/shader/shader_test_triangle_vertex.glsl",
        GL_VERTEX_SHADER);
    result_unwrap(vertex_shader_result, &vertex_shader);

    GLuint fragment_shader;
    result fragment_shader_result = assets_load_gl_shader_GLuint(
        "assets/shader/shader_test_triangle_fragment.glsl",
        GL_FRAGMENT_SHADER);
    result_unwrap(fragment_shader_result, &fragment_shader);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    game->triangle_shader_program = program;
}

void on_update(game_context *game)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(game->triangle_shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void main(void)
{
    result application_result = application((application_create_info){
        .context = &((game_context){0}),
        .on_start = on_start,
        .on_updated = on_update,
    });

    result_unwrap(application_result, 0);
}