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

#define array_init(type, array, array_size, ...)                                                                          \
    array.size = array_size;                                                                                              \
    array.values = (void**)calloc(array.size, sizeof(void*));                                                             \
    if (array.values == NULL) {                                                                                           \
        perror("calloc");                                                                                                 \
        exit(EXIT_FAILURE);                                                                                               \
    }                                                                                                                     \
                                                                                                                          \
    memcpy(array.values, (type[]){__VA_ARGS__}, array.size);                                                              \
                                                                                                                          \
    do {                                                                                                                  \
        for (size_t i = 0; i < sizeof((type[]){__VA_ARGS__}) / sizeof((type[]){__VA_ARGS__}[0]) && i <= array.size; i++) {\
            type temp = (type[]){__VA_ARGS__}[i];                                                                         \
            array.values[i] = &temp;                                                                                      \
        }                                                                                                                 \
    } while (false);                                                                                                      \

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
