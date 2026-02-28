#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

struct array {
    void* values;
    size_t size;
};

#define array_init(type, array, array_size, ...)                       \
    array.size = array_size;                                           \
    array.values = (void*)calloc(array.size, sizeof(type));            \
    if (array.values == NULL) {                                        \
        exit(errno);                                                   \
    }                                                                  \
                                                                       \
    if (array.size > 0) {                                              \
        type values[] = {__VA_ARGS__};                                 \
        const size_t values_size = sizeof(values) / sizeof(values[0]); \
        if (values_size <= array.size && values_size > 0) {            \
            memcpy(array.values, values, sizeof(type) * array.size);   \
        } else {                                                       \
            free(array.values);                                        \
            errno = E2BIG;                                             \
            array.values = NULL;                                       \
        }                                                              \
    } else {                                                           \
        array.values = NULL;                                           \
    }                                                                  \

#define array_at(type, array, index) (((type*)array.values)[index])

#define array_front(type, array) (((type*)array.values)[0])

#define array_back(type, array) (((type*)array.values)[array.size - 1])

#define array_fill(type, array, value)           \
    if (array.values != NULL && array.size > 0) {\
        for (size_t i = 0; i < array.size; i++) {\
            array_at(type, array, i) = value;    \
        }                                        \
    } else if (array.values == NULL) {           \
        errno = EFAULT;                          \
    } else if (array.size == 0) {                \
        errno = EINVAL;                          \
    }                                            \

extern bool array_empty(const struct array* array_p);

extern int array_swap(struct array* lhs_p, struct array* rhs_p);

extern int array_cpy(const struct array* src_p, const struct array* dst_p);

extern int array_mv(struct array** src_pp, struct array** dst_pp);

extern int array_free(struct array* array_p);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef ARRAY_H