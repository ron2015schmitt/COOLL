#!/usr/bin/python

import os
from string import Template

myname = os.path.basename(__file__)
fn_op_functor = "fun_binary_op_functor.hpp"
fn_functor = "fun_binary_functor.hpp"
fn_functions = "fun_binary_functions.hpp"
fn_output = "fun_binary_AUTO.h"
namespace = "mathq"

ops = ["+", "-", "*", "/", "==", "!=", ">", ">=", "<", "<=", "&&", "||"]
opnames = ["add", "subtract", "multiply", "divide","equals","notequals","greater","greatereq","less","lesseq","and","or"]
opcomments = ["Addition", "Subtraction", "Multiplication", "Division","Equal to","Not equal to","Greater than","Greater than or equal to", "Less than","Less than or equal to", "And", "Or"]
optypeclasses = ["AddType", "SubType", "MultType", "DivType", "RelType", "RelType", "RelType", "RelType", "RelType", "RelType","AndType","OrType"]


funcs = ["std::atan2", "std::pow", "std::beta", "std::legendre",  "std::laguerre", "std::hermite", "std::sph_bessel", "std::sph_neumann", "std::cyl_bessel_i", "std::cyl_bessel_j", "std::cyl_bessel_k", "std::cyl_neumann", "std::ellint_1", "std::ellint_2" ]
funcnames = ["atan2", "pow", "beta", "legendre", "laguerre", "hermite", "sph_bessel", "sph_neumann", "cyl_bessel_i", "cyl_bessel_j", "cyl_bessel_k", "cyl_neumann", "ellint_1", "ellint_2"]
functypeclasses = ["MultType", "MultType", "MultType", "MultType", "MultType", "MultType", "MultType", "MultType", "MultType", "MultType", "MultType", "MultType", "MultType", "MultType"]





contents = "";

# -----------------------------------------------------
# functors
# -----------------------------------------------------
contents += """


//********************************************************************
//--------------------------------------------------------------------
//                        Functors
//--------------------------------------------------------------------
//********************************************************************


"""
with open(fn_op_functor, 'r') as file_functor:
    contents0 = file_functor.read();

contents0 = contents0.replace("##MYFILENAME##",fn_op_functor);
contents0 = contents0.replace("##SCRIPTNAME##",myname);

count = 0;
for op in ops:
    opname = opnames[count]
    fun = contents0
    fun = fun.replace("##OP##",op);
    fun = fun.replace("##NAME##",opname);
    contents += fun
    count += 1


with open(fn_functor, 'r') as file_functor:
    contents0 = file_functor.read();

contents0 = contents0.replace("##MYFILENAME##",fn_functor);
contents0 = contents0.replace("##SCRIPTNAME##",myname);
    
count = 0;
for func in funcs:
    fun = contents0
    fun = fun.replace("##FUNCTION##",func);
    fun = fun.replace("##NAME##",funcnames[count]);
    contents += fun
    count += 1

    

# -----------------------------------------------------
# functions
# -----------------------------------------------------
contents += """


//********************************************************************
//--------------------------------------------------------------------
//                           Functions
//--------------------------------------------------------------------
//********************************************************************


"""
with open(fn_functions, 'r') as file_functions:
    contents0 = file_functions.read();

contents0 = contents0.replace("##MYFILENAME##",fn_functor);
contents0 = contents0.replace("##SCRIPTNAME##",myname);

count = 0;
for op in ops:
    fun = contents0
    fun = fun.replace("##OP##",op);
    fun = fun.replace("##FUNCTION##","operator"+op);
    fun = fun.replace("##NAME##",opnames[count]);
    fun = fun.replace("##COMMENTNAME##",opcomments[count]);
    fun = fun.replace("##TYPECLASS##",optypeclasses[count]);
    contents += fun
    count += 1

count = 0;
for func in funcs:
    fun = contents0
    fun = fun.replace("##OP##",funcnames[count]);
    fun = fun.replace("##FUNCTION##",funcnames[count]);
    fun = fun.replace("##NAME##",funcnames[count]);
    fun = fun.replace("##COMMENTNAME##",funcnames[count]);
    fun = fun.replace("##TYPECLASS##",functypeclasses[count]);
    contents += fun
    count += 1


    
# -----------------------------------------------------
# write to file
# -----------------------------------------------------


fn_output_str=fn_output.upper().split(".")[0]

NAMESPACE = namespace.upper()
defvar = NAMESPACE+"__"+fn_output_str+"_H"

prologue = """#ifndef """+defvar+"""
#define """+defvar+""" 1

// THIS FILE WAS *AUTO-GENERATED* BY PYTHON SCRIPT '"""+myname+"""'

namespace """+namespace+""" { 
"""


epilogue = """}; // namespace mathq 
#endif // """+defvar



contents = prologue + contents + epilogue

print(contents)
with open(fn_output, 'w') as file_output:
    file_output.write(contents);