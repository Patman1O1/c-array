#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array/array.h>

namespace array_testing {

    /* ----------------------------------------------------array_init------------------------------------------------ */
    TEST(array_init_suite, zero_size) {
        struct array array = {};

        array_init(int, array, 0);

        EXPECT_EQ(array.values, nullptr);
        EXPECT_EQ(array.size, 0);

        array_free(&array);
    }

    TEST(array_init_suite, num_values_greater_array_size) {
        struct array array = {};

        array_init(int, array, 1, 1, 2, 3);

        EXPECT_EQ(errno, E2BIG);
        EXPECT_EQ(array.values, nullptr);
        EXPECT_EQ(array.size, 1);

        array_free(&array);
    }

} // namespace array_testing
