#include <iostream>
#include <string>

class ILib
{
 public:
  virtual ~ILib() = default;

  /**
   * @brief Publish the processed value.
   */
  virtual void publishProcessedValue() const = 0;

  /**
   * @brief Callback to receive the raw value to be processed
   *
   * @param val The raw value.
   */
  virtual void receiveRawValue(const int val) = 0;
};
