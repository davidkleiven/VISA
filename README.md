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

To compile and link a application using this library add when linking
```bash
... -lsfml-graphics -lsfml-window -lsfml-system -larmadillo -lvisa
```
