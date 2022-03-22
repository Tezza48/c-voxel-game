#pragma once
#include <stdint.h>

typedef struct result {
    int is_error;
    size_t data_size;
    void* data_ptr;
} result;

result result_ok(const void* value_ptr, size_t value_size);

#define result_err(error) result_err_impl(error, __FILE__, __LINE__)
result result_err_impl(char* error, const char* filename, uint32_t line);

#define result_unwrap(result, out_value) result_unwrap_impl(result, __FILE__, __LINE__, out_value)
void result_unwrap_impl(result result, const char* filename, uint32_t line, void* out_value);
