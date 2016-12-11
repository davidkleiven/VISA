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
Run the configure script
```bash
bash configure.sh --prefix=/install/path
```
The default path is */usr/local*.
The libvisa.so will then be placed in */usr/local/lib* and
the header files will be placed in */usr/local/include/visa*.

Compile the library
```bash
make lib
```

Finally run
```bash
make install
```

# Examples
Some examples of how to use the library can be found in the *Examples* folder.
