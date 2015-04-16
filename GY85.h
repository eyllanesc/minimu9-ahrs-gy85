#ifndef GY85_h
#define GY85_h

#include <stdint.h>
#include "I2CBus.h"

// hmc5883l's address
#define hmc5883l_ADDRESS            0x1E
// hmc5883l's register addresses
#define hmc5883l_Config_RegA         0x00
#define	hmc5883l_Config_RegB         0x01
#define	hmc5883l_Mode_Reg            0x02
#define	hmc5883l_AxisXDataReg_MSB    0x03
#define	hmc5883l_AxisXDataReg_LSB    0x04
#define	hmc5883l_AxisZDataReg_MSB    0x05
#define	hmc5883l_AxisZDataReg_LSB    0x06
#define	hmc5883l_AxisYDataReg_MSB    0x07
#define	hmc5883l_AxisYData_RegLSB    0x08
#define	hmc5883l_Status_Reg          0x09
#define	hmc5883l_Ident_RegA          0x10
#define	hmc5883l_Ident_RegB          0x11
#define	hmc5883l_Ident_RegC          0x12

// adxl345's address
#define adxl345_ADDRESS             0x53
// adxl345's register addresses
#define adxl345_reg_ThreshTap       0x1D
#define adxl345_reg_OFSX            0x1E
#define adxl345_reg_OFSY            0x1F
#define adxl345_reg_OFSZ            0x20
#define adxl345_reg_Dur             0x21
#define adxl345_reg_Latent          0x22
#define adxl345_reg_Window          0x23
#define adxl345_reg_ThreshAct       0x24
#define adxl345_reg_ThreshInact     0x25
#define adxl345_reg_TimeInact       0x26
#define adxl345_reg_ActInactCtl     0x27
#define adxl345_reg_ThreshFF        0x28
#define adxl345_reg_TimeFF          0x29
#define adxl345_reg_TapAxes         0x2A
#define adxl345_reg_ACTTapStatus    0x2B
#define adxl345_reg_BwRate          0x2C
#define adxl345_reg_PowerCtl        0x2D
#define adxl345_reg_IntEnable       0x2E
#define adxl345_reg_IntMap          0x2F
#define adxl345_reg_IntSource       0x30
#define adxl345_reg_DataFormat      0x31
#define adxl345_reg_DataX0          0x32
#define adxl345_reg_DataX1          0x33
#define adxl345_reg_DataY0          0x34
#define adxl345_reg_DataY1          0x35
#define adxl345_reg_DataZ0          0x36
#define adxl345_reg_DataZ1          0x37
#define adxl345_reg_FIFOCtl         0x38
#define adxl345_reg_FIFOStatus      0x39

// itg3205's address
#define itg3205_ADDRESS             0x68
// itg_3205's register addresses
#define itg_3205_reg_WhoAmI         0x00
#define itg_3205_reg_SmplRtDiv      0x15
#define itg_3205_reg_DLPFFS         0x16
#define itg_3205_reg_IntCfg         0x17
#define itg_3205_reg_IntStatus      0x1A
#define itg_3205_reg_TempOutH       0x1B
#define itg_3205_reg_TempOutL       0x1C
#define itg_3205_reg_GyroXOutH      0x1D
#define itg_3205_reg_GyroXOutL      0x1E
#define itg_3205_reg_GyroYOutH      0x1F
#define itg_3205_reg_GyroYOutL      0x20
#define itg_3205_reg_GyroZOutH      0x21
#define itg_3205_reg_GyroZOutL      0x22
#define itg_3205_reg_PwrMgm         0x3E

class GY85
{
 public:

    int m[3];  // magnetometer readings
    int a[3];  // accelerometer readings
    int g[3];  // gyroscope readings

    GY85(const char * i2cDeviceName);

    void enable(void);

    void writeMagReg(uint8_t reg, uint8_t value);
    uint8_t readMagReg(uint8_t reg);
    void writeAccReg(uint8_t reg, uint8_t value);
    uint8_t readAccReg(uint8_t reg);
    void writeGyroReg(uint8_t reg, uint8_t value);
    uint8_t readGyroReg(uint8_t reg);

    void readMag(void);
    void readAcc(void);
    void readGyro(void);

    void read(void);

private:
    I2CBus i2c_hmc5883l, i2c_adxl345, i2c_itg3205;
};

#endif
