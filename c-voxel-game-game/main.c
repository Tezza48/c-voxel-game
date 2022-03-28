#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "assets.h"

#include "app.h"
#include "renderer.h"

typedef struct game_context
{
    GLuint triangle_shader_program;
} game_context;

//void on_start(game_context *game)
//{
//    glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
//
//    // Loading test shaders for displaying a triangle on screen.
//    GLuint program = glCreateProgram();
//    GLuint vertex_shader;
//    result vertex_shader_result = assets_load_gl_shader_GLuint(
//        "assets/shader/shader_test_triangle_vertex.glsl",
//        GL_VERTEX_SHADER);
//    result_unwrap(vertex_shader_result, &vertex_shader);
//
//    GLuint fragment_shader;
//    result fragment_shader_result = assets_load_gl_shader_GLuint(
//        "assets/shader/shader_test_triangle_fragment.glsl",
//        GL_FRAGMENT_SHADER);
//    result_unwrap(fragment_shader_result, &fragment_shader);
//
//    glAttachShader(program, vertex_shader);
//    glAttachShader(program, fragment_shader);
//    glLinkProgram(program);
//
//    game->triangle_shader_program = program;
//}
//
//void on_update(game_context *game)
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glUseProgram(game->triangle_shader_program);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//}

typedef struct file_read_result {
    char* string_ptr;
    size_t string_length;
} file_read_result;

file_read_result read_file_to_string(const char* path) {
    FILE* file;
    fopen_s(&file, path, "r");

    if (!file) {
        puts("Failed to open file");
        exit(-1);
    }

    fseek(file, 0, SEEK_END);
    size_t file_length = ftell(file);
    rewind(file);

    char* string_ptr = calloc(file_length + 1, sizeof(char));
    if (!string_ptr) {
        puts("For some reason buffer's not allocated");
        exit(-1);
    }
    fread(string_ptr, sizeof(char), file_length, file);

    fclose(file);

    return (file_read_result){
        .string_ptr = string_ptr,
        .string_length = file_length,
    };
}

void main(void)
{
    app_t* app = app_create((app_create_info_t) {
        .window_title = "c-voxel-app",
    });

    renderer_t* renderer = renderer_create(app);

    renderer_set_clear_color(color_create_rgba(1.0, 0.5, 0.25, 1.0));

    file_read_result v_source = read_file_to_string("assets/shader/shader_test_triangle_vertex.glsl");
    file_read_result f_source = read_file_to_string("assets/shader/shader_test_triangle_fragment.glsl");
    render_pipeline_desc_t pipeline_desc = {
        .vertex_source_ptr = v_source.string_ptr,
        .vertex_source_length = v_source.string_length,
        .fragment_source_ptr = f_source.string_ptr,
        .fragment_source_length = f_source.string_length,
    };
    render_pipeline_t* pipeline = render_pipeline_create(renderer, &pipeline_desc);
    free(v_source.string_ptr);
    free(f_source.string_ptr);

    while (app_is_running(app)) {
        app_check_events(app);

        renderer_clear(renderer);

        //renderer_set_render_pipeline(renderer, pipeline);
        glUseProgram(pipeline->_program);

        //renderer_draw_vertices(renderer, 0, 3, 1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        renderer_present(renderer, app);
    }

    render_pipeline_destroy(pipeline);

    renderer_destroy(renderer);

    app_destroy(app);
}