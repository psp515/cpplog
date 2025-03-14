//
// Created by kolbe on 14.03.2025.
//

#include <gtest/gtest.h>
#include <cpplog/sinks/file_sink.h>

using namespace std;
using namespace cpplog::sinks;
using namespace cpplog::common;

int Add(int a, int b) {
  return a + b;
}

// Test case
TEST(AdditionTest, PositiveNumbers) {
  EXPECT_EQ(Add(2, 3), 5);  // Checks that 2 + 3 = 5
  EXPECT_EQ(Add(7, 3), 10); // Checks that 7 + 3 = 10
}
