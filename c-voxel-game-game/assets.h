#pragma once
#include <GL/glew.h>

typedef enum {
	ASSETS_RESULT_OK,
	ASSETS_RESULT_ERROR_FILE_OPEN,
	ASSETS_RESULT_ERROR_FILE_CLOSE,
	ASSETS_RESULT_ERROR_COMPILATION,
	ASSETS_RESULT_ERROR_UNDEFINED,
} ASSETS_RESULT;


ASSETS_RESULT assets_load_gl_shader(const char* path, GLenum type, GLuint* out_shader);