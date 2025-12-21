#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include <stdlib.h>

#include "status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum allocator_command_e {
    ALLOCATOR_COMMAND_MALLOC = 0,
    ALLOCATOR_COMMAND_CALLOC = 1,
    ALLOCATOR_COMMAND_REALLOC = 2,
    ALLOCATOR_COMMAND_FREE = 3,
} allocator_command_t;

typedef struct allocator_alloc_params_t {
    size_t number_of_bytes;
} allocator_alloc_params_t;

typedef runtime_status_t (*allocator_ctl_fn_t)(void* self, allocator_command_t command, const void* params, void** inout_ptr);

typedef struct allocator_t {
    void* self;
    allocator_ctl_fn_t ctl;
} allocator_t;

runtime_status_t allocator_libc_ctl(void* self, allocator_command_t command, const void* params, void** inout_ptr);

#ifndef ALLOCATOR_SYSTEM_CTL
    #define ALLOCATOR_SYSTEM_CTL allocator_libc_ctl
#else
    extern runtime_status_t ALLOCATOR_SYSTEM_CTL(void* self, allocator_command_t command, const void* params, void** inout_ptr);
#endif

static inline allocator_t allocator_system() {
    allocator_t allocator = {
        NULL,
        ALLOCATOR_SYSTEM_CTL,
    };
    return allocator;
}

#ifdef __cplusplus
}
#endif

#endif  // ALLOCATOR_H_
