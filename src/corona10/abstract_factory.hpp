#ifndef _ABSTRACT_FACTORY_HPP
#define _ABSTRACT_FACTORY_HPP

#include <string>

namespace corona10 {
class Value {
public:
  enum class Type { NONE = 0, STRING, INTEGER };
  Value() noexcept;
  explicit Value(Type type);
  explicit Value(std::string &&in_string) noexcept;
  explicit Value(std::int64_t in_integer);
  bool is_int() const { return type_ == Type::INTEGER; }
  bool is_string() const { return type_ == Type::STRING; }

private:
  std::string string_value_;
  std::int64_t int_value_;
  Type type_;
};

class AbstractFactory {
public:
  virtual ~AbstractFactory() = 0;
  virtual Value *CreateIntegerValue() = 0;
  virtual Value *CreateStringValue() = 0;
};

// Mayer Singleton
class ValueFactory : public AbstractFactory {
public:
  static ValueFactory &getInstance() {
    static ValueFactory instance;
    return instance;
  }
  virtual Value *CreateIntegerValue() override;
  virtual Value *CreateStringValue() override;

private:
  ValueFactory() = default;
  ~ValueFactory() = default;
  ValueFactory(const ValueFactory &) = delete;
  ValueFactory &operator=(const ValueFactory &) = delete;
};
} // namespace corona10
#endif