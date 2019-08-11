// START-OF-NOTICE
// Copyright 2003, Columbia University
// Authors: Ron Schmitt
//
//
// This file is part of the Columbia Object Oriented 
// Linear-algebra Library (COOLL).
//
// You should have received a copy of the License Agreement for the
// COOLL along with the software;  see the file LICENSE.  
// If not, contact
// Department of Applied Physics and Applied Mathematics
// Columbia Univeristy 
// New York, NY 10027
//
// Permission to modify the code and to distribute modified code is
// granted, provided the text of this NOTICE is retained, a notice that
// the code was modified is included with the above COPYRIGHT NOTICE and
// with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
// file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//
// END-OF-NOTICE
//===========================================================================





#ifndef COMPLEXAPP_H
#define COMPLEXAPP_H



#include <cmath>
#include <complex>
#include <string>



namespace COOLL {


  /****************************************************************************
   *              Binary applicative templates 
   ****************************************************************************/



  // polar(r,phi)

  template <class D > class ApPolar {
  public:
    ApPolar() { }

    static inline std::complex<D> apply(D r, D phi) { 
      using std::polar;
      return polar(r,phi); 
    }

    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = "polar(" + sa + " , " + sb +  ")";
      return sout;
    }

  };

 

  // complex(x,y)

  template <class D > class ApComplex {
  public:
    ApComplex() { }

    static inline std::complex<D> apply(D x, D y) { 
      return std::complex<D>(x,y); 
    }

    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = "complex(" + sa + " , " + sb +  ")";
      return sout;
    }

  };





  // y = acomplex + breal

  template <class DataT> class ApAddCR {
  public:
    ApAddCR() { }
  
    static inline std::complex<DataT> apply( std::complex<DataT> a, DataT b) { 
      return a+b; 
    }

    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = sa + " + " + sb;
      return sout;
    }

  };
  // y = areal + bcomplex

  template <class DataT> class ApAddRC {
  public:
    ApAddRC() { }
  
    static inline std::complex<DataT> apply(DataT a, std::complex<DataT> b) { 
      return a+b; 
    }

    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = sa + " + " + sb;
      return sout;
    }

  };




  // y = acomplex - breal

  template <class DataT> class ApSubtractCR {
  public:
    ApSubtractCR() { }
  
    static inline std::complex<DataT> apply( std::complex<DataT> a, DataT b) { 
      return a-b; 
    }

    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = sa + " - " + sb;
      return sout;
    }

  };
  // y = areal - bcomplex

  template <class DataT> class ApSubtractRC {
  public:
    ApSubtractRC() { }
  
    static inline std::complex<DataT> apply(DataT a, std::complex<DataT> b) { 
      return a-b; 
    }

    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = sa + " - " + sb;
      return sout;
    }

  };




  // y = acomplex * breal

  template <class DataT> class ApMultiplyCR {
  public:
    ApMultiplyCR() { }
  
    static inline std::complex<DataT> apply( std::complex<DataT> a, DataT b) { 
      return a*b; 
    }

    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = sa + " * " + sb;
      return sout;
    }

  };
  // y = areal * bcomplex

  template <class DataT> class ApMultiplyRC {
  public:
    ApMultiplyRC() { }
  
    static inline std::complex<DataT> apply(DataT a, std::complex<DataT> b) { 
      return a*b; 
    }

    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = sa + " * " + sb;
      return sout;
    }

  };




  // y = acomplex / breal

  template <class DataT> class ApDivideCR {
  public:
    ApDivideCR() { }
  
    static inline std::complex<DataT> apply( std::complex<DataT> a, DataT b) { 
      return a/b; 
    }

    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = sa + " / " + sb;
      return sout;
    }

  };
  // y = areal / bcomplex

  template <class DataT> class ApDivideRC {
  public:
    ApDivideRC() { }
  
    static inline std::complex<DataT> apply(DataT a, std::complex<DataT> b) { 
      return a/b; 
    }

    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = sa + " / " + sb;
      return sout;
    }

  };






  // y = pow(acomplex,breal),  ie. a raised to the b power
  template <class D> class ApPowCR {
  public:
    ApPowCR() { }
    static inline std::complex<D> apply(std::complex<D> a, D b) { 
      using std::pow;
      return pow(a,b); 
    }
    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = "pow( " + sa + " , " + sb + " )";
      return sout;
    }
  };
  // y = pow(areal,bcomplex),  ie. a raised to the b power
  template <class D> class ApPowRC {
  public:
    ApPowRC() { }
    static inline std::complex<D> apply( D a, std::complex<D> b) { 
      using std::pow;
      return pow(a,b); 
    }
    static std::string debugtxt(const std::string& sa, const std::string& sb) {
      std::string sout = "pow( " + sa + " , " + sb + " )";
      return sout;
    }
  };





  /****************************************************************************
   *              unary applicative templates 
   ****************************************************************************/


  // abs(a)

  template <class D> class ApCAbs {
  public:
    ApCAbs() { }

    static inline D apply(std::complex<D> a) { 
      using std::abs;
      return abs(a); 
    }

    static std::string debugtxt(const std::string& sa) {
      std::string sout = "abs(" + sa + ")";
      return sout;
    }

  };


  // arg(a)

  template <class D> class ApArg {
  public:
    ApArg() { }

    static inline D apply(std::complex<D> a) { 
      using std::arg;
      return arg(a); 
    }

    static std::string debugtxt(const std::string& sa) {
      std::string sout = "arg(" + sa + ")";
      return sout;
    }

  };




  // conj(a)

  template <class D > class ApConj {
  public:
    ApConj() { }

    static inline std::complex<D> apply(std::complex<D> a) { 
      using std::conj;
      return conj(a); 
    }

    static std::string debugtxt(const std::string& sa) {
      std::string sout = "conj(" + sa + ")";
      return sout;
    }

  };


  // real(a)

  template <class D> class ApReal {
  public:
    ApReal() { }


    static inline const D apply(const std::complex<D> a) { 
      using std::real;
      return real(a); 
    }

    static std::string debugtxt(const std::string& sa) {
      std::string sout = "real(" + sa + ")";
      return sout;
    }

  };


  // imag(a)

  template <class D> class ApImag {
  public:
    ApImag() { }

    static inline D apply(std::complex<D> a) { 
      using std::imag;
      return imag(a); 
    }

    static std::string debugtxt(const std::string& sa) {
      std::string sout = "imag(" + sa + ")";
      return sout;
    }

  };






};

#endif

