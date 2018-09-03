#include <corona10/abstract_factory.hpp>

namespace corona10 {
Value::Value() noexcept : type_(Type::NONE) {}

Value::Value(std::string &&in_string) noexcept
    : type_(Type::STRING), string_value_(std::move(in_string)) {}

Value::Value(std::int64_t in_integer)
    : type_(Type::INTEGER), int_value_(in_integer) {}

AbstractFactory::~AbstractFactory() {}

Value *ValueFactory::CreateIntegerValue() {
  Value *value = new Value(0);
  return value;
}

Value *ValueFactory::CreateStringValue() {
  Value *value = new Value("");
  return value;
}
} // namespace corona10