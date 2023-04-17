#include "factory.h"

std::shared_ptr<BaseClass> Factory::instantiateType(std::string ID)
{
  // Check that the ID has an entry
  if (!type_registry_.count(ID))
    throw std::runtime_error("Requested ID not in Factory type_registry_!");

  // Instantiate an instance of this type ID
  return type_registry_.at(ID)();
}
