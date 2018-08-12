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

  std::string input1 = "";
  std::string output1 = converter->convert(input1);
  ASSERT_EQ(output1, "");

  std::string input2 = "H";
  std::string output2 = converter->convert(input2);
  ASSERT_EQ(output2, "h");
  delete converter;
}