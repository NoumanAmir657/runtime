#ifndef TEST_UTILS_H_
#define TEST_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include "status.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

#define TEST_FAIL(msg) do { \
    fprintf(stderr, COLOR_RED "[FAIL] %s:%d: %s" COLOR_RESET "\n", __FILE__, __LINE__, msg); \
    exit(1); \
} while(0)

#define ASSERT_TRUE(cond) do { \
    if (!(cond)) TEST_FAIL("Condition " #cond " failed"); \
} while(0)

#define ASSERT_NOT_NULL(ptr) do { \
    if ((ptr) == NULL) TEST_FAIL("Pointer " #ptr " is NULL"); \
} while(0)

#define ASSERT_NULL(ptr) do { \
    if ((ptr) != NULL) TEST_FAIL("Pointer " #ptr " is NOT NULL"); \
} while(0)

#define ASSERT_OK(status_expr) do { \
    runtime_status_t _status = (status_expr); \
    if (!RUNTIME_STATUS_IS_OK(_status)) { \
        fprintf(stderr, COLOR_RED "[FAIL] %s:%d: Operation failed with error code %d" COLOR_RESET "\n", __FILE__, __LINE__, _status); \
        exit(1); \
    } \
} while(0)

#define ASSERT_ERROR(status_expr, expected_err) do { \
    runtime_status_t _status = (status_expr); \
    if (_status != (expected_err)) { \
        fprintf(stderr, COLOR_RED "[FAIL] %s:%d: Expected error %d but got %d" COLOR_RESET "\n", __FILE__, __LINE__, expected_err, _status); \
        exit(1); \
    } \
} while(0)

#define RUN_TEST(func) do { \
    printf("[RUN ] %s...\n", #func); \
    func(); \
    printf(COLOR_GREEN "[PASS] %s" COLOR_RESET "\n", #func); \
} while(0)

#endif // TEST_UTILS_H_
