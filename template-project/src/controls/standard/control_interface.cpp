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

    if (prevUpdateCounterX != updateCounter) {
        chassisXInput.update(drivers->remote.getChannel(Remote::Channel::LEFT_HORIZONTAL), currTime);
        prevUpdateCounterX = updateCounter;
    }

    float finalX = limitVal<float>(chassisXInput.getInterpolatedValue(currTime), -1.0f, 1.0f);

    return finalX;
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

        if (prevUpdateCounterY != updateCounter) {
            chassisYInput.update(drivers->remote.getChannel(Remote::Channel::LEFT_VERTICAL), currTime);
            prevUpdateCounterY = updateCounter;
        }

        float finalY = limitVal<float>(chassisYInput.getInterpolatedValue(currTime), -1.0f, 1.0f);

        return finalY;
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

        if (prevUpdateCounterRotation != updateCounter) {
            chassisRotationInput.update(drivers->remote.getChannel(Remote::Channel::RIGHT_HORIZONTAL), currTime);
            prevUpdateCounterRotation = updateCounter;
        }

        float finalRotation = limitVal<float>(chassisRotationInput.getInterpolatedValue(currTime), -1.0f, 1.0f);

        return finalRotation;
    }

    float ControlInterface::getGimbalYawInput() {
        return drivers->remote.getChannel(Remote::Channel::RIGHT_HORIZONTAL);
    }

    float ControlInterface::getGimbalPitchInput() {
        return drivers->remote.getChannel(Remote::Channel::RIGHT_VERTICAL);
    }
}