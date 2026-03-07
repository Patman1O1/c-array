#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#define array_init(type, array, array_size, ...)                             \
    array.size = array_size;                                                 \
    array.values_p = (void*)calloc(array.size, sizeof(type));                \
    if (array.values_p == NULL) {                                            \
        exit(errno);                                                         \
    }                                                                        \
                                                                             \
    if (array.size > 0) {                                                    \
        type __values[] = {__VA_ARGS__};                                     \
        const size_t __values_size = sizeof(__values) / sizeof(__values[0]); \
        if (__values_size <= array.size && __values_size > 0) {              \
            memcpy(array.values_p, __values, sizeof(type) * __values_size);  \
        } else {                                                             \
            free(array.values_p);                                            \
            errno = E2BIG;                                                   \
            array.values_p = NULL;                                           \
        }                                                                    \
    } else {                                                                 \
        array.values_p = NULL;                                               \
    }                                                                        \

#define array_at(type, array, index) \
    (assert(array.values_p != NULL), \
     assert(index < array.size),     \
    ((type*)array.values_p)[index])  \

#define array_front(type, array)     \
    (assert(array.values_p != NULL), \
     assert(array.size > 0),         \
    ((type*)array.values_p)[0])      \

#define array_back(type, array)              \
    (assert(array.values_p != NULL),         \
     assert(array.size > 0),                 \
    ((type*)array.values_p)[array.size - 1]) \

#define array_fill(type, array, value)              \
    if (array.values_p != NULL && array.size > 0) { \
        for (size_t i = 0; i < array.size; i++) {   \
            array_at(type, array, i) = value;       \
        }                                           \
    } else if (array.values_p == NULL) {            \
        errno = EFAULT;                             \
    } else if (array.size == 0) {                   \
        errno = EINVAL;                             \
    }                                               \

struct array {
    void* values_p;
    size_t size;
};

extern int array_cmp(const struct array* lhs_p, const struct array* rhs_p);

extern bool array_empty(const struct array* array_p);

extern int array_swap(struct array* lhs_p, struct array* rhs_p);

extern int array_cpy(const struct array* src_p, const struct array* dst_p);

extern int array_mv(struct array** src_pp, struct array** dst_pp);

extern int array_free(struct array* array_p);


#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef ARRAY_H