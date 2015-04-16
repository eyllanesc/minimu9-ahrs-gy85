#ifndef _MINIMU9_H
#define _MINIMU9_H

#include "IMU.h"
#include "GY85.h"

class MinIMU9 : public IMU {
public:
    MinIMU9(const char * i2cDeviceName);

    GY85 imu;

    virtual vector readAcc();
    virtual vector readMag();
    virtual vector readGyro();

    virtual void enable();
    virtual void loadCalibration();
    virtual void measureOffsets();
};

#endif
