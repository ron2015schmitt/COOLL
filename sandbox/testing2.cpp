#include <vector>
#include <array>

#define MATHQ_DEBUG 0
#include "mathq.h"
#include "macros.h"


struct Hello {
  int helloworld() { return 0; }
};

struct Generic {};

// SFINAE test
template <typename T>
class has_helloworld {
  typedef char one;
  struct two {
    char x[2];
  };

  template <typename C>
  static one test(decltype(&C::helloworld));
  template <typename C>
  static two test(...);

public:
  enum { value = sizeof(test<T>(0)) == sizeof(char) };
};


template <bool B>
using EnableIfB = typename std::enable_if<B, int>::type;


template <typename T, size_t D>
class yabba {
  T values[D];

public:
  template <size_t D1 = D, EnableIfB<D1 == 1> = 0>
  yabba(T t1) {
    values[0] = t1;
  }
  template <size_t D1 = D, EnableIfB<D1 == 2> = 0>
  yabba(T t1, T t2) {
    values[0] = t1;
    values[1] = t2;
  }

  template <size_t D1 = D, EnableIfB<D1 == 3> = 0>
  yabba(T t1, T t2, T t3) {
    values[0] = t1;
    values[1] = t2;
    values[2] = t3;
  }

  T operator[](int i) {
    return values[i];
  }
};




template <class D, int N>
class Arraytype {
public:
  typedef std::array<D, N> Type;
};

template <class D>
class Arraytype<D, 0> {
public:
  typedef std::valarray<D> Type;
};





int main(int argc, char *argv[]) {
  const double pi = M_PI;
  std::string myname = argv[0];
  using namespace mathq;
  using namespace display;

  // force color even if piped to more,less or a file
  Terminal::setColorOverride(true);
  Terminal::setOverrideValue(true);

  cr();
  cr();
  mout << StyledString::get(HORLINE);
  mout << "running: " << CREATESTYLE(BOLD).apply(myname) << std::endl;


  mout << "MATHQ_DEBUG=" << MATHQ_DEBUG << std::endl;

  print_mathq_info();

  if constexpr (3 > 1) {
    int x = 5;
    disp(x);
  } else {
    int y = 7;
    disp(y);
  }


  Arraytype<double, 3>::Type x;
  Arraytype<double, 0>::Type y;
  x[0] = 1.1;
  x[1] = 2.2;
  x[2] = 3.3;
  tdisp(x);
  tdisp(y);

  disp(has_helloworld<Hello>::value);
  disp(has_helloworld<Generic>::value);

  {
    Vector<double, 3> v;
    tdisp(v.size());
    v(0) = 1.1;
    v(1) = 2.2;
    v(2) = 3.3;
    tdisp(v);
  }

  {
    Vector<double> v(3);
    tdisp(v.size());
    v(0) = 1.1;
    v(1) = 2.2;
    v(2) = 3.3;
    tdisp(v);
  }

  {
    yabba<double, 3> v(1, 2, 3);
    tdisp(v[0]);
    tdisp(v[1]);
    tdisp(v[2]);
  }


  {
    std::valarray<double> val;
    tdisp(val);
    val.resize(4);
    tdisp(val);
  }



  cr();
  mout << "done: " << CREATESTYLE(BOLD).apply(myname) << std::endl;
  mout << StyledString::get(HORLINE);
  cr();

  return 0;
}
