#include "gtest/gtest.h"

#include "corona10/decorator.hpp"

TEST(example, FirstHalfUpperTest) {
  corona10::AbstractConverter *converter =
      new corona10::FirstHalfUpperConverter(new corona10::StringConverter());
  std::string input = "HelloWorld";
  std::string output = converter->convert(input);
  ASSERT_EQ(output, "HELLOWorld");
  delete converter;
}

TEST(example, LastHalfLowerTest) {
  corona10::AbstractConverter *converter =
      new corona10::LastHalfLowerConverter(new corona10::StringConverter());
  std::string input = "HelloWorld";
  std::string output = converter->convert(input);
  ASSERT_EQ(output, "Helloworld");
  delete converter;
}

TEST(example, MixtureTest) {
  corona10::AbstractConverter *converter =
      new corona10::FirstHalfUpperConverter(
          new corona10::LastHalfLowerConverter(
              new corona10::StringConverter()));
  std::string input = "HelloWorld";
  std::string output = converter->convert(input);
  ASSERT_EQ(output, "HELLOworld");
  delete converter;
}