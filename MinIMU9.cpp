#include "vector.h"
#include "MinIMU9.h"
#include "exceptions.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <wordexp.h>

MinIMU9::MinIMU9(const char * i2cDeviceName) :
  imu(i2cDeviceName)
{
}

void MinIMU9::enable()
{
    imu.enable();
}

void MinIMU9::loadCalibration()
{
    /*wordexp_t expansion_result;
    wordexp("~/.minimu9-ahrs-cal", &expansion_result, 0);

    std::ifstream file(expansion_result.we_wordv[0]);
    if (file.fail())
    {
        throw posix_error("Failed to open calibration file ~/.minimu9-ahrs-cal.");
    }

    file >> mag_min(0) >> mag_max(0) >> mag_min(1) >> mag_max(1) >> mag_min(2) >> mag_max(2);
    if (file.fail() || file.bad())
    {
        throw std::runtime_error("Failed to parse calibration file ~/.minimu9-ahrs-cal.");
    }*/
    mag_min(0) = -291;
    mag_max(0) =  306;
    mag_min(1) = -261;
    mag_max(1) =  332;
    mag_min(2) = -262;
    mag_max(2) =  277;
}

void MinIMU9::measureOffsets()
{
    gyro_offset = vector::Zero();
    const int sampleCount = 32;
    for(int i = 0; i < sampleCount; i++)
    {
        imu.readGyro();
        gyro_offset += vector_from_ints(&imu.g);
        usleep(20*1000);
    }
    gyro_offset /= sampleCount;
}

vector MinIMU9::readMag()
{
    imu.readMag();
    IMU::raw_m = int_vector_from_ints(&imu.m);
    vector v;
    v(0) = (float)(imu.m[0] - mag_min(0)) / (mag_max(0) - mag_min(0)) * 2 - 1;
    v(1) = (float)(imu.m[1] - mag_min(1)) / (mag_max(1) - mag_min(1)) * 2 - 1;
    v(2) = (float)(imu.m[2] - mag_min(2)) / (mag_max(2) - mag_min(2)) * 2 - 1;
    return v;
}

vector MinIMU9::readAcc()
{
    const float accel_scale = 0.00390625;
    imu.readAcc();
    IMU::raw_a = int_vector_from_ints(&imu.a);
    return vector_from_ints(&imu.a) * accel_scale;
}

vector MinIMU9::readGyro()
{
    const float gyro_scale = 0.06957*3.14159265 / 180;
    imu.readGyro();
    IMU::raw_g = int_vector_from_ints(&imu.g);
    return ( vector_from_ints(&imu.g) - gyro_offset ) * gyro_scale;
}
