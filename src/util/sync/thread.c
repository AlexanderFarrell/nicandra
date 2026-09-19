#include "util/sync/thread.h"
#include "time.h"

void nc_sleep_milliseconds(uint32_t milliseconds) {
    struct timespec res;
    struct timespec req = {
        .tv_sec = milliseconds / 1000,
        .tv_nsec = (milliseconds % 1000) * 1000000L
    };

    nanosleep(&req, &res);    
}