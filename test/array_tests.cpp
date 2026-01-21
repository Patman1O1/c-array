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

    /* -----------------------------------------------------array_at------------------------------------------------- */
    TEST(array_at_suite, array_at_test) {
        struct ::array array = {};
        array_init(int, array, 3, 1, 2, 3);

        for (std::size_t i = 0; i < array.size; i++) {
            constexpr std::array matcher = {1, 2, 3};
            EXPECT_EQ(array_at(int, array, i), matcher[i]);
        }

        EXPECT_EQ(array_free(&array), EXIT_SUCCESS);
    }

    /* ----------------------------------------------------array_front----------------------------------------------- */
    TEST(array_front_suite, single_value_array) {
        struct ::array array = {};
        array_init(int, array, 1, 1);

        EXPECT_EQ(array_front(int, array), 1);

        EXPECT_EQ(array_free(&array), EXIT_SUCCESS);
    }

    TEST(array_front_suite, multi_value_array) {
        struct ::array array = {};
        array_init(int, array, 3, 3, 2, 1);

        EXPECT_EQ(array_front(int, array), 3);

        EXPECT_EQ(array_free(&array), EXIT_SUCCESS);
    }

    /* ----------------------------------------------------array_back------------------------------------------------ */
    TEST(array_back_suite, single_value_array) {
        struct ::array array = {};
        array_init(int, array, 1, 1);

        EXPECT_EQ(array_back(int, array), 1);

        EXPECT_EQ(array_free(&array), EXIT_SUCCESS);
    }

    TEST(array_back_suite, multi_value_array) {
        struct ::array array = {};
        array_init(int, array, 3, 1, 2, 3);

        EXPECT_EQ(array_back(int, array), 3);

        EXPECT_EQ(array_free(&array), EXIT_SUCCESS);
    }

    /* ----------------------------------------------------array_fill------------------------------------------------ */
    TEST(array_fill_suite, empty_array) {
        struct ::array array = {};

        array_init(int, array, 0);

        array_fill(int, array, 101);

        EXPECT_EQ(errno, EFAULT);

        EXPECT_EQ(::array_free(&array), EXIT_SUCCESS);
    }

    TEST(array_fill_suite, single_value_array) {
        struct ::array array = {};

        array_init(int, array, 1, 1);

        EXPECT_EQ(array_at(int, array, 0), 1);

        array_fill(int, array, 101);

        EXPECT_EQ(array_at(int, array, 0), 101);

        EXPECT_EQ(::array_free(&array), EXIT_SUCCESS);
    }

    TEST(array_fill_suite, multi_value_array) {
        struct ::array array = {};

        array_init(int, array, 10);

        array_fill(int, array, 101);

        for (std::size_t i = 0; i < array.size; i++) {
            EXPECT_EQ(array_at(int, array, i), 101);
        }

        EXPECT_EQ(::array_free(&array), EXIT_SUCCESS);
    }

    /* ----------------------------------------------------array_empty----------------------------------------------- */
    TEST(array_empty_suite, true_case) {
        struct ::array array = {};
        array_init(int, array, 0);

        EXPECT_TRUE(::array_empty(&array));

        EXPECT_EQ(::array_free(&array), EXIT_SUCCESS);
    }

    TEST(array_empty_suite, false_case) {
        struct ::array array = {};
        array_init(int, array, 3, 1, 2, 3);

        EXPECT_FALSE(::array_empty(&array));

        EXPECT_EQ(::array_free(&array), EXIT_SUCCESS);
    }

} // namespace array_testing
