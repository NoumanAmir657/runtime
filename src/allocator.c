#include "allocator.h"

runtime_status_t allocator_libc_ctl(void* self, allocator_command_t command,
                                    const void* params, void** inout_ptr) {
  if (inout_ptr == NULL) {
    return RUNTIME_STATUS_INVALID_ARGUMENT;
  }

  (void)self;  // Unused

  switch (command) {
    case ALLOCATOR_COMMAND_MALLOC: {
      if (params == NULL) return RUNTIME_STATUS_INVALID_ARGUMENT;

      const allocator_alloc_params_t* alloc_params =
          (const allocator_alloc_params_t*)params;

      if (alloc_params->number_of_bytes == 0) {
        *inout_ptr = NULL;
        return RUNTIME_STATUS_OK;
      }

      void* new_ptr = malloc(alloc_params->number_of_bytes);
      if (new_ptr == NULL) {
        return RUNTIME_STATUS_OUT_OF_MEMORY;
      }

      *inout_ptr = new_ptr;
      return RUNTIME_STATUS_OK;
    }

    case ALLOCATOR_COMMAND_CALLOC: {
      if (params == NULL) return RUNTIME_STATUS_INVALID_ARGUMENT;

      const allocator_alloc_params_t* alloc_params =
          (const allocator_alloc_params_t*)params;

      if (alloc_params->number_of_bytes == 0) {
        *inout_ptr = NULL;
        return RUNTIME_STATUS_OK;
      }

      void* new_ptr = calloc(1, alloc_params->number_of_bytes);
      if (new_ptr == NULL) {
        return RUNTIME_STATUS_OUT_OF_MEMORY;
      }

      *inout_ptr = new_ptr;
      return RUNTIME_STATUS_OK;
    }

    case ALLOCATOR_COMMAND_REALLOC: {
      if (params == NULL) return RUNTIME_STATUS_INVALID_ARGUMENT;

      const allocator_alloc_params_t* alloc_params =
          (const allocator_alloc_params_t*)params;

      void* old_ptr = *inout_ptr;
      void* new_ptr = realloc(old_ptr, alloc_params->number_of_bytes);

      if (alloc_params->number_of_bytes > 0 && new_ptr == NULL) {
        return RUNTIME_STATUS_OUT_OF_MEMORY;
      }

      *inout_ptr = new_ptr;
      return RUNTIME_STATUS_OK;
    }

    case ALLOCATOR_COMMAND_FREE: {
      if (*inout_ptr != NULL) {
        free(*inout_ptr);
        *inout_ptr = NULL;
      }
      return RUNTIME_STATUS_OK;
    }

    default:
      return RUNTIME_STATUS_UNIMPLEMENTED;
  }
}
