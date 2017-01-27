# VISA

VISA (VISualize Array) is a tool for visualizing armadillo arrays using the
SFML library.

# Dependencies
This library depends on:
  * Simple and Fast Multimedia Library [SFML](http://www.sfml-dev.org/)
  * [Armadillo](http://arma.sourceforge.net/)

The unittests depends in addition on
  * [Google Test](https://github.com/google/googletest)
  * Pthreads

To compile and link an application using this library add when linking
```bash
... -lsfml-graphics -lsfml-window -lsfml-system -larmadillo -lvisa
```

# Installation
Run
```bash
cmake .
```
The default path is */usr/local*.
The libvisa.so will then be placed in */usr/local/lib* and
the header files will be placed in */usr/local/include/visa*.

Compile the library
```bash
make
```

Finally run
```bash
make install
```

Note that the *ARMA_NO_DEBUG* is set which means that the library will no perform bounds checking.

# Examples
Some examples of how to use the library can be found in the *Examples* folder.
