#include "nicandra.h"
#include "util/log.h"
#include "util/string.h"

void nc_app_run() {
    String a, b, c, low, up, title;
    nc_string_init(&a, "Hello this is a string! ");
    nc_string_init(&b, "And this is some added content!\n");
    c = nc_string_concat(&a, &b);
    low = nc_string_to_lower(&c);
    up = nc_string_to_upper(&c);
    title = nc_string_to_title(&c);

    log_info("Original: %s\n", c.content);
    log_info("Lower:    %s\n", low.content);
    log_info("Upper:    %s\n", up.content);
    log_info("Title:    %s\n", title.content);

    nc_string_deinit(&a);
    nc_string_deinit(&b);
    nc_string_deinit(&c);
    nc_string_deinit(&low);
    nc_string_deinit(&up);
    nc_string_deinit(&title);

    log_verbose("This is verbose!\n");
    log_info("This is info!\n");
    log_warn("This is a warning\n");
    log_error("This is an error!\n");
}
