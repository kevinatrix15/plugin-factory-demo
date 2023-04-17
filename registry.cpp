#include "registry.h"

MyTypeRegistry::RegMap MyTypeRegistry::map_{};

void MyTypeRegistry::AddRegistration(const Registration& func)
{
  map_.try_emplace(func.type_id, func);
}

void MyTypeRegistry::RegisterAll(Factory& factory, int custom_arg)
{
  for (auto& [id, reg_function] : map_)
    reg_function.doRegister(factory, custom_arg);
}

std::vector<std::string> MyTypeRegistry::GetRegisteredIds() const
{
  std::vector<std::string> registered_ids;
  registered_ids.reserve(map_.size());
  for (const auto& [name, reg_function] : map_)
    registered_ids.push_back(reg_function.type_id);

  return registered_ids;
}
