#include "util/string.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STRING_MAX 5000000

String nc_string_make(const char * c_string) {
    String retval;
    nc_string_init(&retval, c_string);
    return retval;
}

void nc_string_init(String *string, const char *c_string) {
    string->length = strnlen(c_string, STRING_MAX);
    string->content = malloc(string->length + 1);
    strncpy((void*)string->content, c_string, string->length + 1);
}

void nc_string_deinit(String *string) {
    free((void*)string->content);
}

String nc_string_concat(const String *first, const String *second) {
    String retval;
    retval.length = first->length + second->length;
    retval.content = malloc(retval.length + 1);
    strncpy((void*)retval.content, first->content, first->length);
    strncpy((void*)retval.content + first->length, second->content, 
        second->length + 1);
    return retval;
}

String nc_string_to_lower(const String *str) {
    char * content = malloc(str->length + 1);
    for (size_t i = 0; i < str->length; i++) {
        content[i] = (char)tolower(str->content[i]);
    }
    String retval = {
        .content = content,
        .length = str->length
    };
    return retval;
}

String nc_string_to_upper(const String *str) {
    char * content = malloc(str->length + 1);
    for (size_t i = 0; i < str->length; i++) {
        content[i] = (char)toupper(str->content[i]);
    }
    String retval = {
        .content = content,
        .length = str->length
    };
    return retval;
}

String nc_string_to_title(const String *str) {
    char * content = malloc(str->length + 1);
    int upper = 1;

    for (size_t i = 0; i < str->length; i++) {
        if (upper == 1) {
            content[i] = (char)toupper(str->content[i]);
            upper = 0;
        } else {
            content[i] = (char)tolower(str->content[i]);
            if (isspace(content[i])) {
                upper = 1;
            }
        }
    }
    String retval = {
        .content = content,
        .length = str->length
    };
    return retval;
}