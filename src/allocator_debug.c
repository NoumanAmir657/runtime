#include "allocator_debug.h"

#include <stdio.h>
#include <stdlib.h>

runtime_status_t allocator_debug_ctl(void* self, allocator_command_t command,
                                     const void* params, void** inout_ptr) {
  if (inout_ptr == NULL) {
    printf("[DEBUG] Error: inout_ptr is NULL\n");
    return RUNTIME_STATUS_INVALID_ARGUMENT;
  }

  (void)self;

  switch (command) {
    case ALLOCATOR_COMMAND_MALLOC: {
      if (params == NULL) return RUNTIME_STATUS_INVALID_ARGUMENT;
      const allocator_alloc_params_t* alloc_params =
          (const allocator_alloc_params_t*)params;

      printf("[DEBUG] Malloc request: %zu bytes\n",
             alloc_params->number_of_bytes);

      if (alloc_params->number_of_bytes == 0) {
        *inout_ptr = NULL;
        printf("[DEBUG]   -> Zero-byte alloc (Success: NULL)\n");
        return RUNTIME_STATUS_OK;
      }

      void* new_ptr = malloc(alloc_params->number_of_bytes);

      if (new_ptr) {
        printf("[DEBUG]   -> Success: %p\n", new_ptr);
        *inout_ptr = new_ptr;
        return RUNTIME_STATUS_OK;
      } else {
        printf("[DEBUG]   -> Failed (OOM)\n");
        return RUNTIME_STATUS_OUT_OF_MEMORY;
      }
    }

    case ALLOCATOR_COMMAND_CALLOC: {
      if (params == NULL) return RUNTIME_STATUS_INVALID_ARGUMENT;
      const allocator_alloc_params_t* alloc_params =
          (const allocator_alloc_params_t*)params;

      printf("[DEBUG] Calloc request: %zu bytes\n",
             alloc_params->number_of_bytes);

      if (alloc_params->number_of_bytes == 0) {
        *inout_ptr = NULL;
        printf("[DEBUG]   -> Zero-byte alloc (Success: NULL)\n");
        return RUNTIME_STATUS_OK;
      }

      void* new_ptr = calloc(1, alloc_params->number_of_bytes);

      if (new_ptr != NULL) {
        printf("[DEBUG]   -> Success: %p\n", new_ptr);
        *inout_ptr = new_ptr;
        return RUNTIME_STATUS_OK;
      } else {
        printf("[DEBUG]   -> Failed (OOM)\n");
        return RUNTIME_STATUS_OUT_OF_MEMORY;
      }
    }

    case ALLOCATOR_COMMAND_REALLOC: {
      if (params == NULL) return RUNTIME_STATUS_INVALID_ARGUMENT;
      const allocator_alloc_params_t* alloc_params =
          (const allocator_alloc_params_t*)params;

      printf("[DEBUG] Realloc request: %p -> %zu bytes\n", *inout_ptr,
             alloc_params->number_of_bytes);

      void* old_ptr = *inout_ptr;
      void* new_ptr = realloc(old_ptr, alloc_params->number_of_bytes);

      if (alloc_params->number_of_bytes > 0 && new_ptr == NULL) {
        printf("[DEBUG]   -> Failed (Original pointer preserved)\n");
        return RUNTIME_STATUS_OUT_OF_MEMORY;
      }

      printf("[DEBUG]   -> Success: %p\n", new_ptr);
      *inout_ptr = new_ptr;
      return RUNTIME_STATUS_OK;
    }

    case ALLOCATOR_COMMAND_FREE: {
      printf("[DEBUG] Free request: %p\n", *inout_ptr);
      if (*inout_ptr != NULL) {
        free(*inout_ptr);
        *inout_ptr = NULL;
      }
      return RUNTIME_STATUS_OK;
    }

    default:
      printf("[DEBUG] Unknown command: %d\n", command);
      return RUNTIME_STATUS_UNIMPLEMENTED;
  }
}
