#pragma once
#include <stdint.h>

typedef struct Result {
    int is_error;
    union {
        const char* error;
        void* ptr;
        int32_t int32;
    };
} Result;

Result result_make_error(const char* error);
Result result_make_ok(void* value_ptr);
Result result_make_ok_int32(int32_t value);

void* result_unwrap_internal(Result* result, const char* file, int line);
int32_t result_unwrap_internal_int32(Result* result, const char* file, int line);

#define result_unwrap(result)\
result_unwrap_internal(result, __FILE__, __LINE__)

#define result_unwrap_int32(result)\
result_unwrap_internal_int32(result, __FILE__, __LINE__)