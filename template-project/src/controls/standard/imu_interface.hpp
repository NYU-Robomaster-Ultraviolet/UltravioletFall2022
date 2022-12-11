#ifndef IMU_INTERFACE_HPP_
#define IMU_INTERFACE_HPP_
#include "drivers.hpp"
#include "modm/math/geometry/angle.hpp"
#include "controls/standard/standard_constants.hpp"

/* 
ImuRadInterfrace is a class that will return the values of imu readings in radians. It will also 
use displacement angles when measuring position relative to its starting position.
due to taproot, yaw = roll, roll = pitch, pitch = yaw
*/

class ImuRadInterface{
public:
    ImuRadInterface(tap::Drivers *drivers) : drivers(drivers) {}

    //getters for offset from angles from starting position from radians 
    float getYaw() const{return modm::toRadian(drivers->bmi088.getPitch()) - startingYaw;}
    float getPitch() const{return modm::toRadian(drivers->bmi088.getRoll()) - startingPitch;}
    float getRoll() const{return modm::toRadian(drivers->bmi088.getYaw()) - startingRoll;}

    //getters for velocities from gyro sensor, converted in rad/sec
    float getGyroX() const {return modm::toRadian(drivers->bmi088.getGx());}
    float getGyroY() const {return modm::toRadian(drivers->bmi088.getGy());}
    float getGyroZ() const {return modm::toRadian(drivers->bmi088.getGz());}

    //getters for angular velocities in rad/sec^2
    float getAX() const {return modm::toRadian(drivers->bmi088.getAx());}
    float getAY() const {return modm::toRadian(drivers->bmi088.getAy());}
    float getAZ() const {return modm::toRadian(drivers->bmi088.getAz());}

    bool ready() const {
        return tap::communication::sensors::imu::ImuInterface::ImuState::IMU_CALIBRATED == 
        drivers->bmi088.getImuState();}

private:
    tap::Drivers *drivers;
    GIMBAL_CONSTANTS constants;

    //starting positions of yaw and pitch gimbal angles in radians.
    float startingPitch = constants.STARTING_PITCH;
    float startingYaw = 0;
    float startingRoll = 0;

}; //class ImuInterface

#endif