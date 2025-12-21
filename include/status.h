#ifndef STATUS_H_
#define STATUS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef int runtime_status_t;

typedef enum runtime_status_code_e {
    RUNTIME_STATUS_OK = 0,
    RUNTIME_STATUS_INVALID_ARGUMENT = -1,
    RUNTIME_STATUS_OUT_OF_MEMORY = -2,
    RUNTIME_STATUS_UNIMPLEMENTED = -3,
} runtime_status_code_t;

#define RUNTIME_STATUS_IS_OK(x) ((x) == RUNTIME_STATUS_OK)

#ifdef __cplusplus
}
#endif

#endif  // STATUS_H_
