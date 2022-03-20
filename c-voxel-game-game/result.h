#pragma once

typedef struct Result {
    int is_error;
    union {
        char* error;
        void* value;
    };
} Result;

Result result_make_error(const char* error);
Result result_make_ok(void* value_ptr);

void* result_unwrap_internal(Result* result, const char* file, int line);

#define result_unwrap(result)\
result_unwrap_internal(result, __FILE__, __LINE__)