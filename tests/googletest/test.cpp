#include <stdio.h>
#include <string.h>

#include <gtest/gtest.h>
#include "algorithm.h"

TEST(algorithm, add_multiply)
{
    EXPECT_EQ(2, add(5, -3));
    EXPECT_EQ(12, multiply(3, 4));
}

TEST(system, strict_ansi)
{
#ifndef __STRICT_ANSI__
 std::cout<<"__STRICT_ANSI__ macro defined."<<std::endl;
#endif
}
