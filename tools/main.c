#include <stdio.h>
#include "allocator.h"

int main() {
    printf("Allocator system initialized.\n");
    allocator_t allocator = allocator_system();
    allocator_alloc_params_t params = { .number_of_bytes = 128 };
    void* ptr = NULL;
    if (allocator.ctl(allocator.self, ALLOCATOR_COMMAND_MALLOC, &params, &ptr) != 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    printf("Allocated 128 bytes at %p\n", ptr);
    allocator.ctl(allocator.self, ALLOCATOR_COMMAND_FREE, NULL, &ptr);
    printf("Memory freed\n");
    return 0;
}
