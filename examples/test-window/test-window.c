#include "core/app.h"
#include "util/log.h"
#include "util/string.h"
#include <nicandra.h>

static void start() {
    nc_log_info("Starting!");
}

static void end() {
    nc_log_info("Ending!");
}

int main() {
    AppInfo info = {
        .app_name = nc_string_make("Test Window"),
        .app_version = {
            .major = 0,
            .minor = 1,
            .patch = 0,
        }
    };
    nc_app_run(info, start, end);
}
