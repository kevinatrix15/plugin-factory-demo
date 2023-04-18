# GNU Linker - Dynamic Lib Issue Minimal Example

Minimal example showing the dynamic library linking issue:

## Library B

```c++
// -------- B.h --------

class B
{
public:
  B() { }

  static void setFoo(int val);
  static int getFoo();

protected:
  static int foo_;
};

// -------- B.cpp --------

int B::foo_{1};

B::setFoo(int val)
{
  foo_ = val;
}

int B::getFoo()
{
  return foo_;
}
```

## A.cpp

```c++
// -------- A.h --------
struct A
{
  A();
};

// -------- A.cpp --------
#include "B.h"

A::A()
{
  B::setFoo(5);
}

static A an_A;
```

## main.cpp

```c++
#include "A.h"
#include "B.h"

int main()
{
  B::GetFoo(); // returns 1
}
```

## build.sh

```bash
g++ -fPIC -I. -shared A.cpp -o libA.so
g++ -fPIC -I. -shared B.cpp -o libB.so
g++ -fPIC -I. main.cpp -o main -lA -lB
./main
```
