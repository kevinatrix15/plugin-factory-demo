#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "factory.h"

class MyTypeRegistry
{
 public:
  struct Registration
  {
    const std::string type_id;
    std::function<void(Factory&, int)> doRegister;
    Registration(const std::string& ID) : type_id(ID){};
  };

  using RegMap = std::unordered_map<std::string, Registration>;

  //! Add a type registration to the registry
  static void AddRegistration(const Registration& func);

  //! Simulate emplacing all of our types into the factory
  static void RegisterAll(Factory& factory, int custom_arg);

  //! Return a vector of registration IDs of all types which have been registered
  std::vector<std::string> GetRegisteredIds() const;

 private:
  static RegMap map_;
};
