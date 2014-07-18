![Xigua](http://i.imgur.com/TFpew7Z.png)
===

[![Build Status](https://travis-ci.org/LiquidHelium/Xigua.png?branch=master)](https://travis-ci.org/LiquidHelium/Xigua)


Xigua is a interpreted functional programming language that aims to be simple, extensible, flexible and easily integrated into other projects. Xigua is written in modern C++ and requires no other libraries or tools to run other than a C++11 compiler. This repo also contains a Sublime Text theme for the language.

Examples of Xigua code:
---

Hello World

    [println "Hello World!"]

Factorial

    [= fac [fn (1) [1]
               (n) [n * [fac [n - 1]]]]]

    [println [factorial 5]]

Macros

    [= =fn [macro (name args proc)
                  [= name [fn args proc]]]]

    [=fn add (a b) [+ a b]]

    [println [add 2 2]]

Lots more examples can be found in the repo under examples/

Compiling
---

Xigua has been tested on Windows 8.1 using Nuwen's MinGW distro and Visual Studio 2013 and on OS X 10.9 using the default compiler. It will probably work on all platforms with a C++11 platform but I can't confirm. The project currently uses CMake to generate makefiles, with the flag XIGUA_BUILD_SHELL (defaults to ON) to build the shell/interpreter/repl and the flag XIGUA_BUILD_TESTS (defaults to OFF) to build the unit tests. The CMake process is pretty generic, just use the CMake GUI if you don't know how to use it. The project uses googletest to test but it isn't required if you don't build the tests.

Using The Shell/Intepreter/REPL
---

If you compile the shell it should generate a xigua_shell executable, simply run it with no arguments and you'll get a Xigua REPL, if you pass it a relative file location it'll run that file.


Using In Your C++ Project
---
Xigua aims to be easy to use in other projects as an inteprated language, to use it you will need to link against libxigua.a and include the include/ folder. Xigua contains a simple header file that will include all Xigua headers for you. Simply add the below code to relevent files:

    #include "xigua/xigua.hpp"

Currently the API isn't documented but you can get a good idea of how it works by looking at src/shell/main.cpp

Documentation will be up shortly hopefully.


Licence
---

Xigua is very liberally licenced. Licence details can be found in in licence.txt
