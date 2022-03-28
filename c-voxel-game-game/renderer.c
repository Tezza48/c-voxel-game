#include "renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

renderer_t* renderer_create(app_t* app)
{
	renderer_t* renderer = calloc(1, sizeof(renderer_t));

	glfwMakeContextCurrent(app->_window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        printf("%s", glewGetErrorString(err));

        exit(-1);
    }

    printf("OPENGL LOADED: %s\n", glfwGetVersionString());

    return renderer;
}

void renderer_present(renderer_t* renderer, app_t* app)
{
    glfwSwapBuffers(app->_window);
}

void renderer_clear(renderer_t* renderer) {
    // TODO WT: This is going to need to be fleshed out to allow for clearing ANY framebuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_destroy(renderer_t* renderer)
{
    free(renderer);
}

void renderer_set_clear_color(color_t color)
{
    glClearColor(color.value[0], color.value[1], color.value[2], color.value[3]);
}
//
//#define COBJMACROS
//#include <d3d11.h>

void renderer_draw_vertices(renderer_t* renderer, uint32_t start_vertex, uint32_t vertex_count, uint32_t instance_count)
{
    //ID3D11DeviceContext_Draw(device, vertex_count, start_vertex);

    glDrawArrays(GL_TRIANGLES, start_vertex, vertex_count);
}

GLuint create_gl_shader(char* source_ptr, size_t source_length, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source_ptr, &source_length);
    glCompileShader(shader);

    GLuint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE) {
        GLint error_buffer_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &error_buffer_length);

        char* error_buffer_ptr = calloc(error_buffer_length + 1, sizeof(char));
        if (error_buffer_ptr) {
            glGetShaderInfoLog(shader, error_buffer_length, 0, error_buffer_ptr);

            printf("ERROR: error compiling shader | %s\n", source_ptr);
        
            puts(error_buffer_ptr);
            free(error_buffer_ptr);
        }


        glDeleteShader(shader);
        exit(-1);
    }

    return shader;
}

render_pipeline_t* render_pipeline_create(renderer_t* renderer, render_pipeline_desc_t* descriptor)
{
    GLuint v_shader = create_gl_shader(
        descriptor->vertex_source_ptr,
        descriptor->vertex_source_length,
        GL_VERTEX_SHADER);
    GLuint f_shader = create_gl_shader(
        descriptor->fragment_source_ptr,
        descriptor->fragment_source_length,
        GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, v_shader);
    glAttachShader(program, f_shader);
    glLinkProgram(program);

    uint32_t link_status = GL_TRUE;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE) {
        size_t log_length = { 0 };
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        char* log_ptr = calloc(log_length + 1, sizeof(char));

        glGetProgramInfoLog(program, log_length, &log_length, log_ptr);
        printf("Failed to link program: %s\n", log_ptr);



        GLint error;
        while (error = glGetError() != GLEW_OK) {
            puts(glewGetErrorString(error));
        }

        free(log_ptr);

        exit(-1);
    }

    glDetachShader(program, v_shader);
    glDetachShader(program, f_shader);

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    render_pipeline_t* pipeline = calloc(1, sizeof(render_pipeline_t));
    if (!pipeline) {
        puts("Failed to create pipeline");
        exit(-1);
    }

    pipeline->_program = program;

    return pipeline;
}

void render_pipeline_destroy(render_pipeline_t* pipeline)
{
    glDeleteProgram(pipeline->_program);

    free(pipeline);
}

void renderer_set_render_pipeline(renderer_t* renderer, render_pipeline_t* pipeline)
{
    glUseProgram(pipeline->_program);
}
