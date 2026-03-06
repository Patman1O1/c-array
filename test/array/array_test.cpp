#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../include/array/array.h"

namespace array_tests {

    // ── Method Tests (array_init) ────────────────────────────────────────────────────────────────────────────────────
    TEST(array_init, empty_array) {
        struct ::array array;
        array_init(int, array, 0);

        EXPECT_EQ(array.size, 0);
        EXPECT_EQ(array.values_p, nullptr);
    }

    TEST(array_init, single_value_array) {
        struct ::array array;
        array_init(int, array, 1, 1);

        EXPECT_EQ(array.size, 1);
        EXPECT_NE(array.values_p, nullptr);

        EXPECT_EQ(1, array_at(int, array, 0));
    }

    TEST(array_init, multi_value_array) {
        struct ::array array;

        array_init(int, array, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(array.size, 5);
        EXPECT_NE(array.values_p, nullptr);

        EXPECT_EQ(1, array_at(int, array, 0));
        EXPECT_EQ(2, array_at(int, array, 1));
        EXPECT_EQ(3, array_at(int, array, 2));
        EXPECT_EQ(4, array_at(int, array, 3));
        EXPECT_EQ(5, array_at(int, array, 4));
    }

    // ── Method Tests (array_at) ──────────────────────────────────────────────────────────────────────────────────────
    TEST(array_at, single_value_array) {
        struct ::array array;
        array_init(int, array, 1, 1);

        EXPECT_EQ(1, array_at(int, array, 0));
    }

    TEST(array_at, multi_value_array) {
        struct ::array array;
        array_init(int, array, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(1, array_at(int, array, 0));
        EXPECT_EQ(2, array_at(int, array, 1));
        EXPECT_EQ(3, array_at(int, array, 2));
        EXPECT_EQ(4, array_at(int, array, 3));
    }

    // ── Method Tests (array_front) ───────────────────────────────────────────────────────────────────────────────────
    TEST(array_front, single_value_array) {
        struct ::array array;
        array_init(int, array, 1, 1);

        EXPECT_EQ(1, array_front(int, array));
    }

    TEST(array_front, multi_value_array) {
        struct ::array array;
        array_init(int, array, 5, 5, 4, 3, 2, 1);

        EXPECT_EQ(5, array_front(int, array));
    }

    // ── Method Tests (array_back) ────────────────────────────────────────────────────────────────────────────────────
    TEST(array_back, single_value_array) {
        struct ::array array;
        array_init(int, array, 1, 1);

        EXPECT_EQ(1, array_back(int, array));
    }

    TEST(array_back, multi_value_array) {
        struct ::array array;
        array_init(int, array, 5, 5, 4, 3, 2, 1);

        EXPECT_EQ(1, array_back(int, array));
    }

} // namespace array_tests
