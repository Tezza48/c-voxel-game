#pragma once

#include "app.h"
#include "color.h"

// renderer_t
typedef struct renderer_t {
	uint8_t REMOVEME;
} renderer_t;

renderer_t* renderer_create(app_t* app);

void renderer_present(renderer_t* renderer, app_t* app);

/// <summary>
/// Clear the current render target.
/// </summary>
/// <param name="renderer"></param>
void renderer_clear(renderer_t* renderer);

void renderer_destroy(renderer_t* renderer);
void renderer_set_clear_color(color_t color);

void renderer_draw_vertices(renderer_t* renderer, uint32_t start_vertex, uint32_t vertex_count, uint32_t instance_count);

// render_pipeline_t
typedef struct render_pipeline_desc_t {
	char* vertex_source_ptr;
	size_t vertex_source_length;

	char* fragment_source_ptr;
	size_t fragment_source_length;
}render_pipeline_desc_t;

typedef struct render_pipeline_t {
	GLuint _program;
}render_pipeline_t;

render_pipeline_t* render_pipeline_create(renderer_t* renderer, render_pipeline_desc_t* descriptor);
void render_pipeline_destroy(render_pipeline_t* pipeline);

void renderer_set_render_pipeline(renderer_t* renderer, render_pipeline_t* pipeline);