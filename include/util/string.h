#ifndef NICANDRA_STRING_H
#define NICANDRA_STRING_H

#include <stddef.h>

/**
* An immutable, heap allocated container of characters to make up text.
*/
typedef struct String String;
struct String {
    const char * content;
    size_t length;
};

String nc_string_make(const char * c_string);

void nc_string_init(String * string, const char * c_string);

void nc_string_deinit(String * string);

String nc_string_concat(const String * first, const String * second);

String nc_string_to_lower(const String * str);

String nc_string_to_upper(const String * str);

String nc_string_to_title(const String * str);

#endif