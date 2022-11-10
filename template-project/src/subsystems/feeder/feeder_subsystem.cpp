#include "feeder_subsystem.hpp"

#include "tap/communication/serial/remote.hpp"
#include "tap/algorithms/math_user_utils.hpp"

using namespace tap;

namespace feeder
{

    void FeederSubsystem::initialize()
    {
        feederMotor.initialize();
    }
    void FeederSubsystem::refresh() {
        // updateRpmPid(&frontLeftPid, &frontLeftMotor, frontLeftDesiredRpm);
        // updateRpmPid(&frontRightPid, &frontRightMotor, frontRightDesiredRpm);
        // updateRpmPid(&backLeftPid, &backLeftMotor, backLeftDesiredRpm);
        // updateRpmPid(&backRightPid, &backRightMotor, backRightDesiredRpm);
        
        //should we be calling refresh for Feeder motor? not sure 
    }
    void FeederSubsystem::updateRpmPid(modm::Pid<float>* pid, tap::motor::DjiMotor* const motor, float desiredRpm) {
        pid->update(desiredRpm - motor->getShaftRPM());
        motor->setDesiredOutput(pid->getValue());
    }

    /*
        TODO:
        code review
        function is called when command calls execute
    */
    void FeederSubsystem::setOnState(float targetRPM) 
    {

        feederSpeedOutput = tap::algorithms::limitVal<float>(
            RPM_SCALE_FACTOR*targetRPM, -MAX_CURRENT_OUTPUT, MAX_CURRENT_OUTPUT
        );
    }
} //namespace feeder