//
// Created by Mike Mitterer on 21.03.16.
//

#include <gtest/gtest.h>

TEST(basic_check, test_eq) {
    int i{10};
    int j{i};
EXPECT_EQ(1, 1);
}

TEST(basic_check, test_neq) {
EXPECT_NE(1, 0);
}

