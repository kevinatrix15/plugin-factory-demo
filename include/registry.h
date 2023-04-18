#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "factory.h"

// A registry for all custom / derived types from other libraries
// Handles (semi-)automatic registration (into a Factory) of all types
// registered into it
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

// Simplifies registration of custom types by replacing all of the boilerplate with a single macro
#define REGISTER_TYPE(TypeName) static CustomTypeRegistrar<TypeName> TypeName##_registration(#TypeName)
