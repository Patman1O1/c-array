#ifndef EXPORT_H
#define EXPORT_H

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#ifndef C_ARRAY_STATIC_DEFINE
#  include <c_array/export_shared.h>
#else
#  include <c_array/export_static.h>
#endif // #ifndef C_ARRAY_STATIC_DEFINE

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef EXPORT_H

