#include "lib_interface.h"

class SquareLib : public ILib
{
 public:
  /**
   * @brief Publish the processed value.
   */
  void publishProcessedValue() const override
  {
    // TODO: publish curr_val_ (requires a shim / external interface defined)
  }

  /**
   * @brief Callback to receive the raw value to be processed
   *
   * @param val The raw value.
   */
  void receiveRawValue(const int val) override
  {
    curr_val_ = val * val;
  }

 private:
  int curr_val_{0};
};

