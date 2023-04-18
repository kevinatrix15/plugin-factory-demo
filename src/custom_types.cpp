#include <iostream>

#include "factory.h"
#include "registry.h"

#include "custom_types.h"

A::A(int val)
{
  foo = val;
  std::cout << "Hello from A! I got the value: " << foo << std::endl;
};

int A::getVar()
{
  return foo;
}

B::B(int val)
{
  bar = val;
  std::cout << "Hello from B! I got the value: " << bar << std::endl;
};

int B::getVar()
{
  return bar;
}

// Register our types into the custom types registry
REGISTER_TYPE(A);
REGISTER_TYPE(B);
