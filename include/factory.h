#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

// The generic base type used by the Factory
class BaseClass
{
 public:
  BaseClass(){};

  virtual int getVar() = 0;
};

/**
 * Handy typedef for a function which returns a new BaseClass pointer
 * (Note that this could be constructing a derived type under the hood)
 */
typedef std::function<std::shared_ptr<BaseClass>()> TypeBuilder;

/**
 * A Factory capable of instantiating objects derived from our BaseClass
 * Any type placed in the Factory's registry can be constructed
 */
class Factory
{
 public:
  Factory(){};

  /**
   * Register a new type with the Factory
   * The registry entry consists of a unique ID and a builder function
   */
  void registerType(std::string ID, TypeBuilder builder)
  {
    type_registry_[ID] = builder;
  }

  //! Instantiate the type with the given ID
  std::shared_ptr<BaseClass> instantiateType(std::string ID);

 protected:
  //! A registry mapping IDs to "builders" (constructors)
  std::unordered_map<std::string, TypeBuilder> type_registry_;
};
