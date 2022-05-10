#ifndef MATHQ__MATH_QUATERNION_H
#define MATHQ__MATH_QUATERNION_H

#include <sstream>

namespace mathq {



// ***************************************************************************
// *                   Quaternion Number
// ***************************************************************************
template <typename D>
class Quaternion {
private:
  D r_;
  D i_;
  D j_;
  D k_;

public:
  Quaternion() : r_(1), i_(1), j_(1), k_(1) {
  }
  Quaternion(const D r, const D i, const D j, const D k) : r_(r), i_(i), j_(j), k_(k) {
  }

  D real() const {
    return r_;
  }

  D imag() const {
    return i_;
  }

  D jmag() const {
    return j_;
  }

  D kmag() const {
    return k_;
  }

  D scalar() const {
    return r_;
  }


  Vector<D, 3> &vector() const {
    Vector<D, 3> *vector = new Vector<D, 3>({i_, j_, k_});
    return *vector;
  }


  Quaternion<D> &negate() {
    r_ = -r_;
    i_ = -i_;
    j_ = -j_;
    k_ = -k_;
    return *this;
  }

  D operator=(const D &y) {
    r_ = y.r_;
    i_ = y.i_;
    j_ = y.j_;
    k_ = y.k_;
  }

  inline static std::string classname() {
    D d;
    return "Quaternion" + display::getBracketedTypeName(d);
  }




  // arithmetic operators
  Quaternion<D> &operator+=(const Quaternion<D> &y) {
    *this = *this + y;
    return *this;
  }

  Quaternion<D> &operator-=(const Quaternion<D> &y) {
    *this = *this - y;
    return *this;
  }


  Quaternion<D> &operator*=(const D &y) {
    *this = *this * y;
    return *this;
  }

  Quaternion<D> &operator/=(const D &y) {
    *this = *this / y;
    return *this;
  }




  // stream << operator

  friend std::ostream &operator<<(std::ostream &stream, const Quaternion<D> &w) {

    /// TODO: create style for the i,j,k

    using namespace display;
    std::stringstream ss;

    if ((w.real() == 0) && (w.imag() == 0) && (w.jmag() == 0) && (w.kmag() == 0)) {
      stream << "0";
      return stream;
    }

    bool first = true;
    if (w.real() != 0) {
      first = false;
      dispval_strm(stream, w.real());
    }

    if (w.imag() != 0) {
      if (!first) {
        stream << " + ";
      }
      first = false;
      if (w.imag() != 1) {
        if (w.imag() == -1) {
          stream << "-";
        } else {
          dispval_strm(stream, w.imag());
        }
      }
      stream << "i";
    }

    if (w.jmag() != 0) {
      if (!first) {
        stream << " + ";
      }
      first = false;
      if (w.jmag() != 1) {
        if (w.jmag() == -1) {
          stream << "-";
        } else {
          dispval_strm(stream, w.jmag());
        }
      }
      stream << "j";
    }

    if (w.kmag() != 0) {
      if (!first) {
        stream << " + ";
      }
      first = false;
      if (w.kmag() != 1) {
        if (w.kmag() == -1) {
          stream << "-";
        } else {
          dispval_strm(stream, w.kmag());
        }
      }
      stream << "k";
    }

    return stream;
  }


  // template <class D>
  friend inline std::istream &operator>>(const std::string s, Quaternion<D> &w) {
    std::istringstream st(s);
    return (st >> w);
  }


  // stream >> operator

  // TODO: implement this
  friend std::istream &operator>>(std::istream &stream, Quaternion<D> &w) {
    return stream;
  }
};


// ***************************************************************************
// * j: the unit imaginary j
// * k: the unit imaginary k
// ***************************************************************************


namespace unit_quaternion {
const Quaternion<float> jF(0, 0, 1, 0);
const Quaternion<double> j(0, 0, 1, 0);
const Quaternion<long double> jL(0, 0, 1, 0);

const Quaternion<float> kF(0, 0, 0, 1);
const Quaternion<double> k(0, 0, 0, 1);
const Quaternion<long double> kL(0, 0, 0, 1);
}; // namespace unit_quaternion



// ***************************************************************************
// numbercast
// ***************************************************************************


template <typename I2, typename F1>
EnableMethodIf<IsQuaternion<I2>::value, I2>
numbercast(const Quaternion<F1> &y) {
  typedef typename IsQuaternion<I2>::RealType F2;
  F2 _r = numbercast<F2>(y.real());
  F2 _i = numbercast<F2>(y.imag());
  F2 _j = numbercast<F2>(y.jmag());
  F2 _k = numbercast<F2>(y.kmag());
  return Quaternion<F2>(_r, _i, _j, _k);
}


// ***************************************************************************
// // From real, Imaginary, complex
// // ***************************************************************************


// template <typename D>
// inline std::complex<D>
// Complex(const Quaternion<D> &x) {
//   return std::complex<D>(0, x.value());
// }


// ***************************************************************************
// * Quaternion arithmetic: Quaternion<D>
// ***************************************************************************

// +Quaternion<D>

template <typename D>
inline Quaternion<D>
operator+(const Quaternion<D> &x) {
  return x;
}

// -Quaternion<D>

template <typename D>
inline Quaternion<D>
operator-(const Quaternion<D> &x) {
  Quaternion<D> y = x;
  return y.negate();
}


// ***************************************************************************
// * Quaternion arithmetic: Quaternion<D1> OP Quaternion<D2>
// ***************************************************************************


// Quaternion<D1> + Quaternion<D2>

template <typename D1, typename D2>
inline mathq::Quaternion<typename mathq::AddType<D1, D2>::Type>
operator+(const Quaternion<D1> &x1, const Quaternion<D2> &x2) {
  typedef typename mathq::AddType<D1, D2>::Type D3;
  return mathq::Quaternion<D3>(
      x1.real() + x2.real(),
      x1.imaj() + x2.imaj(),
      x1.jmaj() + x2.jmaj(),
      x1.kmaj() + x2.kmaj());
  /// CAVEAT: If you have a trailing ',' in the parm list you wil get a mysterious "error: expected primary-expression before ‘(’ token"
}

// Quaternion<D1> - Quaternion<D2>

template <typename D1, typename D2>
inline mathq::Quaternion<typename mathq::AddType<D1, D2>::Type>
operator-(const Quaternion<D1> &x1, const Quaternion<D2> &x2) {
  typedef typename mathq::AddType<D1, D2>::Type D3;
  return mathq::Quaternion<D3>(
      x1.real() - x2.real(),
      x1.imaj() - x2.imaj(),
      x1.jmaj() - x2.jmaj(),
      x1.kmaj() - x2.kmaj());
  /// CAVEAT: If you have a trailing ',' in the parm list you wil get a mysterious "error: expected primary-expression before ‘(’ token"
}

// Quaternion<D1> * Quaternion<D2>

template <typename D1, typename D2>
inline auto
operator*(const Quaternion<D1> &x1, const Quaternion<D2> &x2) {
  typedef typename mathq::AddType<D1, D2>::Type D3;
  return mathq::Quaternion<D3>(
      x1.real() * x2.real() - x1.imag() * x2.imag() - x1.jmag() * x2.jmag() - x1.kmag() * x2.kmag(),
      x1.real() * x2.imag() + x1.imag() * x2.real() + x1.jmag() * x2.kmag() - x1.kmag() * x2.jmag(),
      x1.real() * x2.jmag() - x1.imag() * x2.kmag() + x1.jmag() * x2.real() + x1.kmag() * x2.imag(),
      x1.real() * x2.kmag() + x1.imag() * x2.jmag() - x1.jmag() * x2.imag() + x1.kmag() * x2.real());
  /// CAVEAT: If you have a trailing ',' in the parm list you wil get a mysterious "error: expected primary-expression before ‘(’ token"
}


// Quaternion<D1> / Quaternion<D2>

// template <typename D1, typename D2>
// inline auto
// operator/(const Quaternion<D1> &x1, const Quaternion<D2> &x2) {
//   typedef typename DivType<D1, D2>::Type D3;
//   return D3(x1.value() / x2.value());
// }






// // ***************************************************************************
// // * Quaternion-Real arithmetic:  Quaternion<D1> OP R2
// // *                                  R1  OP Quaternion<D2>
// // ***************************************************************************

// // Quaternion<D1> + R2

// template <typename D1, typename D2, typename = std::enable_if_t<std::is_arithmetic<D2>::value>>
// inline std::complex<typename AddType<D1, D2>::Type>
// operator+(const Quaternion<D1> &xi, const D2 &xr) {
//   typedef typename AddType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(xr, xi.value());
// }

// // D1 + Quaternion<D2>

// template <typename D1, typename D2, typename = std::enable_if_t<std::is_arithmetic<D1>::value>>
// inline std::complex<typename AddType<D1, D2>::Type>
// operator+(const D1 &xr, const Quaternion<D2> &xi) {
//   typedef typename AddType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(xr, xi.value());
// }


// // Quaternion<D1> - D2

// template <typename D1, typename D2, typename = std::enable_if_t<std::is_arithmetic<D2>::value>>
// inline std::complex<typename AddType<D1, D2>::Type>
// operator-(const Quaternion<D1> &xi, const D2 &xr) {
//   typedef typename AddType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(-xr, xi.value());
// }

// // D1 - Quaternion<D2>

// template <typename D1, typename D2, typename = std::enable_if_t<std::is_arithmetic<D1>::value>>
// inline std::complex<typename AddType<D1, D2>::Type>
// operator-(const D1 &xr, const Quaternion<D2> &xi) {
//   typedef typename AddType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(xr, -xi.value());
// }


// Quaternion<D1> * D2

template <typename D1, typename D2, typename = std::enable_if_t<std::is_arithmetic<D2>::value>>
inline Quaternion<typename MultType<D1, D2>::Type>
operator*(const Quaternion<D1> &x1, const D2 &x2) {
  typedef typename MultType<D1, D2>::Type D3;
  typedef Quaternion<D3> T3;
  return T3(
      x1.real() * x2,
      x1.imag() * x2,
      x1.jmag() * x2,
      x1.kmag() * x2);
}

// D1 * Quaternion<D2>

template <typename D1, typename D2, typename = std::enable_if_t<std::is_arithmetic<D2>::value>>
inline Quaternion<typename MultType<D1, D2>::Type>
operator*(const D1 &x1, const Quaternion<D2> &x2) {
  typedef typename MultType<D1, D2>::Type D3;
  typedef Quaternion<D3> T3;
  return T3(
      x1 * x2.real(),
      x1 * x2.imag(),
      x1 * x2.jmag(),
      x1 * x2.kmag());
}


// // Quaternion<D1> / D2

// template <typename D1, typename D2, typename = std::enable_if_t<std::is_arithmetic<D2>::value>>
// inline Quaternion<typename DivType<D1, D2>::Type>
// operator/(const Quaternion<D1> &x1, const D2 &x2) {
//   typedef typename DivType<D1, D2>::Type D3;
//   typedef Quaternion<D3> T3;
//   return T3(x1.value() / x2);
// }

// // D1 / Quaternion<D2>

// template <typename D1, typename D2, typename = std::enable_if_t<std::is_arithmetic<D2>::value>>
// inline Quaternion<typename DivType<D1, D2>::Type>
// operator/(const D1 &x1, const Quaternion<D2> &x2) {
//   typedef typename DivType<D1, D2>::Type D3;
//   typedef Quaternion<D3> T3;
//   return T3(-x1 / x2.value());
// }




// ***************************************************************************
// * Quaternion-Imaginary arithmetic:  Quaternion<D1> OP R2
// *                                  R1  OP Quaternion<D2>
// ***************************************************************************

// // Quaternion<D1> + Imaginary<D2>

// template <typename D1, typename D2>
// inline Imaginary<typename AddType<D1, D2>::Type>
// operator+(const Quaternion<D1> &xi, const Imaginary<D2> &z) {
//   typedef typename AddType<D1, D2>::Type D3;
//   typedef typename Imaginary<D3> T3;
//   return T3(real(z), xi.value() + imag(z));
// }

// // Imaginary<D1> + Quaternion<D2>
// template <typename D1, typename D2>
// inline Imaginary<typename AddType<D1, D2>::Type>
// operator+(const Imaginary<D2> &z, const Quaternion<D1> &xi) {
//   typedef typename AddType<D1, D2>::Type D3;
//   typedef typename Imaginary<D3> T3;
//   return T3(real(z), imag(z) + xi.value());
// }


// // Quaternion<D1> - Imaginary<D2>

// template <typename D1, typename D2>
// inline Imaginary<typename SubType<D1, D2>::Type>
// operator-(const Quaternion<D1> &xi, const Imaginary<D2> &z) {
//   typedef typename SubType<D1, D2>::Type D3;
//   typedef typename Imaginary<D3> T3;
//   return T3(-real(z), xi.value() - imag(z));
// }

// // Imaginary<D1> - Quaternion<D2>

// template <typename D1, typename D2>
// inline Imaginary<typename SubType<D1, D2>::Type>
// operator-(const Imaginary<D2> &z, const Quaternion<D1> &xi) {
//   typedef typename SubType<D1, D2>::Type D3;
//   typedef typename Imaginary<D3> T3;
//   return T3(real(z), imag(z) - xi.value());
// }


// Quaternion<D1> * Imaginary<D2>

template <typename D1, typename D2>
inline Quaternion<typename MultType<D1, D2>::Type>
operator*(const Quaternion<D1> &x1, const Imaginary<D2> &x2) {
  typedef typename MultType<D1, D2>::Type D3;
  typedef typename mathq::Quaternion<D3> T3;
  return T3(
      -x1.imag() * x2.value(),
      x1.real() * x2.value(),
      x1.kmag() * x2.value(),
      -x1.jmag() * x2.value());
}


// Imaginary<D2> * Quaternion<D1>

template <typename D1, typename D2>
inline Quaternion<typename MultType<D1, D2>::Type>
operator*(const Imaginary<D2> &x1, const Quaternion<D1> &x2) {
  typedef typename MultType<D1, D2>::Type D3;
  typedef typename mathq::Quaternion<D3> T3;
  return T3(
      x1.value() * x2.imag(),
      -x1.value() * x2.real(),
      -x1.value() * x2.kmag(),
      x1.value() * x2.jmag());
}


// // Quaternion<D1> / Imaginary<D2>

// template <typename D1, typename D2>
// inline Imaginary<typename DivType<D1, D2>::Type>
// operator/(const Quaternion<D1> &xi, const Imaginary<D2> &z) {
//   typedef typename DivType<D1, D2>::Type D3;
//   typedef typename Imaginary<D3> T3;
//   return T3(-xi.value() * imag(z), xi.value() * real(z));
// }

// // Imaginary<D2> / Quaternion<D1>

// template <typename D1, typename D2>
// inline Imaginary<typename DivType<D1, D2>::Type>
// operator/(const Imaginary<D2> &z, const Quaternion<D1> &xi) {
//   typedef typename DivType<D1, D2>::Type D3;
//   typedef typename Imaginary<D3> T3;
//   D3 topR = xi.value() * imag(z);
//   D3 topI = xi.value() * real(z);
//   D3 bot = real(z) * real(z) + imag(z) * imag(z);
//   return T3(topR / bot, topI / bot);
// }





// // ***************************************************************************
// // * Quaternion arithmetic:  Quaternion<D1> OP complex<D2>
// // *                          complex<D1> OP Quaternion<D2>
// // ***************************************************************************

// // Quaternion<D1> + complex<D2>

// template <typename D1, typename D2>
// inline std::complex<typename AddType<D1, D2>::Type>
// operator+(const Quaternion<D1> &xi, const std::complex<D2> &z) {
//   typedef typename AddType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(real(z), xi.value() + imag(z));
// }

// // complex<D1> + Quaternion<D2>
// template <typename D1, typename D2>
// inline std::complex<typename AddType<D1, D2>::Type>
// operator+(const std::complex<D2> &z, const Quaternion<D1> &xi) {
//   typedef typename AddType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(real(z), imag(z) + xi.value());
// }


// // Quaternion<D1> - complex<D2>

// template <typename D1, typename D2>
// inline std::complex<typename SubType<D1, D2>::Type>
// operator-(const Quaternion<D1> &xi, const std::complex<D2> &z) {
//   typedef typename SubType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(-real(z), xi.value() - imag(z));
// }

// // complex<D1> - Quaternion<D2>

// template <typename D1, typename D2>
// inline std::complex<typename SubType<D1, D2>::Type>
// operator-(const std::complex<D2> &z, const Quaternion<D1> &xi) {
//   typedef typename SubType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(real(z), imag(z) - xi.value());
// }


// // Quaternion<D1> * complex<D2>

// template <typename D1, typename D2>
// inline std::complex<typename MultType<D1, D2>::Type>
// operator*(const Quaternion<D1> &xi, const std::complex<D2> &z) {
//   typedef typename MultType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(-xi.value() * imag(z), xi.value() * real(z));
// }


// // complex<D2> * Quaternion<D1>

// template <typename D1, typename D2>
// inline std::complex<typename MultType<D1, D2>::Type>
// operator*(const std::complex<D2> &z, const Quaternion<D1> &xi) {
//   typedef typename MultType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(-imag(z) * xi.value(), real(z) * xi.value());
// }


// // Quaternion<D1> / complex<D2>

// template <typename D1, typename D2>
// inline std::complex<typename DivType<D1, D2>::Type>
// operator/(const Quaternion<D1> &xi, const std::complex<D2> &z) {
//   typedef typename DivType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   return T3(-xi.value() * imag(z), xi.value() * real(z));
// }

// // complex<D2> / Quaternion<D1>

// template <typename D1, typename D2>
// inline std::complex<typename DivType<D1, D2>::Type>
// operator/(const std::complex<D2> &z, const Quaternion<D1> &xi) {
//   typedef typename DivType<D1, D2>::Type D3;
//   typedef typename std::complex<D3> T3;
//   D3 topR = xi.value() * imag(z);
//   D3 topI = xi.value() * real(z);
//   D3 bot = real(z) * real(z) + imag(z) * imag(z);
//   return T3(topR / bot, topI / bot);
// }



// //*******************************************************
// //          Typedefs
// //*******************************************************


// typedef Quaternion<float> ImFloat;
// typedef Quaternion<double> ImDouble;
// typedef Quaternion<long double> ImLongDouble;
// typedef Quaternion<char> ImChar;
// typedef Quaternion<signed char> ImSignedChar;
// typedef Quaternion<short> ImShort;
// typedef Quaternion<int> ImInt;
// typedef Quaternion<long> ImLong;
// typedef Quaternion<long long> ImLongLong;
// typedef Quaternion<unsigned char> ImUnsignedChar;
// typedef Quaternion<unsigned short> ImUnsignedShort;
// typedef Quaternion<unsigned int> ImUnsignedInt;
// typedef Quaternion<unsigned long> ImUnsignedLong;
// typedef Quaternion<unsigned long long> ImUnsignedLongLong;



//*******************************************************
//          unary funcs
//*******************************************************

// real(z)

template <typename D>
inline D real(const Quaternion<D> &z) {
  return z.real();
}

// imag(z)

template <typename D>
inline D imag(const Quaternion<D> &z) {
  return z.imag();
}

// jmag(z)

template <typename D>
inline D jmag(const Quaternion<D> &z) {
  return z.jmag();
}

// kmag(z)

template <typename D>
inline D kmag(const Quaternion<D> &z) {
  return z.kmag();
}

// // arg(z)  -  this is pi/2, but let the std library calculate
// //            since we don't know data type

// template <typename D>
// inline D arg(const Quaternion<D> &z) {
//   using std::arg;
//   std::complex<D> dummy(0, 1);
//   return arg(dummy);
// }


// // proj(z)  -  the "projection of z onto the Riemann sphere"--NOT REALLY
// //
// //             For most z, std::proj(z)==z, but all complex infinities,
// //             even the numbers where one component is infinite and the
// //             other is NaN, become positive real infinity, (INFINITY, 0)
// //             or (INFINITY, -0). The sign of the imaginary (zero) component
// //             is the sign of std::imag(z).

// template <typename D>
// inline std::complex<D> proj(const Quaternion<D> &z) {
//   using std::proj;
//   std::complex<D> c(0, z.value());
//   return proj(c);
// }


// abs(z)

template <typename D>
inline D abs(const Quaternion<D> &z) {
  return std::sqrt(z.real() * z.real() + z.imag() * z.imag() + z.jmag() * z.jmag() + z.kmag() * z.kmag());
}

// normsqr(z) -

template <typename D>
inline D normsqr(const Quaternion<D> &z) {
  return z.real() * z.real() + z.imag() * z.imag() + z.jmag() * z.jmag() + z.kmag() * z.kmag();
}


// // conj(z)  - we go against C++  convention
// //            Note: C++ std lib returns complex number for conj(real)

// template <typename D>
// inline Quaternion<D>
// conj(const Quaternion<D> &z) {
//   return -z;
// }



// // complex conjugate OPERTOR ~

// template <typename D, typename = std::enable_if_t<std::is_floating_point<D>::value>>
// Quaternion<D>
// operator~(const Quaternion<D> &z) {
//   return conj(z);
// }



// // polar(z)

// template <typename D>
// inline std::complex<D>
// polar(const Quaternion<D> &z) {
//   return std::complex(abs(z), arg(z));
// }

// // exp(z)

// template <typename D>
// inline std::complex<D>
// exp(const Quaternion<D> &z) {
//   const D &val = z.value();
//   return std::complex(cos(val), sin(val));
// }

// // log(z)

// template <typename D>
// inline std::complex<D>
// log(const Quaternion<D> &z) {
//   using std::arg;
//   using std::log;
//   const D &val = z.value();
//   return std::complex(log(val), arg(z));
// }


// // log10
// template <typename D>
// std::complex<D>
// log10(const Quaternion<D> &z) {
//   using std::log;
//   const D A0 = 1 / log(D(10));
//   return A0 * log(z);
// }


// // log2
// template <typename D>
// std::complex<D>
// log2(const Quaternion<D> &z) {
//   using std::log;
//   const D A0 = 1 / log(D(2));
//   return A0 * log(z);
// }


// // pow(I1,I2)
// template <typename D1, typename D2>
// inline std::complex<typename MultType<D1, D2>::Type>
// pow(const Quaternion<D1> &x1, const Quaternion<D2> &x2) {
//   using std::pow;
//   typedef typename MultType<D1, D2>::Type D3;
//   return pow(
//       Complex(numbercast<Quaternion<D3>>(x1)),
//       Complex(numbercast<Quaternion<D3>>(x2)));
// }


// // pow(I1,R2)
// template <typename D1, typename D2, typename = std::enable_if_t<std::is_arithmetic<D2>::value>>
// inline std::complex<typename MultType<D1, D2>::Type>
// pow(const Quaternion<D1> &x1, const D2 &x2) {
//   using std::pow;
//   typedef typename MultType<D1, D2>::Type D3;
//   return pow(
//       Complex(numbercast<Quaternion<D3>>(x1)),
//       numbercast<D3>(x2));
// }

// // pow(R1,I2)
// template <typename D1, typename D2, typename = std::enable_if_t<std::is_arithmetic<D1>::value>>
// inline std::complex<typename MultType<D1, D2>::Type>
// pow(const D1 &x1, const Quaternion<D2> &x2) {
//   using std::pow;
//   typedef typename MultType<D1, D2>::Type D3;
//   return pow(
//       numbercast<D3>(x1),
//       Complex(numbercast<Quaternion<D3>>(x2)));
// }


// // pow(I1,C2)
// template <typename D1, typename D2>
// inline std::complex<typename MultType<D1, D2>::Type>
// pow(const Quaternion<D1> &x1, const std::complex<D2> &x2) {
//   using std::pow;
//   typedef typename MultType<D1, D2>::Type D3;
//   return pow(
//       Complex(numbercast<Quaternion<D3>>(x1)),
//       numbercast<std::complex<D3>>(x2));
// }

// // pow(C1,I2)
// template <typename D1, typename D2>
// inline std::complex<typename MultType<D1, D2>::Type>
// pow(const std::complex<D1> &x1, const Quaternion<D2> &x2) {
//   using std::pow;
//   typedef typename MultType<D1, D2>::Type D3;
//   return pow(
//       numbercast<std::complex<D3>>(x1),
//       Complex(numbercast<Quaternion<D3>>(x2)));
// }


// // sqrt
// template <typename D>
// std::complex<D>
// sqrt(const Quaternion<D> &z) {
//   using std::sqrt;
//   const D A0 = sqrt(z.value() / 2);
//   return A0 * std::complex<D>(1, 1);
// }


// // sqr
// template <typename D>
// D sqr(const Quaternion<D> &z) {
//   return -z.value() * z.value();
// }

// // cube
// template <typename D>
// Quaternion<D> cube(const Quaternion<D> &z) {
//   return Quaternion<D>(-z.value() * z.value() * z.value());
// }




// // sin
// template <typename D>
// Quaternion<D>
// sin(const Quaternion<D> &z) {
//   using std::sin;
//   return Quaternion<D>(sin(z.value()));
// }

// // cos
// template <typename D>
// D cos(const Quaternion<D> &z) {
//   using std::cos;
//   return cos(z.value());
// }

// // tan
// template <typename D>
// Quaternion<D>
// tan(const Quaternion<D> &z) {
//   using std::tan;
//   return Quaternion<D>(tan(z.value()));
// }

// // asin
// template <typename D>
// Quaternion<D>
// asin(const Quaternion<D> &z) {
//   using std::asin;
//   return Quaternion<D>(asin(z.value()));
// }

// // acos
// template <typename D>
// std::complex<D>
// acos(const Quaternion<D> &z) {
//   using std::acos;
//   return acos(Complex(z));
// }

// // atan
// template <typename D>
// std::complex<D>
// atan(const Quaternion<D> &z) {
//   using std::atan;
//   return atan(Complex(z));
// }

// // atan2
// template <typename D>
// std::complex<D>
// atan2(const Quaternion<D> &z) {
//   using std::atan2;
//   return atan2(z.value(), 0);
// }



// // sinh
// template <typename D>
// Quaternion<D>
// sinh(const Quaternion<D> &z) {
//   using std::sinh;
//   return Quaternion<D>(sinh(z.value()));
// }

// // cosh
// template <typename D>
// D cosh(const Quaternion<D> &z) {
//   using std::cosh;
//   return cosh(z.value());
// }

// // tanh
// template <typename D>
// Quaternion<D>
// tanh(const Quaternion<D> &z) {
//   using std::tanh;
//   return Quaternion<D>(tanh(z.value()));
// }


// // asinh
// template <typename D>
// std::complex<D>
// asinh(const Quaternion<D> &z) {
//   using std::asinh;
//   return asinh(Complex(z));
// }

// // acosh
// template <typename D>
// std::complex<D>
// acosh(const Quaternion<D> &z) {
//   using std::acosh;
//   return acosh(Complex(z));
// }

// // atanh
// template <typename D>
// std::complex<D>
// atanh(const Quaternion<D> &z) {
//   using std::atanh;
//   return atanh(Complex(z));
// }




// // imaginary rounding

// template <typename D>
// Quaternion<D> round(const Quaternion<D> &x) {
//   using std::round;
//   return Quaternion<D>(round(x.value()));
// }

// // Quaternion - sgn
// template <typename D>
// Quaternion<D> sgn(const Quaternion<D> &z) {
//   return Quaternion<D>(sgn(z.value()));
// }

// // Quaternion - floor
// template <typename D>
// Quaternion<D> floor(const Quaternion<D> &z) {
//   using std::floor;
//   return Quaternion<D>(floor(z.value()));
// }

// // Quaternion - ceil
// template <typename D>
// Quaternion<D> ceil(const Quaternion<D> &z) {
//   using std::ceil;
//   return Quaternion<D>(ceil(z.value()));
// }



// // Quaternion - roundzero
// template <typename D>
// Quaternion<D> roundzero(const Quaternion<D> &z, const D tolerance = Functions<D>::tolerance) {
//   return Quaternion<D>(roundzero(z.value(), tolerance));
// }

// // Quaternion - approx

// template <typename D1, typename D2>
// bool approx(const Quaternion<D1> &x, const Quaternion<D2> &y, const typename AddType<D1, D2>::Type tol = Functions<typename AddType<D1, D2>::Type>::tolerance) {
//   return mathq::approx(x.value(), y.value(), tol);
// }



}; // namespace mathq


#endif
