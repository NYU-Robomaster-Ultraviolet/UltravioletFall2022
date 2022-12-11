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
    .kp = 600.0f,
    .ki = 0.0f,
    .kd = 500.0f,
    .maxICumulative = 10.0f,
    .maxOutput = 16000.0f,
    .tQDerivativeKalman = 1.0f,
    .tRDerivativeKalman = 1.0f,
    .tQProportionalKalman = 1.0f,
    .tRProportionalKalman = 1.0f,
    .errDeadzone = 0.0f,
    .errorDerivativeFloor = 0.0f,
};

static constexpr tap::algorithms::SmoothPidConfig PITCH_PID = {
    .kp = 1850.0f,
    .ki = 0.0f,
    .kd = 150.0f,
    .maxICumulative = 10.0f,
    .maxOutput = 16000.0f,
    .tQDerivativeKalman = 1.0f,
    .tRDerivativeKalman = 1.0f,
    .tQProportionalKalman = 1.0f,
    .tRProportionalKalman = 1.0f,
    .errDeadzone = 0.5f,
    .errorDerivativeFloor = 0.0f,
};
 //struct GIMBAL_SMOOTH_PID

struct GIMBAL_CONSTANTS{
//Gimbal PID output to motor speed error factor
static constexpr float MOTOR_SPEED_FACTOR = 200.0f;
//the value in which controller inputs are multiplied by for gimbal movement, basically sensitivity
static constexpr float YAW_SCALE = 0.5f;
static constexpr float PITCH_SCALE = 0.2f;
//Gimbal Starting angles
static constexpr float YAW_STARTING_ANGLE = 0.0f;
static constexpr float PITCH_STARTING_ANGLE = 1.57079632679489661923f; //pi / 2
//Pitch Angle Limits
static constexpr float PITCH_MIN_ANGLE = 0.0f; //starting position is initialized as 0
static constexpr float PITCH_MAX_ANGLE = 2.61799; //150 degrees
//gimbal yaw and pitch speed limits
static constexpr float MIN_YAW_SPEED = 300.0f;
static constexpr float MAX_YAW_SPEED = 8000.0f; 
static constexpr float MIN_PITCH_SPEED = 300.0f;
static constexpr float MAX_PITCH_SPEED = 20000.0f;
//Gimbal minimum angles of movement
static constexpr float YAW_MINIMUM_RADS = .005f;
static constexpr float PITCH_MINIMUM_RADS = .01f;
//minimum value for pitch RPM to be considered stable
static constexpr float MIN_PITCH_RPM = .0005f;
//starting pitch angle from when the robot is turned on 
static constexpr float  STARTING_PITCH = -M_1_PI / 6;

//values for gravity compensation
static constexpr float LEVEL_ANGLE = 1.5708; //90 degrees
static constexpr float BARREL_LENGTH = 165.0f; //turret barrel length in mm
static constexpr float BARREL_MIN_HEIGHT = 135.6f; 
static constexpr float BARREL_LEVEL_HEIGHT = 172.8f; 
static constexpr float GRAVITY_COMPENSATION_SCALAR = 5500;
};//struct GIMBAL_CONSTANTS
#endif