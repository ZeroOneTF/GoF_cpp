#ifndef _ADATPOR_PATTERN_HPP
#define _ADATPOR_PATTERN_HPP
#include <vector>

namespace corona10 {
template <typename T> class Stack {
public:
  Stack() = default;
  virtual ~Stack(){};
  virtual void push(T data) = 0;
  virtual T pop() = 0;
};

// Object Adaptor Pattern
template <typename T> class VectorStack : public Stack<T> {
public:
  VectorStack() = default;
  virtual ~VectorStack() override {}

  virtual void push(T data) override { _vec.push_back(data); }

  virtual T pop() override {
    T ret = _vec.back();
    _vec.pop_back();
    return ret;
  }

  std::size_t size() { return _vec.size(); }

private:
  std::vector<T> _vec;
};
} // namespace corona10
#endif