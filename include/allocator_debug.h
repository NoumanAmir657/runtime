#ifndef ALLOCATOR_DEBUG_H_
#define ALLOCATOR_DEBUG_H_

#include "allocator.h"

#ifdef __cplusplus
extern "C" {
#endif

// A custom allocator control function that logs operations to stdout
// before delegating to the system malloc/free.
runtime_status_t allocator_debug_ctl(void* self, allocator_command_t command, const void* params, void** inout_ptr);

#ifdef __cplusplus
}
#endif

#endif  // ALLOCATOR_DEBUG_H_
