/// WARNING: Whatever you do, don’t mix specialization and overloading
///
#include <print>
#include <string>
#include <vector>
/// simple template specialization example:

template <int N> struct Factorial {
  static constexpr int value = N * Factorial<N - 1>::value;
};

// specializing for the value 0
template <> struct Factorial<0> {
  static constexpr int value = 1;
};

// NOTE: function template partial specialization is not allowed :)
// but you can use overload
//
// https://www.fluentcpp.com/2017/08/15/function-templates-partial-specialization-cpp/

// consider this
template <typename T> void do_something(const T &x) {
  std::print("do something...");
}

// specialization of f
template <> void do_something<std::string>(const std::string &x) {
  std::print("template (string): {}", x);
}

// ... or
void do_something(const std::string &x) {

  std::print("overload (string): {}", x);
}
/*
 * NOTE: imaginary cpp - template partial specialization
 * template <typename T>
 * void f<std::vector<T>>(std::vector<T> const& v)
 * {
 * 	// something here
 * }
 */

template <typename T>
void do_something(std::vector<T> const &v) // #2
{
  std::print("vector");
  // body of f for vectors
}


int main() {
  do_something(std::vector<int>{}); // this call goes to #2
  return 0;
}
