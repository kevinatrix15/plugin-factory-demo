#include "lib_interface.h"

#include <memory>

class IAbstractLibFactory
{
 public:
  virtual ~IAbstractLibFactory() = default;

  virtual std::unique_ptr<ILib> make() = 0;
};
