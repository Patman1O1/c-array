#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

struct array {
    void** values;
    size_t size;
};

#define array_init(type, array, array_size, ...)                       \
    array.size = array_size;                                           \
    array.values = (void**)calloc(array.size, sizeof(void*));          \
    if (array.values == NULL) {                                        \
        exit(errno);                                                   \
    }                                                                  \
                                                                       \
    if (array.size > 0) {                                              \
        type values[] = {__VA_ARGS__};                                 \
        const size_t values_size = sizeof(values) / sizeof(values[0]); \
        if (values_size <= array.size) {                               \
            for (size_t i = 0; i < values_size; i++) {                 \
                type value = (type[]){__VA_ARGS__}[i];                 \
                array.values[i] = &value;                              \
            }                                                          \
        } else {                                                       \
            free(array.values);                                        \
            errno = E2BIG;                                             \
            array.values = NULL;                                       \
        }                                                              \
    } else {                                                           \
        array.values = NULL;                                           \
    }                                                                  \

#define array_at(type, array, index) (*(type*)array.values[index])

#define array_front(type, array) (*(type*)array.values[0])

#define array_back(type, array) (*(type*)array.values[array.size - 1])

extern bool array_empty(struct array array);

extern int array_fill(const struct array* array_p, void* value);

extern void array_swap(struct array* lhs_p, struct array* rhs_p);

extern int array_cpy(const struct array* src_p, const struct array* dst_p);

extern int array_cmp(struct array lhs, struct array rhs);

extern int array_free(struct array* array_p);

#ifdef __cplusplus
}
#endif // ifdef __cplusplus

#endif // ifndef ARRAY_H
