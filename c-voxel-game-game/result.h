#pragma once
#include <stdint.h>

typedef struct result {
    int is_error;
    size_t data_size;
    void* data_ptr;
} result;

result result_ok(const void* value_ptr, size_t value_size);
result result_err(char* error);

#define result_unwrap(result, out_value) result_unwrap_impl(result, __FILE__, __LINE__, out_value)
void result_unwrap_impl(result result, const char* filename, uint32_t line, void* out_value);

#ifdef RESULT_IMPL
#include <stdlib.h>
#include <stdio.h>

result result_ok(const void* value_ptr, size_t value_size) {
    result out = {
        .is_error = 0,
        .data_size = value_size,
        .data_ptr = malloc(value_size)
    };

    memcpy(out.data_ptr, value_ptr, out.data_size);

    return out;
}

result result_err(char* error) {
    return (result){
        .is_error = 1,
        .data_size = sizeof(char*),
        .data_ptr = error,
    };
}
#define result_unwrap(result, out_value) result_unwrap_impl(result, __FILE__, __LINE__, out_value)
void result_unwrap_impl(result result, const char* filename, uint32_t line, void* out_value) {
    if (result.is_error) {
        printf("RESULT_UNWRAP PANIC: %s:%d %s\n", filename, line, (const char*)result.data_ptr);
        exit(-1);
    }

    memcpy(out_value, result.data_ptr, result.data_size);

    free(result.data_ptr);
}
#endif

