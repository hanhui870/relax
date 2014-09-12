#include <stdio.h>
#include <string.h>
#include <gtest/gtest.h>
#include "algorithm.h"

TEST(algorithm, add_multiply)
{
    EXPECT_EQ(2, add(5, -3));
    EXPECT_EQ(12, multiply(3, 4));
}
