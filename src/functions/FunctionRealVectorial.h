#pragma once#include "Function.h"

class FunctionRealVectorial {
public:
  virtual vectorN evaluate(real t) const = 0;

  virtual vectorN operator ()(real t) const {
    return this->evaluate(t);
  }

  virtual String toString() const = 0;

  virtual ~FunctionRealVectorial() {
  }
};
