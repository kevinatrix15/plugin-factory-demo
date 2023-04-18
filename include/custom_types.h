#pragma once

#include "factory.h"

// Example custom classes deriving from the Factory's base class
// This library contains static variables whose constructors register
// these types with our types registry (which handles registration
// of all custom types with the Factory)

class A : public BaseClass
{
 public:
  A(int val);

  int getVar() override;

 protected:
  int foo{0};
};

class B : public BaseClass
{
 public:
  B(int val);

  int getVar() override;

 protected:
  int bar{0};
};
