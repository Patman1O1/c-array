#include <errno.h>

#include "array/array.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

    bool array_empty(const struct array array) { return array.size == 0; }

    int array_fill(const struct array* array_p, void* value) {
        if (array_p == NULL || value == NULL) {
            errno = EFAULT;
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < array_p->size; i++) {
            array_p->values[i] = value;
        }

        return EXIT_SUCCESS;
    }

    void array_swap(struct array* lhs_p, struct array* rhs_p) {
        if (lhs_p == NULL || rhs_p == NULL || lhs_p == rhs_p) {
            return;
        }

        void** temp = lhs_p->values;
        lhs_p->values = rhs_p->values;
        rhs_p->values = temp;
    }

    int array_cpy(const struct array* src_p, const struct array* dst_p) {
        if (src_p == NULL || dst_p == NULL) {
            errno = EFAULT;
            return EXIT_FAILURE;
        }

        if (src_p->size != dst_p->size) {
            errno = EINVAL;
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < src_p->size; i++) {
            dst_p->values[i] = src_p->values[i];
        }

        return EXIT_SUCCESS;
    }

    int array_mv(struct array** src_pp, struct array** dst_pp) {
        // Make sure the address of the source pointer and the address of the destination pointer do NOT point to NULL
        if (src_pp == NULL || dst_pp == NULL) {
            errno = EFAULT;
            return errno;
        }

        // Free the array instance pointed to by the source pointer
        if (*dst_pp != NULL) {
            free(*dst_pp);

            // Return the error number returned by free() if it is not equal to EXIT_SUCCESS (i.e. 0)
            if (errno != EXIT_SUCCESS) {
                return errno;
            }
        }

        // Return the error number returned by free() if it is not equal to EXIT_SUCCESS (i.e. 0)
        if (errno != EXIT_SUCCESS) {
            return errno;
        }

        // Point the destination pointer to the array instance pointed to by the source pointer
        *dst_pp = *src_pp;

        // Point the source pointer to NULL
        *src_pp = NULL;

        return EXIT_SUCCESS;
    }

    int array_cmp(const struct array lhs, const struct array rhs) {
        if (lhs.values == rhs.values) {
            return 0;
        }

        for (size_t i = 0; i < lhs.size; i++) {
            if (lhs.values[i] < rhs.values[i]) {
                return -1;
            }

            if (lhs.values[i] > rhs.values[i]) {
                return 1;
            }
        }

        return 0;
    }

    int array_free(struct array* array_p) {
        if (array_p == NULL) {
            return EFAULT;
        }

        if (array_p->values == NULL) {
            return EXIT_SUCCESS;
        }

        free(array_p);
        return EXIT_SUCCESS;
    }

#ifdef __cplusplus
}
#endif // ifdef __cplusplus
