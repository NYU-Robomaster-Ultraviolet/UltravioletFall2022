#ifdef TARGET_STANDARD
#include "control_interface.hpp"

#include "tap/architecture/clock.hpp"
#include "tap/communication/serial/remote.hpp"
#include "tap/drivers.hpp"

using namespace tap::communication::serial;
/**
 * @brief Gets the current X input from the operator.
 * As the remote only returns user input every 17ms, analog input is interpolated to get a smoother usable value.
 *
 * @return float The current X input from the operator.
 */
namespace src::control{
    float ControlInterface::getChassisXInput() {
    uint32_t updateCounter = drivers->remote.getUpdateCounter();
    uint32_t currTime = tap::arch::clock::getTimeMilliseconds();
    //updates the value receive from controller
    if (prevUpdateCounterX != updateCounter) {
        chassisXInput.update(drivers->remote.getChannel(Remote::Channel::LEFT_HORIZONTAL), currTime);
        prevUpdateCounterX = updateCounter;
    }
    
    //limits value between -1 , 1
    float analogX = limitVal<float>(chassisXInput.getInterpolatedValue(currTime), -1.0f, 1.0f);

    return analogX;
    }
    /**
     * @brief Gets the current Y input from the operator.
     * As the remote only returns user input every 17ms, analog input is interpolated to get a smoother usable value.
     *
     * @return float The current Y input from the operator.
     */
    float ControlInterface::getChassisYInput() {
        uint32_t updateCounter = drivers->remote.getUpdateCounter();
        uint32_t currTime = tap::arch::clock::getTimeMilliseconds();
        //updates the value receive from controller
        if (prevUpdateCounterY != updateCounter) {
            chassisYInput.update(drivers->remote.getChannel(Remote::Channel::LEFT_VERTICAL), currTime);
            prevUpdateCounterY = updateCounter;
        }
        //limits value between -1 , 1
        float analogY = limitVal<float>(chassisYInput.getInterpolatedValue(currTime), -1.0f, 1.0f);

        return analogY;
    }
    /**
     * @brief Gets the current rotation input from the operator.
     * As the remote only returns user input every 17ms, analog input is interpolated to get a smoother usable value.
     *
     * @return float The current rotation input from the operator.
     */
    float ControlInterface::getChassisRotationInput() {
        uint32_t updateCounter = drivers->remote.getUpdateCounter();
        uint32_t currTime = tap::arch::clock::getTimeMilliseconds();
        //updates the value receive from controller
        if (prevUpdateCounterRotation != updateCounter) {
            chassisRotationInput.update(drivers->remote.getChannel(Remote::Channel::RIGHT_HORIZONTAL), currTime);
            prevUpdateCounterRotation = updateCounter;
        }

        //limits value between -1 , 1
        float analogRotation = limitVal<float>(chassisRotationInput.getInterpolatedValue(currTime), -1.0f, 1.0f);

        return analogRotation;
    }

    float ControlInterface::getGimbalYawInput() {

        return drivers->remote.getChannel(Remote::Channel::RIGHT_HORIZONTAL);
    }

    float ControlInterface::getGimbalPitchInput() {
        return drivers->remote.getChannel(Remote::Channel::RIGHT_VERTICAL);
    }
} //namespace control
#endif