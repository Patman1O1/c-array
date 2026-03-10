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

        array_free(&array);
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

    // ── Method Tests (array_cmp) ─────────────────────────────────────────────────────────────────────────────────────
    TEST(array_cmp, lhs_null) {
        struct ::array rhs;
        array_init(int, rhs, 0);

        EXPECT_EQ(EFAULT, array_cmp(nullptr, &rhs));
        EXPECT_EQ(EFAULT, errno);
    }

    TEST(array_cmp, rhs_null) {
        struct ::array lhs;
        array_init(int, lhs, 0);

        EXPECT_EQ(EFAULT, array_cmp(&lhs, nullptr));
        EXPECT_EQ(EFAULT, errno);
    }

    TEST(array_cmp, lhs_empty__rhs_filled) {
        struct ::array lhs, rhs;

        array_init(int, lhs, 0);
        array_init(int, rhs, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(-1, array_cmp(&lhs, &rhs));

        array_free(&rhs);
    }

    TEST(array_cmp, lhs_filled__rhs_empty) {
        struct ::array lhs, rhs;

        array_init(int, lhs, 5, 1, 2, 3, 4, 5);
        array_init(int, rhs, 0);

        EXPECT_EQ(1, array_cmp(&lhs, &rhs));

        array_free(&lhs);
    }

    TEST(array_cmp, both_filled__lhs_size_larger) {
        struct ::array lhs, rhs;

        array_init(int, lhs, 5, 1, 2, 3, 4, 5);
        array_init(int, rhs, 1, 6);

        EXPECT_EQ(1, array_cmp(&lhs, &rhs));

        array_free(&lhs);
        array_free(&rhs);
    }

    TEST(array_cmp, both_filled__rhs_size_larger) {
        struct ::array lhs, rhs;

        array_init(int, lhs, 1, 1);
        array_init(int, rhs, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(-1, array_cmp(&lhs, &rhs));

        array_free(&lhs);
        array_free(&rhs);
    }

    TEST(array_cmp, both_filled__both_sizes_equal__lhs_values_greater) {
        struct ::array lhs, rhs;

        array_init(int, lhs, 5, 6, 7, 8, 9, 10);
        array_init(int, rhs, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(1, array_cmp(&lhs, &rhs));

        array_free(&lhs);
        array_free(&rhs);
    }

    TEST(array_cmp, both_filled__both_sizes_equal__rhs_values_greater) {
        struct ::array lhs, rhs;

        array_init(int, lhs, 5, 1, 2, 3, 4, 5);
        array_init(int, rhs, 5, 6, 7, 8, 9, 10);

        EXPECT_EQ(-1, array_cmp(&lhs, &rhs));

        array_free(&lhs);
        array_free(&rhs);
    }

    TEST(array_cmp, both_filled__both_sizes_equal__both_values_equal) {
        struct ::array lhs, rhs;

        array_init(int, lhs, 5, 1, 2, 3, 4, 5);
        array_init(int, rhs, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(0, array_cmp(&lhs, &rhs));

        array_free(&lhs);
        array_free(&rhs);
    }

    // ── Method Tests (array_fill) ────────────────────────────────────────────────────────────────────────────────────
    TEST(array_fill, empty_array) {
        struct ::array array;
        array_init(int, array, 0);

        array_fill(int, array, 101);

        EXPECT_EQ(array.size, 0);
        EXPECT_EQ(array.values_p, nullptr);
        EXPECT_EQ(errno, EFAULT);

        // The pointer to the underlying array must be non-null in order
        // to test the last if-else statement branch in array_fill
        int* dummy_p = new int();
        array.values_p = dummy_p;
        array_fill(int, array, 101);
        EXPECT_EQ(errno, EINVAL);
        delete dummy_p;
    }

    TEST(array_fill, single_value_array) {
        struct ::array array;
        array_init(int, array, 1, 1);

        array_fill(int, array, 101);

        EXPECT_EQ(array.size, 1);
        EXPECT_NE(array.values_p, nullptr);

        EXPECT_EQ(101, array_at(int, array, 0));

        array_free(&array);
    }

    TEST(array_fill, multi_value_array) {
        struct ::array array;
        array_init(int, array, 5, 1, 2, 3, 4, 5);

        array_fill(int, array, 101);

        EXPECT_EQ(array.size, 5);
        EXPECT_NE(array.values_p, nullptr);

        EXPECT_EQ(101, array_at(int, array, 0));
        EXPECT_EQ(101, array_at(int, array, 1));
        EXPECT_EQ(101, array_at(int, array, 2));
        EXPECT_EQ(101, array_at(int, array, 3));
        EXPECT_EQ(101, array_at(int, array, 4));

        array_free(&array);
    }

    // ── Method Tests (array_empty) ───────────────────────────────────────────────────────────────────────────────────
    TEST(array_empty, empty_array) {
        struct ::array array;
        array_init(int, array, 0);

        EXPECT_EQ(array.size, 0);
        EXPECT_EQ(array.values_p, nullptr);
        EXPECT_TRUE(array_empty(&array));
    }

    TEST(array_empty, single_value_array) {
        struct ::array array;
        array_init(int, array, 1, 1);

        EXPECT_NE(array.size, 0);
        EXPECT_NE(array.values_p, nullptr);
        EXPECT_FALSE(array_empty(&array));

        array_free(&array);
    }

    TEST(array_empty, multi_value_array) {
        struct ::array array;
        array_init(int, array, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(array.size, 5);
        EXPECT_NE(array.values_p, nullptr);
        EXPECT_FALSE(array_empty(&array));

        array_free(&array);
    }

    // ── Method Tests (array_swap) ────────────────────────────────────────────────────────────────────────────────────
    TEST(array_swap, lhs_null) {
        struct ::array rhs;
        array_init(int, rhs, 0);

        EXPECT_EQ(-1, array_swap(nullptr, &rhs));
        EXPECT_EQ(errno, EFAULT);
    }

    TEST(array_swap, rhs_null) {
        struct ::array lhs;
        array_init(int, lhs, 0);

        EXPECT_EQ(-1, array_swap(&lhs, nullptr));
        EXPECT_EQ(errno, EFAULT);
    }

    TEST(array_swap, both_null) {
        EXPECT_EQ(-1, array_swap(nullptr, nullptr));
        EXPECT_EQ(errno, EFAULT);
    }

    TEST(array_swap, both_empty) {
        struct ::array lhs, rhs;

        array_init(int, lhs, 0);
        array_init(int, rhs, 0);

        EXPECT_EQ(EXIT_SUCCESS, array_swap(&lhs, &rhs));

        EXPECT_EQ(nullptr, lhs.values_p);
        EXPECT_EQ(nullptr, rhs.values_p);

        EXPECT_EQ(0, lhs.size);
        EXPECT_EQ(0, rhs.size);
    }

    TEST(array_swap, lhs_filled__rhs_empty) {
        struct ::array lhs, rhs;

        struct ::array matcher;
        array_init(int, matcher, 5, 1, 2, 3, 4, 5);

        array_init(int, lhs, 5, 1, 2, 3, 4, 5);
        array_init(int, rhs, 0);

        EXPECT_EQ(EXIT_SUCCESS, array_swap(&lhs, &rhs));
        EXPECT_TRUE(array_empty(&lhs));

        EXPECT_EQ(0, array_cmp(&rhs, &matcher));
        EXPECT_FALSE(array_empty(&rhs));

        array_free(&lhs);
        array_free(&rhs);
        array_free(&matcher);
    }

    TEST(array_swap, lhs_empty__rhs_filled) {
        struct ::array lhs, rhs;

        struct ::array matcher;
        array_init(int, matcher, 5, 1, 2, 3, 4, 5);

        array_init(int, lhs, 0);
        array_init(int, rhs, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(EXIT_SUCCESS, array_swap(&lhs, &rhs));
        EXPECT_TRUE(array_empty(&rhs));

        EXPECT_EQ(0, array_cmp(&lhs, &matcher));
        EXPECT_FALSE(array_empty(&lhs));

        array_free(&lhs);
        array_free(&rhs);
        array_free(&matcher);
    }

    TEST(array_swap, both_filled) {
        struct ::array lhs, rhs;

        struct ::array lhs_matcher, rhs_matcher;

        array_init(int, lhs, 5, 1, 2, 3, 4, 5);
        array_init(int, rhs, 5, 6, 7, 8, 9, 10);

        array_init(int, lhs_matcher, 5, 6, 7, 8, 9, 10);
        array_init(int, rhs_matcher, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(EXIT_SUCCESS, array_swap(&lhs, &rhs));

        EXPECT_FALSE(array_empty(&lhs));
        EXPECT_FALSE(array_empty(&rhs));

        EXPECT_EQ(0, array_cmp(&lhs, &lhs_matcher));
        EXPECT_EQ(0, array_cmp(&rhs, &rhs_matcher));

        array_free(&lhs);
        array_free(&rhs);

        array_free(&lhs_matcher);
        array_free(&rhs_matcher);
    }

    // ── Method Tests (array_cpy) ─────────────────────────────────────────────────────────────────────────────────────
    TEST(array_cpy, src_null) {
        struct ::array dst;
        array_init(int, dst, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(-1, array_cpy(nullptr, &dst));
        EXPECT_EQ(errno, EFAULT);

        array_free(&dst);
    }

    TEST(array_cpy, dst_null) {
        struct ::array src;
        array_init(int, src, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(-1, array_cpy(&src, nullptr));
        EXPECT_EQ(errno, EFAULT);

        array_free(&src);
    }

    TEST(array_cpy, both_empty) {
        struct ::array src, dst;

        array_init(int, src, 0);
        array_init(int, dst, 0);

        EXPECT_EQ(EXIT_SUCCESS, array_cpy(&src, &dst));

        EXPECT_TRUE(array_empty(&src));
        EXPECT_TRUE(array_empty(&dst));
    }

    TEST(array_cpy, different_sizes) {
        struct ::array src, dst;
        struct ::array matcher;

        array_init(int, src, 0);
        array_init(int, dst, 5, 1, 2, 3, 4, 5);

        array_init(int, matcher, 5, 1, 2, 3, 4, 5);

        EXPECT_EQ(-1, array_cpy(&src, &dst));
        EXPECT_EQ(errno, EINVAL);

        EXPECT_TRUE(array_empty(&src));
        EXPECT_EQ(0, array_cmp(&dst, &matcher));

        array_free(&dst);
    }

    TEST(array_cpy, same_sizes) {
        struct ::array src, dst;

        array_init(int, src, 5, 1, 2, 3, 4, 5);
        array_init(int, dst, 5, 6, 7, 8, 9, 10);

        EXPECT_EQ(EXIT_SUCCESS, array_cpy(&src, &dst));

        EXPECT_EQ(0, array_cmp(&dst, &src));
    }

    // ── Method Tests (array_mv) ──────────────────────────────────────────────────────────────────────────────────────


} // namespace array_tests
