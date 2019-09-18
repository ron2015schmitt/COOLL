#define MATRICKS_DEBUG 1
#include "matricks.h"

#include <vector>

#if CPP11 == 1
#include <initializer_list>
#endif

#include <type_traits>
#include <string>

template <class, template <class> class>
struct is_instance : public std::false_type {};

template <class T, template <class> class U>
struct is_instance<U<T>, U> : public std::true_type {};

int main()
{
  using namespace matricks;
  using namespace display;

  const double pi = M_PI;
  int n = 45;
  unsigned int m = 256;
  double x = 3.14;
  double vals[] = {1.1,2.2,3.3};
  bool done = true;
  Vector<double> v = range<double>(1,10);
  char str[] = "hello";
  std::string s = "world";
  std::complex<double> z(1,-1);


  cr();cr();
  disp(n);
  disp(m);
  disp(x);
  disp(vals);
  disp(done);
  disp(v);
  disp(str);
  disp(s);
  disp(z);

  cr();cr();
  tdisp(n);
  tdisp(m);
  tdisp(x);
  tdisp(vals);
  tdisp(done);
  tdisp(v);
  tdisp(str);
  tdisp(s);
  tdisp(z);

  cr();cr();
  mdisp(n,m,x,vals,done,str,s,z);

  cr();cr();
  dispval(n);
  dispval(m);
  
  cr();cr();
  disp(n+3);
  disp(10*x-1);
  disp(!done);
  disp( round(10*sin(pi/10*v) + 10) );
  disp(s+" tour");
  mout << std::endl;

  mout << createStyle(GRAY1) << "  ";
  mout << createStyle(GRAY2) << "  ";
  mout << createStyle(WHITE+BLACKBACK) << "  ";
  mout << std::endl;
  
  mout << createStyle(RED) << "  ";
  mout << std::endl;
  mout << createStyle(ORANGE) << "  ";
  mout << std::endl;
  mout << createStyle(YELLOW) << "  ";
  mout << createStyle(YELLOWBRIGHT) << "  ";
  mout << std::endl;
  mout << createStyle(GREEN) << "  ";
  mout << createStyle(GREENBRIGHT) << "  ";
  mout << createStyle(GREEN1) << "  ";
  mout << std::endl;
  mout << createStyle(CYAN) << "  ";
  mout << createStyle(BLUE) << "  ";
  mout << createStyle(BLUEBRIGHT) << "  ";
  mout << createStyle(BLUE1) << "  ";
  mout << createStyle(BLUE2) << "  ";
  mout << createStyle(BLUE3) << "  ";
  mout << std::endl;
  mout << createStyle(MAGENTA) << "  ";
  mout << createStyle(MAGENTA1) << "  ";
  mout << createStyle(VIOLET1) << "  ";
  mout << std::endl;
  mout << createStyle(BOLD) << "  ";
  mout << createStyle(UNDERLINE) << "  ";
  mout << createStyle(CROSSEDOUT) << "  ";
  mout << createStyle(OVERLINE) << "  ";
  mout << createStyle(SLOWBLINK) << "  ";
  mout << std::endl;

  mout << createStyle(REDBACK) << "  ";
  mout << createStyle(ORANGEBACK) << "  ";
  mout << createStyle(YELLOWBACK) << "  ";
  mout << createStyle(GREENBACK) << "  ";
  mout << std::endl;
  mout << std::endl;
  mout << std::endl;

  mout << createStyle(BOLD+UNDERLINE+VIOLET1) << "  ";
  mout << std::endl;
  mout << std::endl;
  mout << std::endl;
  mout << std::endl;

  {
    Style mystyle = createStyle(BOLD+RED);
    mout << mystyle.apply("with style") + " without style " << std::endl;
  }
  mout << std::endl;
  mout << std::endl;
  mout << std::endl;

  {
    int nf = 27;  // color for foreground
    int nb = 227; // color for background 
    Style mystyle(nf, nb);
    mout << mystyle.apply("Hello World") << std::endl;

    mout << std::endl;
    mout << std::endl;
    mout << std::endl;


    Style bold(BOLD); 
    Style mybold = bold + mystyle; 
    mout << mybold.apply("Hello World") << std::endl;

    Style black(BLACK); 
    mout <<"XXX"<< black.apply("XXX")<<"XXX" << std::endl;
    
  }
  
  cr();cr();

  using namespace std;

  double d;

  mout << Fun_Plus_base::expression("x") << endl;

  mout << Fun_Plus<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Plus<double>::expression("x") << endl;
  
  mout << Fun_Minus<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Minus<double>::expression("x") << endl;

  mout << Fun_Cast<double,int>::classname() << " ";
  mout << Fun_Cast<double,int>::expression("n") << endl;
  
  mout << Fun_Add<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Add<double>::expression("x","y") << endl;

  mout << Fun_Subtract<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Subtract<double>::expression("x","y") << endl;
  mout << Fun_Multiply<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Multiply<double>::expression("x","y") << endl;

  mout << Fun_Divide<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Divide<double>::expression("x","y") << endl;


  mout << Fun_Pow<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Pow<double>::expression("x","y") << endl;

  mout << Fun_Monomial<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Monomial<double>::expression("x","n") << endl;

  mout << Fun_Atan2<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Atan2<double>::expression("x","y") << endl;

  mout << Fun_Sin<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Sin<double>::expression("x") << endl;

  mout << Fun_Cos<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Cos<double>::expression("x") << endl;

  mout << Fun_Tan<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Tan<double>::expression("x") << endl;

  mout << Fun_Sqrt<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Sqrt<double>::expression("x") << endl;

  mout << Fun_Sqr<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Sqr<double>::expression("x") << endl;

  mout << Fun_Cube<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Cube<double>::expression("x") << endl;

  mout << Fun_Exp<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Exp<double>::expression("x") << endl;

  mout << Fun_Abs<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Abs<double>::expression("x") << endl;

  mout << Fun_Sgn<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Sgn<double>::expression("x") << endl;

  mout << Fun_Log<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Log<double>::expression("x") << endl;

  mout << Fun_Log2<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Log2<double>::expression("x") << endl;

  mout << Fun_Log10<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Log10<double>::expression("x") << endl;

  mout << Fun_Asin<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Asin<double>::expression("x") << endl;

  mout << Fun_Acos<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Acos<double>::expression("x") << endl;

  mout << Fun_Atan<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Atan<double>::expression("x") << endl;

  mout << Fun_Ceil<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Ceil<double>::expression("x") << endl;

  mout << Fun_Round<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Round<double>::expression("x") << endl;

  mout << Fun_Sinh<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Sinh<double>::expression("x") << endl;

  mout << Fun_Cosh<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Cosh<double>::expression("x") << endl;

  mout << Fun_Tanh<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Tanh<double>::expression("x") << endl;

  mout << Fun_Roundzero<double>::classname() << getBracketedTypeName(d) << " ";
  mout << Fun_Roundzero<double>::expression("x","y") << endl;

  mout << is_instance<Fun_Multiply<double>, Fun_Divide>{} <<endl;
  
  
  return 0;
}