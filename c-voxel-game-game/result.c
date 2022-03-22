#include "result.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

result result_ok(const void* value_ptr, size_t value_size) {
    // It's possible to provide (0, 0) if you con't actually want a value to be passed down.
    if (value_ptr) {
        result out = {
            .is_error = 0,
            .data_size = value_size,
            .data_ptr = malloc(value_size),
        };
        memcpy_s(out.data_ptr, out.data_size, value_ptr, out.data_size);

        return out;
    }

    result out = {
        .is_error = 0,
        .data_size = 0,
        .data_ptr = 0,
    };

    return out;
}

result result_err_impl(char* error, const char* filename, uint32_t line) {
    // TODO WT: Prepend the filename and line to the error message so we know where it was fired.
    return (result) {
        .is_error = 1,
            .data_size = sizeof(char*),
            .data_ptr = error,
    };
}

void result_unwrap_impl(result result, const char* filename, uint32_t line, void* out_value) {
    if (result.is_error) {
        printf("RESULT_UNWRAP PANIC: %s:%d %s\n", filename, line, (const char*)result.data_ptr);
        exit(-1);
    }


    if (out_value) {
        memcpy_s(out_value, result.data_size, result.data_ptr, result.data_size);
    }

    if(result.data_ptr) {
        free(result.data_ptr);
    }
}