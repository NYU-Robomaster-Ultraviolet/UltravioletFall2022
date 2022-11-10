#ifndef STANDARD_CONSTANTS_HPP_
#define STANDARD_CONSTANTS_HPP_
/**
 * @brief Definitions for operator interface constants (may change based on preference of drivers)
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

struct GIMBAL_PID {
    //pitch speed close-loop PID params, max out and max iout
    static constexpr float 
    PITCH_SPEED_PID_KP = 2000.0f, 
    PITCH_SPEED_PID_KI = 60.0f, 
    PITCH_SPEED_PID_KD = 0.0f,
    PITCH_SPEED_PID_MAX_OUT = 15000.0f,
    PITCH_SPEED_PID_MAX_IOUT = 5000.0f,

    //yaw speed close-loop PID params, max out and max iout
    YAW_SPEED_PID_KP = 3600.0f,
    YAW_SPEED_PID_KI = 20.0f,
    YAW_SPEED_PID_KD = 0.0f,
    YAW_SPEED_PID_MAX_OUT = 30000.0f, 
    YAW_SPEED_PID_MAX_IOUT = 5000.0f, 

    //pitch gyro angle close-loop PID params, max out and max iout
    PITCH_GYRO_ABSOLUTE_PID_KP = 15.0f,	// JERRY: 15.0f
    PITCH_GYRO_ABSOLUTE_PID_KI = 0.0f,		//JERRY: 0.0f
    PITCH_GYRO_ABSOLUTE_PID_KD = 0.0f,		//JERRY: 0.0f

    PITCH_GYRO_ABSOLUTE_PID_MAX_OUT = 10.0f,
    PITCH_GYRO_ABSOLUTE_PID_MAX_IOUT = 0.0f,

    //yaw gyro angle close-loop PID params, max out and max iout
    YAW_GYRO_ABSOLUTE_PID_KP = 15.0f,	// JERRY'code, chewy's pan 26.0f
    YAW_GYRO_ABSOLUTE_PID_KI = 0.0f,	// JERRY'code, chewy's pan 0.0f
    YAW_GYRO_ABSOLUTE_PID_KD = 0.0f,// JERRY'code, chewy's pan 0.3f
    YAW_GYRO_ABSOLUTE_PID_MAX_OUT = 10.0f,  // Jerry 10.0f
    YAW_GYRO_ABSOLUTE_PID_MAX_IOUT = 0.0f;  //Jerry 0.0f
}; //struct GIMBAL_PID
//Gimbal PID output to motor speed error factor
static constexpr float MOTOR_SPEED_FACTOR = 100.0f;
//the value in which controller inputs are multiplied by for gimbal movement, basically sensitivity
static constexpr float YAW_GIMBAL_SCALE = 50.0f;
static constexpr float PITCH_GIMBAL_SCALE = 50.0f;
//Gimbal Starting angles
static constexpr float YAW_STARTING_ANGLE = 1.57079632679489661923f; //pi / 2
static constexpr float PITCH_STARTING_ANGLE = 1.57079632679489661923f; //pi / 2

struct FEEDER_PID
{
    static constexpr float
    PID_KP = 800.0f,
    PID_KI = 0.5f,
    PID_KD = 0.0f,
    PID_MAX_OUT = 10000.0f,
    PID_MAX_IOUT = 9000.0f;
};  // struct FEEDER_PID


#endif