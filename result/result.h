#pragma once

#define RESULT_STRUCT_NAME(TYPE) result_##TYPE

#define DEFINE_RESULT_STRUCT(TYPE)\
typedef struct RESULT_STRUCT_NAME(TYPE) {\
    int is_error;               \
    union {                     \
        TYPE value;                \
        char* error;            \
    };                          \
} RESULT_STRUCT_NAME(TYPE);       \

#define DEFINE_RESULT_OK(TYPE)\
RESULT_STRUCT_NAME(TYPE) RESULT_STRUCT_NAME(TYPE)##_ok(TYPE value) {\
    return (RESULT_STRUCT_NAME(TYPE)) {.is_error = 0, .value = value};\
}\

#define DEFINE_RESULT_ERR(TYPE)\
RESULT_STRUCT_NAME(TYPE) RESULT_STRUCT_NAME(TYPE)##_err(char* error) {\
    return (RESULT_STRUCT_NAME(TYPE)) {.is_error = 1, .error = error};\
}\

#define DEFINE_RESULT_UNWRAP(TYPE)\
TYPE RESULT_STRUCT_NAME(TYPE)##_unwrap(RESULT_STRUCT_NAME(TYPE) result) {\
    if (result.is_error) {puts(result.error); exit(-1);}\
    return result.value;\
}\

#define DEFINE_RESULT(TYPE)\
DEFINE_RESULT_STRUCT(TYPE)\
DEFINE_RESULT_OK(TYPE)\
DEFINE_RESULT_ERR(TYPE)\
DEFINE_RESULT_UNWRAP(TYPE)\


#define RESULT_STRUCT_NAME_PTR(TYPE) result_##TYPE##_ptr

#define DEFINE_RESULT_STRUCT_PTR(TYPE)\
typedef struct RESULT_STRUCT_NAME_PTR(TYPE) {\
    int is_error;                       \
    union {                             \
        TYPE* value;                    \
        char* error;                    \
    };                                  \
} RESULT_STRUCT_NAME_PTR(TYPE);       \

#define DEFINE_RESULT_OK_PTR(TYPE)\
RESULT_STRUCT_NAME_PTR(TYPE) RESULT_STRUCT_NAME_PTR(TYPE)##_ok(TYPE* value) {\
    return (RESULT_STRUCT_NAME_PTR(TYPE)) {.is_error = 0, .value = value};\
}\

#define DEFINE_RESULT_ERR_PTR(TYPE)\
RESULT_STRUCT_NAME_PTR(TYPE) RESULT_STRUCT_NAME_PTR(TYPE)##_err(char* error) {\
    return (RESULT_STRUCT_NAME_PTR(TYPE)) {.is_error = 1, .error = error};\
}\

#define DEFINE_RESULT_UNWRAP_PTR(TYPE)\
TYPE* RESULT_STRUCT_NAME_PTR(TYPE)##_unwrap(RESULT_STRUCT_NAME_PTR(TYPE) result) {\
    if (result.is_error) {puts(result.error); exit(-1);}\
    return result.value;\
}\

#define DEFINE_RESULT_PTR(TYPE)\
DEFINE_RESULT_STRUCT_PTR(TYPE)\
DEFINE_RESULT_OK_PTR(TYPE)\
DEFINE_RESULT_ERR_PTR(TYPE)\
DEFINE_RESULT_UNWRAP_PTR(TYPE)\

//#define Result(x) Result ## x
//
//#define ResultStruct(x)         \
//struct Result(x) {              \
//    int is_error;               \
//    union {                     \
//        x value;                \
//        char* error;            \
//    };                          \
//};                              \
//
//#define ResultOk(x, name, v)    \
//ResultStruct(x) name = {        \
//    .is_error = 0,              \
//    .value = v                  \
//};                              \
//
//#define ResultStructPtr(x)      \
//struct Result(x) {              \
//    int is_error;               \
//    union {                     \
//        x* value;               \
//        char* error;            \
//    };                          \
//}                               \
//
//#define ResultOkPtr(x, name, v) \
//ResultStructPtr(x) name = {     \
//    .is_error = 0,              \
//    .value = v                  \
//};                              \
//
//#define ResultErrPtr(x, name, error_val)\
//ResultStructPtr(x) name = {\
//    .is_error = 1,         \
//    .error = error_val,        \
//};                          \
//
//#define ResultUnwrap(result, out_ptr)    \
//void** out = &out_ptr;\
//if (result.is_error) {\
//    puts("x was an error!");\
//}\
//*out = result.value;\
