#ifndef STANDARD_CONSTANTS_HPP_
#define STANDARD_CONSTANTS_HPP_

#include "tap/algorithms/smooth_pid.hpp"
#include "modm/math/geometry/angle.hpp"

/**
 * @brief constants used for configeration of classes when building standard robot
 *
 */


static constexpr short int USER_MOUSE_YAW_MAX = 1000;
static constexpr short int USER_MOUSE_PITCH_MAX = 1000;
static constexpr float USER_MOUSE_YAW_SCALAR = (1.0f / USER_MOUSE_YAW_MAX);
static constexpr float USER_MOUSE_PITCH_SCALAR = (1.0f / USER_MOUSE_PITCH_MAX);

static constexpr float USER_JOYSTICK_YAW_SCALAR = 0.3f;
static constexpr float USER_JOYSTICK_PITCH_SCALAR = 0.15f;

static constexpr float CHASSIS_MOTOR_DISTANCE = 0.2f;
static constexpr float CHASSIS_ROTATION_SET_SCALE = 0.1f;

static constexpr float WHEELBASE_LENGTH = 0.366f;

static constexpr float
//M3505 motor speed PID 
CHASSIS_MOTOR_KP = 20.0f,
CHASSIS_MOTOR_KI = 0.2f,
CHASSIS_MOTOR_KD = 0.0f,
CHASSIS_MOTOR_MAX_IOUT = 2000.0f, //max integral 
CHASSIS_MOTOR_MAX_OUT = 16000.0f; //max output
 //CHASSIS PID VALUES

static constexpr tap::algorithms::SmoothPidConfig YAW_PID = {
    .kp = 229'183.1f,
    .ki = 0.0f,
    .kd = 10'886.2f,
    .maxICumulative = 0.0f,
    .maxOutput = 32'000.0f,
    .tQDerivativeKalman = 1.0f,
    .tRDerivativeKalman = 30.0f,
    .tQProportionalKalman = 1.0f,
    .tRProportionalKalman = 0.0f,
    .errDeadzone = 0.0f,
    .errorDerivativeFloor = 0.0f,
};

static constexpr tap::algorithms::SmoothPidConfig PITCH_PID = {
    .kp = 229'183.1f,
    .ki = 0.0f,
    .kd = 7'448.5f,
    .maxICumulative = 0.0f,
    .maxOutput = 32000.0f,
    .tQDerivativeKalman = 1.0f,
    .tRDerivativeKalman = 10.0f,
    .tQProportionalKalman = 1.0f,
    .tRProportionalKalman = 2.0f,
    .errDeadzone = 0.0f,
    .errorDerivativeFloor = 0.0f,
};
 //struct GIMBAL_SMOOTH_PID

struct GIMBAL_CONSTANTS{
//Gimbal PID output to motor speed error factor
static constexpr float MOTOR_SPEED_FACTOR = 8000.0f;
//the value in which controller inputs are multiplied by for gimbal movement, basically sensitivity
static constexpr float YAW_SCALE = 0.02f;
static constexpr float PITCH_SCALE = 0.02f;
//Gimbal Starting angles
static constexpr float YAW_STARTING_ANGLE = 0.0f;
static constexpr float PITCH_STARTING_ANGLE = 1.57079632679489661923f; //pi / 2
//Pitch Angle Limits
static constexpr float PITCH_MIN_ANGLE = 0.0f; //starting position is initialized as 0
static constexpr float PITCH_MAX_ANGLE = 0.785398f; //45 degrees
//gimbal yaw and pitch speed limits
static constexpr float MIN_YAW_SPEED = -8000.0f;
static constexpr float MAX_YAW_SPEED = 8000.0f; 
static constexpr float MIN_PITCH_SPEED = -8000.0f;
static constexpr float MAX_PITCH_SPEED = 8000.0f;
//Gimbal minimum angles of movement
static constexpr float YAW_MINIMUM_RADS = .005f;
static constexpr float PITCH_MINIMUM_RADS = .005f;
//minimum value for pitch RPM to be considered stable
static constexpr float MIN_PITCH_RPM = .0005f;
//starting pitch angle from when the robot is turned on 
static constexpr float  STARTING_PITCH = -M_1_PI / 2;

//values for gravity compensation
static constexpr float TURRET_CG_X = 30.17;
static constexpr float TURRET_CG_Z = 34.02;
static constexpr float GRAVITY_COMPENSATION_SCALAR = 7000;
};//struct GIMBAL_CONSTANTS
#endif