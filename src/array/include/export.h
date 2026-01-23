#ifndef EXPORT_H
#define EXPORT_H

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#ifndef ARRAY_STATIC_DEFINE
#  include <array/export_shared.h>
#else
#  include <array/export_static.h>
#endif // ifndef ARRAY_STATIC_DEFINE

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // ifndef EXPORT_H
