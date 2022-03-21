#include <stdio.h>
#include <stdlib.h>
#include "assets.h"

ASSETS_RESULT assets_load_gl_shader(const char* path, GLenum type, GLuint* out_shader) {
    GLint shader;

    {
        FILE* shader_file_ptr;
        errno_t error = fopen_s(&shader_file_ptr, path, "r");
        if (error) {
            if (shader_file_ptr) fclose(shader_file_ptr);

            return ASSETS_RESULT_ERROR_FILE_OPEN;
        }

        // allocate a buffer for the file contents
        fseek(shader_file_ptr, 0, SEEK_END);
        long shader_source_length = ftell(shader_file_ptr);
        rewind(shader_file_ptr);

        char * shader_source_ptr = calloc(shader_source_length + 1, sizeof(char));
        size_t fread_result = fread(shader_source_ptr, sizeof(char), shader_source_length, shader_file_ptr);
        // TODO WT: Check for errors when reading the file.

        if (fclose(shader_file_ptr) != 0) {
            return ASSETS_RESULT_ERROR_FILE_CLOSE;
        }

        // File successfully read into buffer, now we can create the shader.
        shader = glCreateShader(type);

        glShaderSource(shader, 1, &shader_source_ptr, &shader_source_length);
        free(shader_source_ptr);
    }

    glCompileShader(shader);
    GLuint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        GLint error_buffer_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &error_buffer_length);
        char* error_buffer_ptr = calloc(1, error_buffer_length);

        glGetShaderInfoLog(shader, error_buffer_length, 0, error_buffer_ptr);

        printf("ERROR: error compiling shader | %s\n", path);
        puts(error_buffer_ptr);

        free(error_buffer_ptr);
        glDeleteShader(shader);

        return ASSETS_RESULT_ERROR_COMPILATION;
    }

    *out_shader = shader;

    return ASSETS_RESULT_OK;
}