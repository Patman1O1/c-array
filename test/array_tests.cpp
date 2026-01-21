#include <array>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array/array.h>

namespace array_testing {

    /* ----------------------------------------------------array_init------------------------------------------------ */
    TEST(array_init_suite, zero_size) {
        struct ::array array = {};

        array_init(int, array, 0);

        EXPECT_EQ(array.values, nullptr);
        EXPECT_EQ(array.size, 0);

        EXPECT_EQ(::array_free(&array), EXIT_SUCCESS);
    }

    TEST(array_init_suite, num_values_greater_than_array_size) {
        struct ::array array = {};

        array_init(int, array, 1, 1, 2, 3);

        EXPECT_EQ(errno, E2BIG);
        EXPECT_EQ(array.values, nullptr);
        EXPECT_EQ(array.size, 1);

        EXPECT_EQ(::array_free(&array), EXIT_SUCCESS);
    }

    TEST(array_init_suite, num_values_equals_array_size) {
        struct ::array array = {};

        array_init(int, array, 3, 1, 2, 3);

        EXPECT_NE(array.values, nullptr);
        EXPECT_EQ(array.size, 3);

        for (std::size_t i = 0; i < array.size; i++) {
            constexpr std::array matcher = {1, 2, 3};
            EXPECT_EQ(array_at(int, array, i), matcher[i]);
        }

        EXPECT_EQ(::array_free(&array), EXIT_SUCCESS);
    }

    TEST(array_init_suite, num_values_less_than_array_size) {
        struct ::array array = {};

        array_init(int, array, 3, 1);

        for (std::size_t i = 0; i < array.size; i++) {
            constexpr std::array matcher = {1};
            EXPECT_EQ(array_at(int, array, i), matcher[i]);
        }

        EXPECT_EQ(::array_free(&array), EXIT_SUCCESS);
    }

} // namespace array_testing
