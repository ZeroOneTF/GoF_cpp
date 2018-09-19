#include <fstream>

#include "gtest/gtest.h"

#include "corona10/adaptor_pattern.hpp"

TEST(adaptor_pattern, StackVectorTest) {
    corona10::VectorStack<int> stack;
    constexpr int total_number = 10;
    for(int i = 0; i < total_number; i++) {
        stack.push(i);
        ASSERT_EQ(stack.size(), i+1);
    }

    for(int i = 0; i < total_number; i++) {
        int value = stack.pop();
        ASSERT_EQ(value, 10-i-1);
        ASSERT_EQ(stack.size(), 10-i-1);
    }
}