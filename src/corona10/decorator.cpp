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
  std::string converted = ConverterDecorator::convert(str);
  int mid = converted.size() / 2;
  for (auto iter = converted.begin(); iter != converted.begin() + mid; iter++) {
    *iter = toupper(*iter);
  }
  return converted;
}

LastHalfLowerConverter::LastHalfLowerConverter(AbstractConverter *converter)
    : ConverterDecorator(converter) {}

LastHalfLowerConverter::~LastHalfLowerConverter() {}

std::string LastHalfLowerConverter::convert(std::string str) {
  std::string converted = ConverterDecorator::convert(str);
  int mid = converted.size() / 2;
  for (auto iter = converted.begin() + mid; iter != converted.end(); iter++) {
    *iter = tolower(*iter);
  }
  return converted;
}
} // namespace corona10