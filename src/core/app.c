#include "core/app.h"
#include "util/log.h"
#include "util/sync/thread.h"
#include <stdlib.h>
#include <signal.h>

App app;

#define NICANDRA_APP_IS_RUNNING (1 << 0)

static void nc_app_initialize();
static void nc_app_breakdown();
static void nc_app_handle_signal(int signal_code);

void nc_app_run(AppInfo app_info, VoidFunc on_start, VoidFunc on_end) {
    app.info = app_info;
    app.on_start = on_start;
    app.on_end = on_end;    
    app.flags = NICANDRA_APP_IS_RUNNING;

    signal(SIGINT, nc_app_handle_signal);

    nc_app_initialize();

    while (nc_app_is_running()) {
        nc_sleep_milliseconds(17);
    }

    nc_app_breakdown();
}

Bool nc_app_is_running() {
    return (app.flags & NICANDRA_APP_IS_RUNNING) > 0;
}

void nc_app_stop() {
    app.flags &= ~NICANDRA_APP_IS_RUNNING;
}

void nc_app_panic(const char* message) {
    nc_log_error("FATAL: %s\n", message);
    abort();
}

static void nc_app_initialize() {
    if (app.on_start != NULL) {
        app.on_start();
    }
}

static void nc_app_breakdown() {
    if (app.on_end != NULL) {
        app.on_end();
    }
}

static void nc_app_handle_signal(int signal_code) {
    nc_app_stop();
}