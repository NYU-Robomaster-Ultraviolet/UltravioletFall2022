
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

    static constexpr float
    //M3505 motor speed PID 
    CHASSIS_MOTOR_KP = 15000.0f,
    CHASSIS_MOTOR_KI = 10.0f,
    CHASSIS_MOTOR_KD = 0.0f,
    CHASSIS_MOTOR_MAX_IOUT = 2000.0f, //max integral 
    CHASSIS_MOTOR_MAX_OUT = 16000.0f; //max output

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