// result.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "result.h"

DEFINE_RESULT(int)
DEFINE_RESULT_PTR(char)

//DEFINE_RESULT_STRUCT(int)
//
//DEFINE_RESULT_OK(int)
//
//DEFINE_RESULT_UNWRAP(int)

int main()
{
    result_char_ptr string_result = result_char_ptr_ok("Hello, World!");
    result_char_ptr string_error = result_char_ptr_err("There was something wrong");
    char* ok_string = result_char_ptr_unwrap(string_result);
    char* should_error = result_char_ptr_unwrap(string_error);

    puts(ok_string);
    puts(should_error);


    ////struct ThingType {
    ////	char* name;
    ////} thing = { .name = "Will" };

    //////struct Resultint {
    //////	int is_error;
    //////	union {
    //////		int value;
    //////		char* error;
    //////	};
    //////} int_result = { .is_error = 0, .value = 5 };

    ////puts(thing.name);
    ////ResultOkPtr(char, string_result, "Hello World!");
    // ResultErrPtr(char, string_result, "String was eronious");
    // ResultOkPtr(char, other_string_result, "This string is fine");

    // char* value;
    ////ResultUnwrap(string_result, value);

    ////char** out = &value;
    ////if (string_result.is_error) {
    ////	puts("x was an error!");
    ////}
    ////*out = string_result.value;

    // puts(value);
}
