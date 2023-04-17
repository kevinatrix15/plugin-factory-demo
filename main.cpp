#include <iostream>

#include "factory.h"
#include "custom_types.h"
#include "registry.h"

int main()
{
  Factory factory;

  int the_custom_argument = 42;
  MyTypeRegistry::RegisterAll(factory, the_custom_argument);

#ifdef USE_A_TYPE
  // If we don't directly "use" something from lib_A, it will never be loaded
  A foo(1);
  std::cout << "A.var: " << foo.getVar() << std::endl;
#endif

  // Check the contents of the types registry
  MyTypeRegistry registry;
  auto registered_types = registry.GetRegisteredIds();
  std::cout << "Number of registered types: " << registered_types.size() << std::endl;

  for (auto& str : registered_types)
    std::cout << "  Type: '" << str << "'" << std::endl;

  // Try instantiating an "A" using the Factory
  std::shared_ptr<BaseClass> a_base = factory.instantiateType("A");
}
