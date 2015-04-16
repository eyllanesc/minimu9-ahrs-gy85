#include "GY85.h"

GY85::GY85(const char * i2cDeviceName) :
    i2c_hmc5883l(i2cDeviceName), i2c_adxl345(i2cDeviceName), i2c_itg3205(i2cDeviceName)
{
    I2CBus i2c(i2cDeviceName);
    i2c_hmc5883l.addressSet(hmc5883l_ADDRESS);
    i2c_adxl345.addressSet(adxl345_ADDRESS);
    i2c_itg3205.addressSet(itg3205_ADDRESS);
}
//Read
uint8_t GY85::readMagReg(uint8_t reg)
{
    return i2c_hmc5883l.readByte(reg);
}

uint8_t GY85::readAccReg(uint8_t reg)
{
    return i2c_adxl345.readByte(reg);
}

uint8_t GY85::readGyroReg(uint8_t reg)
{
    return i2c_itg3205.readByte(reg);
}
//Write
void GY85::writeMagReg(uint8_t reg, uint8_t value)
{
    i2c_hmc5883l.writeByte(reg, value);
}

void GY85::writeAccReg(uint8_t reg, uint8_t value)
{
    i2c_adxl345.writeByte(reg, value);
}

void GY85::writeGyroReg(uint8_t reg, uint8_t value)
{
    i2c_itg3205.writeByte(reg, value);
}

// Turns on the GY_85's magnetometers,accelerometer and gyroscopes and places them in normal
// mode.
void GY85::enable(void)
{
//init hmc5883l
    writeMagReg(hmc5883l_Mode_Reg, 0x00);
    writeMagReg(hmc5883l_Config_RegA, 0x18);
//init adxl345
    writeAccReg(adxl345_reg_PowerCtl, 0x08);
    writeAccReg(adxl345_reg_DataFormat, 0x08);
    writeAccReg(adxl345_reg_BwRate, 0x09);
//init itg_3205
    writeGyroReg(itg_3205_reg_PwrMgm, 0x00);
    writeGyroReg(itg_3205_reg_SmplRtDiv, 0x07);
    writeGyroReg(itg_3205_reg_DLPFFS, 0x1E);
    writeGyroReg(itg_3205_reg_IntCfg, 0x00);
}

void GY85::readMag(void)
{
    uint8_t block[6];
    i2c_hmc5883l.readBlock(0x80 | hmc5883l_AxisXDataReg_MSB, sizeof(block), block);
    m[0] = (int16_t)(block[0] << 8 | block[1]);
    m[2] = (int16_t)(block[2] << 8 | block[3]);
	m[1] = (int16_t)(block[4] << 8 | block[5]);
}

void GY85::readAcc(void)
{
    uint8_t block[6];
    i2c_adxl345.readBlock(0x80 | adxl345_reg_DataX0, sizeof(block), block);
    a[0] = (int16_t)(block[1] << 8 | block[0]);
    a[1] = (int16_t)(block[3] << 8 | block[2]);
    a[2] = (int16_t)(block[5] << 8 | block[4]);

}

void GY85::readGyro(void)
{
    uint8_t block[6];
    i2c_itg3205.readBlock(0x80 | itg_3205_reg_GyroXOutH, sizeof(block), block);
    g[0] = (int16_t)(block[0] << 8 | block[1]);
    g[1] = (int16_t)(block[2] << 8 | block[3]);
    g[2] = (int16_t)(block[4] << 8 | block[5]);
}

void GY85::read(void)
{
    readMag();
    readAcc();
    readGyro();
}
