#pragma once

#include "factory.h"

class A : public BaseClass
{
 public:
  A(int val);

  int getVar() override;

 protected:
  int var{0};
};
