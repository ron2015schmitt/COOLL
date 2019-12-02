#ifndef MATHQ__TEST_H
#define MATHQ__TEST_H 1



void printStart(const int n) {
  using namespace display;
  std::string s = "Test#" + num2string(n)+":";
  s = printf2str("%-10s",s.c_str());
  mout << createStyle(BLUE2+BOLD).apply(s);
}

template <class T>
void printEnd_(const bool pass, const T& result, const T& expected, const int linenum) {
  using namespace display;
  if (pass) {
    mout << "          " <<  "       = " << result <<std::endl;
    mout << "          ";
    mout << createStyle(GREEN1+BOLD).apply("Passed")  << std::endl;
  } else {
    FormatData<double>::format_string = "%.16g";
    mout << "          " <<  "       = " << result <<std::endl;
    mout << "        " << createStyle(BLUE2).apply("Expected");
    std::stringstream ss;
    ss << expected;
    mout << " = " <<  createStyle(BOLD).apply(ss.str()) << std::endl;
    mout << "          ";
    mout << createStyle(RED+BOLD).apply("FAILED") ;
    std::string s = createStyle(BOLD).apply(num2string(linenum));
    mout << createStyle(BLUE2).apply("  Refer to line#"+s ) << std::endl;
    FormatData<double>::format_string = "%g";
  }
  mout << std::endl;
  
}

#define printEnd(pass, result, expected) printEnd_(pass, result, expected,__LINE__)



void printCode(const std::string& str) {
  using namespace display;
  mout<<  createStyle(GRAY1).apply(str) << std::endl;
}

#define testcode(...)  printCode(stringify(__VA_ARGS__)); __VA_ARGS__

#define testtext(...)  printCode(stringify(__VA_ARGS__))


void printSummary(const std::string filename, const int testnum, const int failnum) {
  using namespace display;

  mout << StyledString::get(HORLINE);
  mout << createStyle(BLUE2+BOLD).apply("SUMMARY:");
  mout << "  " << createStyle(BOLD+MAGENTA1).apply(filename)  <<std::endl;
  
  std::string s = printf2str("%-4d",testnum);
  mout << "          "<< createStyle(BOLD).apply(s);
  mout << createStyle(BOLD).apply("TOTAL") << std::endl;
  
  s = printf2str("%-4d",(testnum-failnum));
  mout << "          "<< createStyle(GREEN1+BOLD).apply(s);
  mout << createStyle(GREEN1+BOLD).apply("PASSED") << std::endl;
  
  if (failnum > 0) {
    s = printf2str("%-4d",(failnum));
    mout << "          "<< createStyle(RED+BOLD).apply(s);
    mout << createStyle(RED+BOLD).apply("FAILED") << std::endl;
  }
  
  mout << StyledString::get(HORLINE);
  cr();
  
}


#endif
