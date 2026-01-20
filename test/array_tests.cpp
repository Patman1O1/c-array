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
    }


} // namespace array_testing
