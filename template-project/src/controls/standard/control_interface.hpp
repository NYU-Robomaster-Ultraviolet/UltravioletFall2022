#ifndef CONTROL_INTERFACE_HPP_
#define CONTROL_INTERFACE_HPP_

#include "tap/algorithms/linear_interpolation_predictor.hpp"
#include "tap/util_macros.hpp"

using namespace tap :: algorithms;

namespace tap{
    class Drivers;
}

namespace Control {

class ControlInterface{
    private:
        tap::Drivers *drivers;

        uint32_t prevUpdateCounterX = 0;
        uint32_t prevUpdateCounterY = 0;
        uint32_t prevUpdateCounterRotation = 0;

        LinearInterpolationPredictor chassisXInput;
        LinearInterpolationPredictor chassisYInput;
        LinearInterpolationPredictor chassisRotationInput;
    public:
        ControlInterface(tap::Drivers *driveers) : drivers(drivers) {}
        mockable float getChassisXInput();
        mockable float getChassisYInput();
        mockable float getChassisRotationInput();

        mockable float getGimbalYawInput();
        mockable float getGimbalPitchInput();
};


}

#endif  // CONTROL_INTERFACE_HPP_