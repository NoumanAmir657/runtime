#include "allocator.h"

#include <stdint.h>

#include "test_utils.h"

void test_malloc_free(void) {
  allocator_t allocator = allocator_system();

  allocator_alloc_params_t params = {.number_of_bytes = 256};
  void* ptr = NULL;

  ASSERT_OK(
      allocator.ctl(allocator.self, ALLOCATOR_COMMAND_MALLOC, &params, &ptr));
  ASSERT_NOT_NULL(ptr);

  ASSERT_OK(allocator.ctl(allocator.self, ALLOCATOR_COMMAND_FREE, NULL, &ptr));
  ASSERT_NULL(ptr);
}

void test_calloc(void) {
  allocator_t allocator = allocator_system();
  size_t size = 1024;
  allocator_alloc_params_t params = {.number_of_bytes = size};
  void* ptr = NULL;

  ASSERT_OK(
      allocator.ctl(allocator.self, ALLOCATOR_COMMAND_CALLOC, &params, &ptr));
  ASSERT_NOT_NULL(ptr);

  unsigned char* bytes = (unsigned char*)ptr;
  for (size_t i = 0; i < size; ++i) {
    if (bytes[i] != 0) {
      TEST_FAIL("Calloc memory was not zeroed");
    }
  }

  allocator.ctl(allocator.self, ALLOCATOR_COMMAND_FREE, NULL, &ptr);
}

void test_realloc(void) {
  allocator_t allocator = allocator_system();

  allocator_alloc_params_t params = {.number_of_bytes = 64};
  void* ptr = NULL;
  ASSERT_OK(
      allocator.ctl(allocator.self, ALLOCATOR_COMMAND_MALLOC, &params, &ptr));

  params.number_of_bytes = 128;
  ASSERT_OK(
      allocator.ctl(allocator.self, ALLOCATOR_COMMAND_REALLOC, &params, &ptr));
  ASSERT_NOT_NULL(ptr);

  ((char*)ptr)[127] = 'A';

  allocator.ctl(allocator.self, ALLOCATOR_COMMAND_FREE, NULL, &ptr);
}

void test_oom_behavior(void) {
  allocator_t allocator = allocator_system();
  allocator_alloc_params_t params = {.number_of_bytes = SIZE_MAX};
  void* ptr = NULL;

  ASSERT_ERROR(
      allocator.ctl(allocator.self, ALLOCATOR_COMMAND_MALLOC, &params, &ptr),
      RUNTIME_STATUS_OUT_OF_MEMORY);

  ASSERT_NULL(ptr);
}

int main(void) {
  printf("Running Allocator Tests...\n");

  RUN_TEST(test_malloc_free);
  RUN_TEST(test_calloc);
  RUN_TEST(test_realloc);
  RUN_TEST(test_oom_behavior);

  printf("\nAll tests passed.\n");
  return 0;
}
