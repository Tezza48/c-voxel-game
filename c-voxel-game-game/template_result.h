#pragma once


#define Result(x) Result##x



//       \
// typedef struct  {  \
//     int is_error;           \
//                             \
//     union {                 \
//         const char* error;  \
//         x value;            \
//     };                      \
// } Result##x;                \
// Result##x                   \