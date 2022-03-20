#include "result.h"
#include <stdlib.h>
#include <stdio.h>

Result result_make_error(const char* error) {
    Result result = {
        .is_error = 1,
        .error = error,
    };

    return result;
}

Result result_make_ok(void* value_ptr) {
    Result result = {
        .is_error = 0,
        .value = value_ptr,
    };

    return result;
}

void* result_unwrap_internal(Result* result, const char* file, int line) {
    if (result->is_error) {
        printf("ERROR: result_unwrap | %s:%d | %s\n", file, line, result->error);

        exit(-1);
    }

    return result->value;
}