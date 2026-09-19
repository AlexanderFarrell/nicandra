#ifndef NICANDRA_APP_H
#define NICANDRA_APP_H

#include "util/numbers.h"
#include "util/types.h"
#include "util/string.h"

typedef struct Version Version;
struct Version {
    u32 major;
    u32 minor;
    u32 patch;
};

typedef struct AppInfo AppInfo;
struct AppInfo {
    String app_name;
    Version app_version;
};

typedef struct App App;
struct App {
    AppInfo info;
    VoidFunc on_start;
    VoidFunc on_end;
    u8 flags;
};

void nc_app_run(AppInfo app_info, VoidFunc on_start, VoidFunc on_end);
Bool nc_app_is_running();
void nc_app_stop();
void nc_app_panic(const char* message);

#endif