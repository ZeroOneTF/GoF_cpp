#include <algorithm>
#include <string>

#include "corona10/decorator.hpp"

namespace corona10 {

AbstractConverter::~AbstractConverter() {}

std::string StringConverter::convert(std::string str) { return str; }

ConverterDecorator::ConverterDecorator(AbstractConverter *converter)
    : p_converter(converter) {}

ConverterDecorator::~ConverterDecorator() { delete p_converter; }

std::string ConverterDecorator::convert(std::string str) {
  return this->p_converter->convert(str);
}

FirstHalfUpperConverter::FirstHalfUpperConverter(AbstractConverter *converter)
    : ConverterDecorator(converter) {}

FirstHalfUpperConverter::~FirstHalfUpperConverter() {}

std::string FirstHalfUpperConverter::convert(std::string str) {
  int mid = str.size() / 2;
  for (auto iter = str.begin(); iter != str.begin() + mid; iter++) {
    *iter = toupper(*iter);
  }
  return ConverterDecorator::convert(str);
}

LastHalfLowerConverter::LastHalfLowerConverter(AbstractConverter *converter)
    : ConverterDecorator(converter) {}

LastHalfLowerConverter::~LastHalfLowerConverter() {}

std::string LastHalfLowerConverter::convert(std::string str) {
  int mid = str.size() / 2;
  for (auto iter = str.begin() + mid; iter != str.end(); iter++) {
    *iter = tolower(*iter);
  }
  return ConverterDecorator::convert(str);
}
} // namespace corona10