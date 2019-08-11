#ifndef MBOOLOPS_H
#define MBOOLOPS_H


namespace Matricks {





  /************************************************************
   *               Templates for Binary Operators that return bool matrixs
   *
   * D = data type, e.g. double
   * A = either an Matrix or a Mexpr
   * B = either an Matrix or a Mexpr
   ************************************************************
   */


  // a==b

  template <class D, class A, class B> 
  inline MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApEqual<D> >  
  operator==( const MorE<D,A>& a, const  MorE<D,B>& b ) {
    return MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApEqual<D> >(a,b);
  }


  // a!=b

  template <class D, class A, class B> 
  inline MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApNotEqual<D> >  
  operator!=( const MorE<D,A>& a, const  MorE<D,B>& b ) {
    return MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApNotEqual<D> >(a,b);
  }



  // a<=b

  template <class D, class A, class B> 
  inline MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApLessEqual<D> >  
  operator<=( const MorE<D,A>& a, const  MorE<D,B>& b ) {
    return MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApLessEqual<D> >(a,b);
  }


  // a>=b

  template <class D, class A, class B> 
  inline MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApGreaterEqual<D> >  
  operator>=( const MorE<D,A>& a, const  MorE<D,B>& b ) {
    return MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApGreaterEqual<D> >(a,b);
  }


  // a<b

  template <class D, class A, class B> 
  inline MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApLess<D> >  
  operator<( const MorE<D,A>& a, const  MorE<D,B>& b ) {
    return MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApLess<D> >(a,b);
  }


  // a>b

  template <class D, class A, class B> 
  inline MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApGreat<D> >  
  operator>( const MorE<D,A>& a, const  MorE<D,B>& b ) {
    return MboolBinOp<D,MorE<D,A>,MorE<D,B>,ApGreat<D> >(a,b);
  }


 /************************************************************
   *    Templates for matrix/scalar Operators that return Bool matrix
   *
   * D = data type, e.g. double (matrix and scalar must be of same data type)
   * A = either an Matrix or a Mexpr
   ************************************************************
   */



  // matrix == scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApEqual<D> > 
  operator==(const MorE<D,A>& a, const D b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApEqual<D> >(a,b);
  }

  // scalar == matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApEqual<D> > 
  operator==(const D a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApEqual<D> >(a,b);
  }

  // matrix != scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApNotEqual<D> > 
  operator!=(const MorE<D,A>& a, const D b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApNotEqual<D> >(a,b);
  }

  // scalar != matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApNotEqual<D> > 
  operator!=(const D a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApNotEqual<D> >(a,b);
  }
  // matrix <= scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApLessEqual<D> > 
  operator<=(const MorE<D,A>& a, const D b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApLessEqual<D> >(a,b);
  }

  // scalar <= matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApLessEqual<D> > 
  operator<=(const D a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApLessEqual<D> >(a,b);
  }
  // matrix >= scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApGreaterEqual<D> > 
  operator>=(const MorE<D,A>& a, const D b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApGreaterEqual<D> >(a,b);
  }

  // scalar >= matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApGreaterEqual<D> > 
  operator>=(const D a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApGreaterEqual<D> >(a,b);
  }
  // matrix < scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApLess<D> > 
  operator<(const MorE<D,A>& a, const D b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApLess<D> >(a,b);
  }

  // scalar < matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApLess<D> > 
  operator<(const D a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApLess<D> >(a,b);
  }
  // matrix > scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApGreat<D> > 
  operator>(const MorE<D,A>& a, const D b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApGreat<D> >(a,b);
  }

  // scalar > matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApGreat<D> > 
  operator>(const D a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApGreat<D> >(a,b);
  }



  // the following are defined for convenience

  // matrix == int scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApEqual<D> > 
  operator==(const MorE<D,A>& a, const int b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApEqual<D> >(a,static_cast<D>(b));
  }

  // int scalar == matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApEqual<D> > 
  operator==(const int a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApEqual<D> >(static_cast<D>(a),b);
  }

  // matrix != int scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApNotEqual<D> > 
  operator!=(const MorE<D,A>& a, const int b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApNotEqual<D> >(a,static_cast<D>(b));
  }

  // int scalar != matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApNotEqual<D> > 
  operator!=(const int a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApNotEqual<D> >(static_cast<D>(a),b);
  }
  // matrix <= int scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApLessEqual<D> > 
  operator<=(const MorE<D,A>& a, const int b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApLessEqual<D> >(a,static_cast<D>(b));
  }

  // int scalar <= matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApLessEqual<D> > 
  operator<=(const int a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApLessEqual<D> >(static_cast<D>(a),b);
  }
  // matrix >= int scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApGreaterEqual<D> > 
  operator>=(const MorE<D,A>& a, const int b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApGreaterEqual<D> >(a,static_cast<D>(b));
  }

  // int scalar >= matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApGreaterEqual<D> > 
  operator>=(const int a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApGreaterEqual<D> >(static_cast<D>(a),b);
  }
  // matrix < int scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApLess<D> > 
  operator<(const MorE<D,A>& a, const int b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApLess<D> >(a,static_cast<D>(b));
  }

  // int scalar < matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApLess<D> > 
  operator<(const int a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApLess<D> >(static_cast<D>(a),b);
  }
  // matrix > int scalar

  template <class D, class A> 
  inline BoolMatOpScal<D,MorE<D,A>,ApGreat<D> > 
  operator>(const MorE<D,A>& a, const int b)
  {
    return  BoolMatOpScal<D,MorE<D,A>,ApGreat<D> >(a,static_cast<D>(b));
  }

  // int scalar > matrix

  template <class D, class B> 
  inline BoolScalOpMat<D,MorE<D,B>,ApGreat<D> > 
  operator>(const int a, const MorE<D,B>& b)
  {
    return  BoolScalOpMat<D,MorE<D,B>,ApGreat<D> >(static_cast<D>(a),b);
  }




  /************************************************************
   *               Templates for Binary Operators
   *
   * A = either an Matrix or a Mexpr
   * B = either an Matrix or a Mexpr
   ************************************************************
   */

  // matrix && matrix

  template <class A, class B> 
  inline MBinOp<bool,MorE<bool,A>,MorE<bool,B>,ApAnd > 
  operator&&(const MorE<bool,A>& a, const MorE<bool,B>& b)
  {
    return  MBinOp<bool,MorE<bool,A>,MorE<bool,B>,ApAnd >(a,b);
  }

  // matrix || matrix

  template <class A, class B> 
  inline MBinOp<bool,MorE<bool,A>,MorE<bool,B>,ApOr > 
  operator||(const MorE<bool,A>& a, const MorE<bool,B>& b)
  {
    return  MBinOp<bool,MorE<bool,A>,MorE<bool,B>,ApOr >(a,b);
  }










  /************************************************************
   *               Templates for matrix/scalar Operators
   *
   * A = either an Matrix or a Mexpr
   ************************************************************
   */


  // matrix && scalar

  template <class A> 
  inline MatOpScal<bool,MorE<bool,A>,ApAnd > 
  operator&&(const MorE<bool,A>& a, const bool b)
  {
    return  MatOpScal<bool,MorE<bool,A>,ApAnd >(a,b);
  }

  // scalar && matrix

  template <class B> 
  inline ScalOpMat<bool,MorE<bool,B>,ApAnd > 
  operator&&(const bool a, const MorE<bool,B>& b)
  {
    return  ScalOpMat<bool,MorE<bool,B>,ApAnd >(a,b);
  }

  
  // matrix || scalar

  template <class A> 
  inline MatOpScal<bool,MorE<bool,A>,ApOr > 
  operator||(const MorE<bool,A>& a, const bool b)
  {
    return  MatOpScal<bool,MorE<bool,A>,ApOr >(a,b);
  }

  // scalar || matrix

  template <class B> 
  inline ScalOpMat<bool,MorE<bool,B>,ApOr > 
  operator||(const bool a, const MorE<bool,B>& b)
  {
    return  ScalOpMat<bool,MorE<bool,B>,ApOr >(a,b);
  }



  /****************************************************************
   *               Templates for Unary Operators & Unary Functions
   *
   * A = either an Matrix or a Mexpr
   *****************************************************************
   */


  
  // !(matrix)

  template <class A> 
  inline MFuncOp<bool,MorE<bool,A>,ApNot > 
  operator!(const MorE<bool,A>& a)
  {
    return  MFuncOp<bool,MorE<bool,A>,ApNot >(a);
  }
  




  










  /****************************************************************************
   * Unary Functions/Operators that return scalars
   ****************************************************************************
   */


  
  // alltrue(a)

  template <class A> 
  inline bool alltrue( const MorE<bool,A>& a ) {
    bool result = true;
    
#ifdef Matricks_CAREFUL
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"alltrue");
      return false;
    }
#endif
 
    for (register size_type i = 0; i< a.size(); i++)
      result = result && a(i);
    
    return result;
  }


  // alltruebyrow(a)

  template <class A> 
  inline LAvector<bool> alltruebyrow( const MorE<bool,A>& a ) {
    
    const size_type NR = a.Nrows();
    const size_type NC = a.Ncols();
#ifdef Matricks_CAREFUL
    std::string s = "alltruebyrow(" + a.debugtxt() + ")";
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"alltruebyrow");
      LAvector<bool> y(0,s);
      return y;
    }
    LAvector<bool> y(NR,s);
#else
    LAvector<bool> y(NR);
#endif

    size_type i = 0;
    for(size_type r = 0; r<NR; r++) {
      bool temp=true;
      for(size_type c = 0; c<NC; c++,i++) {
	temp = temp && a(i);
      }
      y[r] = temp;
    }
    return y;
  }

  // alltruebycol(a)
  template <class A> 
  inline LAvector<bool> alltruebycol( const MorE<bool,A>& a ) {
    
    const size_type NR = a.Nrows();
    const size_type NC = a.Ncols();
#ifdef Matricks_CAREFUL
    std::string s = "alltruebycol(" + a.debugtxt() + ")";
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"alltruebycol");
      LAvector<bool> y(0,s);
      return y;
    }
    LAvector<bool> y(NC,s);
#else
    LAvector<bool> y(NC);
#endif

    for(size_type c = 0; c<NC; c++) {
      size_type LIMIT = NR*NC-NC+c+1;
      bool temp=true;
      for(size_type i = c; i<LIMIT; i+=NC) {
	temp = temp && a(i);
      }
      y[c] = temp;
    }
    return y;
  }









   // anytrue(a)

  template <class A> 
  inline bool anytrue( const MorE<bool,A>& a ) {
    bool result = false;
    
#ifdef Matricks_CAREFUL
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"anytrue");
      return false;
    }
#endif
 
    for (register size_type i = 0; i< a.size(); i++)
      result = result || a(i);
    
    return result;
  }



  // anytruebyrow(a)

  template <class A> 
  inline LAvector<bool> anytruebyrow( const MorE<bool,A>& a ) {
    
    const size_type NR = a.Nrows();
    const size_type NC = a.Ncols();
#ifdef Matricks_CAREFUL
    std::string s = "anytruebyrow(" + a.debugtxt() + ")";
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"anytruebyrow");
      LAvector<bool> y(0,s);
      return y;
    }
    LAvector<bool> y(NR,s);
#else
    LAvector<bool> y(NR);
#endif

    size_type i = 0;
    for(size_type r = 0; r<NR; r++) {
      bool temp=false;
      for(size_type c = 0; c<NC; c++,i++) {
	temp = temp || a(i);
      }
      y[r] = temp;
    }
    return y;
  }

  // anytruebycol(a)
  template <class A> 
  inline LAvector<bool> anytruebycol( const MorE<bool,A>& a ) {
    
    const size_type NR = a.Nrows();
    const size_type NC = a.Ncols();
#ifdef Matricks_CAREFUL
    std::string s = "anytruebycol(" + a.debugtxt() + ")";
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"anytruebycol");
      LAvector<bool> y(0,s);
      return y;
    }
    LAvector<bool> y(NC,s);
#else
    LAvector<bool> y(NC);
#endif

    for(size_type c = 0; c<NC; c++) {
      size_type LIMIT = NR*NC-NC+c+1;
      bool temp=false;
      for(size_type i = c; i<LIMIT; i+=NC) {
	temp = temp || a(i);
      }
      y[c] = temp;
    }
    return y;
  }


  // numtrue(a)

  template <class A> 
  inline size_type numtrue( const MorE<bool,A>& a ) {
    size_type result = 0;
    
#ifdef Matricks_CAREFUL
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"numtrue");
      return 0;
    }
#endif
 
    for (register size_type i = 0; i< a.size(); i++)
      result += static_cast<size_type>(a(i));
    
    return result;
  }



  // numtruebyrow(a)

  template <class A> 
  inline LAvector< size_type> numtruebyrow( const MorE<bool,A>& a ) {
    
    const size_type NR = a.Nrows();
    const size_type NC = a.Ncols();
#ifdef Matricks_CAREFUL
    std::string s = "numtruebyrow(" + a.debugtxt() + ")";
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"numtruebyrow");
      LAvector< size_type> y(0,s);
      return y;
    }
    LAvector< size_type> y(NR,s);
#else
    LAvector< size_type> y(NR);
#endif

    size_type i = 0;
    for(size_type r = 0; r<NR; r++) {
       size_type temp=0;
      for(size_type c = 0; c<NC; c++,i++) {
	temp  += static_cast<size_type>(a(i));
      }
      y[r] = temp;
    }
    return y;
  }

  // numtruebycol(a)
  template <class A> 
  inline LAvector< size_type> numtruebycol( const MorE<bool,A>& a ) {
    
    const size_type NR = a.Nrows();
    const size_type NC = a.Ncols();
#ifdef Matricks_CAREFUL
    std::string s = "numtruebycol(" + a.debugtxt() + ")";
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"numtruebycol");
      LAvector< size_type> y(0,s);
      return y;
    }
    LAvector< size_type> y(NC,s);
#else
    LAvector< size_type> y(NC);
#endif

    for(size_type c = 0; c<NC; c++) {
      size_type LIMIT = NR*NC-NC+c+1;
      size_type temp=0;
      for(size_type i = c; i<LIMIT; i+=NC) {
	temp  += static_cast<size_type>(a(i));
      }
      y[c] = temp;
    }
    return y;
  }



  
  

  // findtrue(a)

  template <class A> 
  inline Matrix<size_type> findtrue( const MorE<bool,A>& a ) {
    size_type N = 0;
    
#ifdef Matricks_CAREFUL
    std::string s = "findtrue(" + a.debugtxt() + ")";
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"findtrue");
      Matrix<size_type> y(0,2,s);
      return y;
    }
#endif
 
    for (register size_type i = 0; i< a.size(); i++)
      N += static_cast<size_type>(a(i));
 
#ifdef Matricks_CAREFUL
    Matrix<size_type> y(N,2,s);
#else
    Matrix<size_type> y(N,2);
#endif

   size_type i = 0;
   size_type j = 0;
    for(size_type r = 0; r<a.Nrows(); r++) {
       for(size_type c = 0; c<a.Ncols(); c++,i++) {
	 if (a(i)) {
	   y(j,0) = r;
	   y(j,1) = c;
	   j++;
	 }
       }
    }
    return y;
  }





  // findtruesi(a) -- return in single index format

  template <class A> 
  inline LAvector<size_type> findtruesi( const MorE<bool,A>& a ) {
    size_type N = 0;
    
#ifdef Matricks_CAREFUL
    std::string s = "findtruesi(" + a.debugtxt() + ")";
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"findtruesi");
      LAvector<size_type> y(0,s);
      return y;
    }
#endif
 
    for (register size_type i = 0; i< a.size(); i++)
      N += static_cast<size_type>(a(i));
 
#ifdef Matricks_CAREFUL
    LAvector<size_type> y(N,s);
#else
    LAvector<size_type> y(N);
#endif

    size_type j = 0;
    for (register size_type i = 0; i< a.size(); i++) {
      if (a(i)) {
	y[j] = i;
	j++;
      }
    }
    
    return y;
  }

  

  // findtruebyrow(a)

  template <class A> 
  inline LAvector<size_type> findtruebyrow( const MorE<bool,A>& a ) {
    size_type N = 0;
    
#ifdef Matricks_CAREFUL
    std::string s = "findtruebyrow(" + a.debugtxt() + ")";
    if (  mexpr_is_size_bad(a.size()) ) {
      mbad_expr_in_unary(a,"findtruebyrow");
      LAvector<size_type> y(0,2,s);
      return y;
    }
#endif
 
    for (register size_type i = 0; i< a.size(); i++)
      N += static_cast<size_type>(a(i));
 
#ifdef Matricks_CAREFUL
    LAvector<size_type> y(N,2,s);
#else
    LAvector<size_type> y(N,2);
#endif

   size_type i = 0;
   size_type j = 0;
    for(size_type r = 0; r<a.Nrows(); r++) {
       for(size_type c = 0; c<a.Ncols(); c++,i++) {
	 if (a(i)) {
	   y[r] = 1;
	 }
       }
    }
    return y;
  }

  



};

#endif 
