#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

struct array {
    void** values;
    size_t size;
};

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef ARRAY_H

