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

// A struct which registers a type into the registry when instantiated
template <typename T>
struct CustomTypeRegistrar
{
 public:
  CustomTypeRegistrar(std::string ID)
  {
    MyTypeRegistry::Registration entry(ID);

    // Implement the registration function for the type
    // We're assuming all of our custom types have a contructor that takes a single integer
    // The Factory expects no constructor arguments, hence the builder function
    entry.doRegister = [ID](Factory& factory, int custom_arg) {
      // The builder function (contructor wrapper)
      TypeBuilder builder = [custom_arg]() { return std::make_shared<T>(custom_arg); };

      // We have a custom contructor that we need to register
      factory.registerType(ID, builder);
    };

    MyTypeRegistry::AddRegistration(entry);
  }
};

// Static variables whose constructor registers a type with the registry library
static CustomTypeRegistrar<A> register_A("A");
static CustomTypeRegistrar<B> register_B("B");
