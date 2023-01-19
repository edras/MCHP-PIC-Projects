#include "mcc_generated_files/system/system.h"

#define IMU_6_DOF_ADDRESS 0b1101000 //NOTE: The LSB is hardwired to 1 on the 6DOF Clickboard

/* Some 6 DOF IMU Click board register addresses */
    
#define       ORIENT_G           0x0B
#define       INT1_CTRL          0x0D
#define       INT2_CTRL          0x0E
#define       WHO_AM_I           0x0F
#define       CTRL1_XL           0x10
#define       CTRL2_G            0x11
#define       CTRL3_C            0x12
#define       CTRL4_C            0x13
#define       CTRL5_C            0x14
#define       CTRL6_C            0x15
#define       CTRL7_G            0x16
#define       CTRL8_XL           0x17
#define       CTRL9_XL           0x18
#define       CTRL10_C           0x19

#define       STATUS_REG         0x1E
#define       OUT_TEMP_L         0x20
#define       OUT_TEMP_H         0x21
#define       OUTX_L_G           0x22
#define       OUTX_H_G           0x23
#define       OUTY_L_G           0x24
#define       OUTY_H_G           0x25
#define       OUTZ_L_G           0x26
#define       OUTZ_H_G           0x27
#define       OUTX_L_XL          0x28
#define       OUTX_H_XL          0x29
#define       OUTY_L_XL          0x2A
#define       OUTY_H_XL          0x2B
#define       OUTZ_L_XL          0x2C
#define       OUTZ_H_XL          0x2D

/*Accel @ 416 Hz sampe rate and default +-2g range and default filter value.*/
#define CTRL1_XL_INIT_VALUE_1     0b01100000 

/*Accel @ 416 Hz sampe rate and +- 4g range and default filter value.*/
#define CTRL1_XL_INIT_VALUE_2     0b01101000 

/*Accel @ 416 Hz sampe rate and +- 4g range and 100 Hz anti-aliasing filter value.*/
#define CTRL1_XL_INIT_VALUE_3     0b01101010 

/*Accel @ 416 Hz sampe rate and +- 4g range and 50 Hz anti-aliasing filter value.*/
#define CTRL1_XL_INIT_VALUE_4     0b01101011 

/*Accel @ 416 Hz sampe rate and +- 8g range and 50 Hz anti-aliasing filter value.*/
#define CTRL1_XL_INIT_VALUE_5     0b01101111 

/* Enable accelerometer filter values set in CTRL1_XL */
#define CTRL4_C_INIT_VALUE    0b10000000 

/*Gyro @ 416 sample rate and 500 dps range*/
#define CTRL2_G_INIT_VALUE_1      0b01100100

/*Gyro @ 416 sample rate and default 1000 dps range*/
#define CTRL2_G_INIT_VALUE_2      0b01101000

/*Gyro @ 416 sample rate and default 2000 dps range*/
#define CTRL2_G_INIT_VALUE_3      0b01101100

/* Configure orientation to be according to silkscreen */
#define ORIENT_G_INIT_VALUE     0b00000001

/* Write [count] number of bytes from [buffer] to register [command] on i2c slave */
void IMU_Write( uint8_t *command, uint8_t *buffer, uint16_t count );

/* Read [count] number of bytes from [buffer] to register [command] on i2c slave */
void IMU_Read( uint8_t *command, uint8_t *buffer, uint16_t count );

uint8_t i2c_read1ByteRegister(uint16_t device_address, uint8_t register_add)
{
    uint8_t returnValue = 0x00;

    while(I2C1_IsBusy());
    if(I2C1_WriteRead(device_address, &register_add, 1, &returnValue, 1))
    {
        while(I2C1_IsBusy());
    }
    
    return returnValue;    
}

void i2c_write1ByteRegister(uint16_t device_address, uint8_t register_add, uint8_t data)
{
    uint8_t data_block[2];
    data_block[0] = register_add;
    data_block[1] = data;
    
    while(I2C1_IsBusy());
    if(I2C1_Write(device_address, data_block, 2))
    {
        while(I2C1_IsBusy());
    }    
}

void i2c_readDataBlock(uint16_t device_address, uint8_t register_add, uint8_t *data, size_t length)
{
    while(I2C1_IsBusy());
    if(I2C1_WriteRead(device_address, &register_add, 1, data, length))
    {
        while(I2C1_IsBusy())
        {
            if(I2C1_ErrorGet() != I2C_ERROR_NONE)
            {
                printf("Error reading 6DOF I2C");
                __delay_ms(100);
            }
        }
    }
}

void IMU_6_DOF_Init(void)
{
    __delay_ms(10);
    // soft reset
    i2c_write1ByteRegister(IMU_6_DOF_ADDRESS, 0x7E, 0xB6);
    __delay_ms(100);

    //set normal power mode accelerometer
    i2c_write1ByteRegister(IMU_6_DOF_ADDRESS, 0x7E, 0x11);
    __delay_ms(10);
    //set normal power mode gyroscope
    i2c_write1ByteRegister(IMU_6_DOF_ADDRESS, 0x7E, 0x15);
    __delay_ms(80);
    
    //start fast offset calibration
    i2c_write1ByteRegister(IMU_6_DOF_ADDRESS, 0x7E, 0x03);
    __delay_ms(80);
    
    
//    i2c_write1ByteRegister(IMU_6_DOF_ADDRESS, ORIENT_G, ORIENT_G_INIT_VALUE);   
    i2c_write1ByteRegister(IMU_6_DOF_ADDRESS, CTRL1_XL, CTRL1_XL_INIT_VALUE_5);
    i2c_write1ByteRegister(IMU_6_DOF_ADDRESS, CTRL2_G, CTRL2_G_INIT_VALUE_3);        
    i2c_write1ByteRegister(IMU_6_DOF_ADDRESS, CTRL4_C, CTRL4_C_INIT_VALUE);
    
}

// Read the rotation rate around the pitch axis (left) from the gyro
int16_t IMU_6DOF_ReadPitchRate(void)
{
    uint8_t values[2];
    i2c_readDataBlock(IMU_6_DOF_ADDRESS, 0x0E, values, 2);
    
    return ((int16_t)( values[0] | ( values[1] << 8 ) ));
}


// Read the Y axis value from the accelerometer.
int16_t IMU_6DOF_ReadYAcc(void)
{
    int16_t retval;
    uint8_t values[2];
    
    i2c_readDataBlock(IMU_6_DOF_ADDRESS, 0x14, values, 2);
    
    retval = ( (int16_t)values[0] | ( (int16_t)values[1] << 8 ) );
    return retval;    
}


int16_t IMU_6DOF_ReadXAcc(void)
{
    int16_t retval;
    uint8_t values[2];
    
    i2c_readDataBlock(IMU_6_DOF_ADDRESS, 0x12, values, 2);
    
    retval = ( (int16_t)values[0] | ( (int16_t)values[1] << 8 ) );
    return retval;    
}


int16_t IMU_6DOF_ReadZAcc(void)
{
    int16_t retval;
    uint8_t values[2];
    
    i2c_readDataBlock(IMU_6_DOF_ADDRESS, 0x16, values, 2);
    
    retval = ( (int16_t)values[0] | ( (int16_t)values[1] << 8 ) );
    return retval;    
}

// Read the acceleration along the yaw axis (up)
int16_t IMU_6DOF_ReadYawAcc(void)
{
    int16_t retval;
    uint8_t values[2];
    
    i2c_readDataBlock(IMU_6_DOF_ADDRESS, 0x0C, values, 2);
    
    retval = ( (int16_t)values[0] | ( (int16_t)values[1] << 8 ) );
    return retval;    
}


/* Read the acceleration along the roll axis (backwards) */
int16_t IMU_6DOF_ReadRollAcc(void)
{
    int16_t retval;
    uint8_t values[2];
    
    i2c_readDataBlock(IMU_6_DOF_ADDRESS, 0x10, values, 2);
    
    retval = ( (int16_t)values[0] | ( (int16_t)values[1] << 8 ) );
    return retval;    
}