#ifndef NICANDRA_THREAD_H
#define NICANDRA_THREAD_H

#include "pthread.h"
#include "util/types.h"

typedef struct Thread Thread;
struct Thread {

};

Thread nc_thread_spawn();

void nc_sleep_milliseconds(u32 milliseconds);

#endif