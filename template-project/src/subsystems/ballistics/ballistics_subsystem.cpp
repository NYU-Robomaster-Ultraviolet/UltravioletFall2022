#include "ballistics_subsystem.hpp"
#include "modm/math/geometry/angle.hpp"


namespace ballistics{
void BallisticsSubsystem::initialize(){
    
}

void BallisticsSubsystem::refresh(){ 
    if(yawMotor.isMotorOnline()){
        uint16_t currentYawEncoder = yawMotor.getEncoderUnwrapped();
        currYaw = wrappedEncoderValueToRadians(currentYawEncoder);

    }
    if(pitchMotor.isMotorOnline()){
        uint16_t currentPitchEncoder = pitchMotor.getEncoderUnwrapped();
        currPitch = wrappedEncoderValueToRadians(currentPitchEncoder);

    }
}

inline float BallisticsSubsystem::wrappedEncoderValueToRadians(int64_t encoderValue) {
    return (M_TWOPI * static_cast<float>(encoderValue)) / tap::motor::DjiMotor::ENC_RESOLUTION;
}


void BallisticsSubsystem::calc_pitch_yaw(vector<vector<float>> target_info, vector<vector<float>> our1_info,float velocity,float barrel_len){
    float x = target_info[0][0] - our1_info[0][0];
    float y = target_info[0][1] - our1_info[0][1];
    float z = target_info[0][2] - our1_info[0][2];
    
    float vx = target_info[1][0] - our1_info[1][0];
    float vy = target_info[1][1] - our1_info[1][1];
    float vz = target_info[1][2] - our1_info[1][2];
    
    float ax = target_info[1][0] - our1_info[1][0];
    float ay = target_info[1][1] - our1_info[1][1];
    float az = target_info[1][2] - our1_info[1][2];
    
    vector<float> possible_ts;
    possible_ts.push_back(0.25*(ax*ax + ay*ay + az*az));
    possible_ts.push_back(vx*ax + vy*ay + vz*az);
    possible_ts.push_back(vx*vx + vy*vy + vz*vz + ax*x + ay*y + az*z - velocity*velocity);
    possible_ts.push_back(2*(-velocity*barrel_len + x*vx + y*vy + z*vz));

}
}//namespace ballistics