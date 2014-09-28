#include <stdio.h>
#include <string.h>

#include <gtest/gtest.h>
#include "template.h"

TEST(cpp_template, add_action)
{
    EXPECT_EQ(2, add(5, -3));
    EXPECT_EQ(5, add(3.7, 1.3));
}
