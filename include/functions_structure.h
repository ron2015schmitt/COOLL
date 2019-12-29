#ifndef MATRICKS__FUNCTIONS_STRUCTURE_H
#define MATRICKS__FUNCTIONS_STRUCTURE_H 1


namespace mathq {


    
  // ************************************************************************
  // *              Transpose, Conjugate, Adjoint, and ~
  // ************************************************************************



  
  // transpose(A) 

  template <class X, class E, class D, int M, int R> 
  auto transpose(const TensorR<X,E,D,M,R>& x)
  {
    return TER_Transpose<TensorR<X,E,D,M,R>,E,D,M,R,FUNCTOR_pos<E,E,D,D>>(x);
  }

  // adjoint(A) - conjugate transpose - complex

  template <class X, class E, class D, int M, int R> 
  auto adjoint(const TensorR<X,E,std::complex<D>,M,R>& x)
  {
    return TER_Transpose<TensorR<X,E,std::complex<D>,M,R>,E,std::complex<D>,M,R,FUNCTOR_conj_complex<E,E,std::complex<D>,std::complex<D>>>(x);
  }

  

  // adjoint(A) - conjugate transpose - Imaginary

  template <class X, class E, class D, int M, int R> 
  auto adjoint(const TensorR<X,E,Imaginary<D>,M,R>& x)
  {
    return TER_Transpose<TensorR<X,E,Imaginary<D>,M,R>,E,Imaginary<D>,M,R,FUNCTOR_conj_imag<E,E,Imaginary<D>,Imaginary<D>>>(x);
  }



  
  // ~A conjugate transpose operator

  template <class X, class E, class D, int M, int R> 
  auto operator~(const TensorR<X,E,D,M,R>& x)
  {
    return adjoint(x);
  }










  // join

  template <class A, class B, class E, class D, int M, int R, typename = EnableIf<R==1> >
auto join(const TensorR<A,E,D,M,R>& x1, const TensorR<B,E,D,M,R>& x2) {
    return TER_Join<TensorR<A,E,D,M,R>, TensorR<B,E,D,M,R>, E,D,M>(x1,x2);
  }


  // operator,

  template <class A, class B, class E, class D, int M, int R, typename = EnableIf<R==1> >
  auto operator,(const TensorR<A,E,D,M,R>& x1, const TensorR<B,E,D,M,R>& x2) {
    return join(x1,x2);
  }
  


  // join - LHS

  template <class A, class B, class E, class D, int M, int R, typename = EnableIf<R==1> >
auto join(TensorRW<A,E,D,M,R>& x1, TensorRW<B,E,D,M,R>& x2) {
    return TERW_Join<TensorRW<A,E,D,M,R>, TensorRW<B,E,D,M,R>, E,D,M>(x1,x2);
  }





  // rep(v,m)

  template <class A, class D> 
   auto rep(const TensorR<A,D,D,1,1>& a, const size_type m) {
    return TER_Rep<TensorR<A,D,D,1,1>,D>(a,m);
  }

  




  

};

#endif 