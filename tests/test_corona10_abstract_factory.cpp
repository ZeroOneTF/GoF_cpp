#include <fstream>

#include "gtest/gtest.h"

#include "corona10/abstract_factory.hpp"

TEST(abstract_factory, IntegerValueTest) {
  auto& factory  = corona10::ValueFactory::getInstance();
  corona10::Value* value = factory.CreateIntegerValue();
  ASSERT_TRUE(value->is_int());
  ASSERT_FALSE(value->is_string());
  delete value;
}

TEST(abstract_factory, StringValueTest) {
  auto& factory  = corona10::ValueFactory::getInstance();
  corona10::Value* value = factory.CreateStringValue();
  ASSERT_FALSE(value->is_int());
  ASSERT_TRUE(value->is_string());
  delete value;
}