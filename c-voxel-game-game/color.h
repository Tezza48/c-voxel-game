#pragma once

typedef struct color_t {
	float value[4];
} color_t;

inline color_t color_create_rgba(float r, float g, float b, float a) {
	return (color_t) {
		.value = { r, g, b, a }
	};
}