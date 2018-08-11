#include <string>

namespace corona10 {

class AbstractConverter {
public:
  virtual std::string convert(std::string str) = 0;
  virtual ~AbstractConverter() = 0;
};

class StringConverter : public AbstractConverter {
public:
  StringConverter() {}
  ~StringConverter() {}
  std::string convert(std::string str) override;
};

class ConverterDecorator : public AbstractConverter {
public:
  explicit ConverterDecorator(AbstractConverter *converter);
  ~ConverterDecorator();
  std::string convert(std::string str) override;

private:
  AbstractConverter *p_converter;
};

class FirstHalfUpperConverter : public ConverterDecorator {
public:
  explicit FirstHalfUpperConverter(AbstractConverter *converter);
  ~FirstHalfUpperConverter();
  std::string convert(std::string str) override;
};

class LastHalfLowerConverter : public ConverterDecorator {
public:
  explicit LastHalfLowerConverter(AbstractConverter *converter);
  ~LastHalfLowerConverter();
  std::string convert(std::string str) override;
};

} // namespace corona10
