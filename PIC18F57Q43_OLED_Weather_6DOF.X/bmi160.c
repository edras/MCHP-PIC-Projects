#include "mcc_generated_files/system/system.h"
#include "bmi160.h"

#define IMU_6_DOF_ADDRESS 0b1101000 //NOTE: The LSB is hardwired to 1 on the 6DOF Clickboard

/* Some 6 DOF IMU Click board register addresses */
#define REG_CMD             0x7E
#define CMD_START_FOC       0x03  // Fast Offset Calibration
#define CMD_APMU_MODE_SUSP  0x10  // Acc Power Mode Suspend
#define CMD_APMU_MODE_NORM  0x11  // Acc PMU Normal
#define CMD_APMU_MODE_LP    0x12  // Acc PMU Low Power
#define CMD_GPMU_MODE_SUSP  0x14  // Gyr Power Mode Suspend
#define CMD_GPMU_MODE_NORM  0x15  // Gyr PMU Normal
#define CMD_GPMU_MODE_LP    0x17  // Gyr PMU Fast Start-up
#define CMD_MPMU_MODE_SUSP  0x18  // Mag Power Mode Suspend
#define CMD_MPMU_MODE_NORM  0x19  // Mag PMU Normal
#define CMD_MPMU_MODE_LP    0x1A  // Mag PMU Fast Start-up
#define CMD_PROG_NVM        0xA0  // Writes the NVM regsiters into NVM
#define CMD_FIFO_FLUSH      0xB0  // clears all data in the FIFO
#define CMD_INT_RESET       0xB1  // resets the interrupt engine
#define CMD_SOFT_RESET      0xB6  // triggers a reset including a reboot
#define CMD_STEP_CNT_CLR    0xB2  // Trigger a reset of the step counter

#define REG_INT_STATUS_0    0x1C
#define BIT_INT_S0_FLAT     0x80
#define BIT_INT_S0_ORIENT   0x40
#define BIT_INT_S0_S_TAP    0x20
#define BIT_INT_S0_D_TAP    0x10
#define BIT_INT_S0_PMU_TRG  0x08
#define BIT_INT_S0_ANY_MOV  0x04
#define BIT_INT_S0_SIG_MOT  0x02
#define BIT_INT_S0_STEP     0x01

#define REG_INT_STATUS_1    0x1D
#define BIT_INT_S1_NO_MOV   0x80
#define BIT_INT_S1_FWM      0x40
#define BIT_INT_S1_FFULL    0x20
#define BIT_INT_S1_DRDY     0x10
#define BIT_INT_S1_LOWG     0x08
#define BIT_INT_S1_HIGHG    0x04
#define BIT_INT_S1_RESV1    0x02
#define BIT_INT_S1_RESV0    0x01

#define REG_INT_STATUS_2    0x1E
#define BIT_INT_S2_TAP_SIGN 0x80
#define BIT_INT_S2_TAP_1STZ 0x40
#define BIT_INT_S2_TAP_1STY 0x20
#define BIT_INT_S2_TAP_1STX 0x10
#define BIT_INT_S2_ANY_SIGN 0x08
#define BIT_INT_S2_ANY_1STZ 0x04
#define BIT_INT_S2_ANY_1STY 0x02
#define BIT_INT_S2_ANY_1STX 0x01

#define REG_INT_STATUS_3    0x1F
#define BIT_INT_S3_FLAT     0x80
#define BIT_INT_S3_ORIENT_2 0x40
#define BIT_INT_S3_ORIENT_1 0x20
#define BIT_INT_S3_ORIENT_0 0x10
#define BIT_INT_S3_H_SIGN   0x08
#define BIT_INT_S3_H_1STZ   0x04
#define BIT_INT_S3_H_1STY   0x02
#define BIT_INT_S3_H_1STX   0x01

#define REG_INT_EN          0x50
#define BIT_INT_EN_FLAT     0x80
#define BIT_INT_EN_ORIENT   0x40
#define BIT_INT_EN_S_TAP    0x20
#define BIT_INT_EN_D_TAP    0x10
#define BIT_INT_EN_RSV      0x08
#define BIT_INT_EN_ANYMZ    0x04
#define BIT_INT_EN_ANYMY    0x02
#define BIT_INT_EN_ANYMX    0x01

bool interrupt_triggered = false;

bool IMU_6DOF_checkInterrupt(IMU_6DOF_Click *click)
{
    if(interrupt_triggered)
    {
        interrupt_triggered = false;
        uint8_t which_int  = IMU_6DOF_ReadRegister(REG_INT_STATUS_0);
        uint8_t sign_first = IMU_6DOF_ReadRegister(REG_INT_STATUS_2);
        IMU_6DOF_WriteRegister(REG_CMD, CMD_INT_RESET); 

        click->sign = (bool)(sign_first & BIT_INT_S2_TAP_SIGN);
        click->single_tap = (bool) (which_int & BIT_INT_S0_S_TAP);
        click->double_tap = (bool) (which_int & BIT_INT_S0_D_TAP);
        click->x = (bool)(sign_first & BIT_INT_S2_TAP_1STX);
        click->y = (bool)(sign_first & BIT_INT_S2_TAP_1STY);
        click->z = (bool)(sign_first & BIT_INT_S2_TAP_1STZ);
        
        return true;
    }
    return false;
}

uint8_t IMU_6DOF_ReadRegister(uint8_t register_add)
{
    uint8_t returnValue = 0x00;

    while(I2C1_IsBusy());
    if(I2C1_WriteRead(IMU_6_DOF_ADDRESS, &register_add, 1, &returnValue, 1))
    {
        while(I2C1_IsBusy());
    }
    
    return returnValue;    
}

void IMU_6DOF_WriteRegister(uint8_t register_add, uint8_t data)
{
    uint8_t data_block[2];
    data_block[0] = register_add;
    data_block[1] = data;
    
    while(I2C1_IsBusy());
    if(I2C1_Write(IMU_6_DOF_ADDRESS, data_block, 2))
    {
        while(I2C1_IsBusy());
    }    
}

void IMU_6DOF_ReadDataBlock(uint8_t register_add, uint8_t *data, size_t length)
{
    while(I2C1_IsBusy());
    if(I2C1_WriteRead(IMU_6_DOF_ADDRESS, &register_add, 1, data, length))
    {
        while(I2C1_IsBusy());
    }
}

void IMU_6DOF_SetInterruptEnable(bool enable)
{
    unsigned char int_config = 0;
    int_config = BIT_INT_EN_D_TAP + BIT_INT_EN_S_TAP;
    
    if(enable)
    {
        IMU_6DOF_WriteRegister(REG_INT_EN, int_config);
    }
    else
    {
        IMU_6DOF_WriteRegister(REG_INT_EN, 0x00);        
    }
}

void IMU_6DOF_InterruptHandler(void)
{
    interrupt_triggered = true;
}

void IMU_6DOF_Init(void)
{
    __delay_ms(10);
    // soft reset
    IMU_6DOF_WriteRegister(REG_CMD, CMD_SOFT_RESET);
    __delay_ms(100);
    //set normal power mode accelerometer
    IMU_6DOF_WriteRegister(REG_CMD, CMD_APMU_MODE_NORM); 
    __delay_ms(10);
    //set normal power mode gyroscope
    IMU_6DOF_WriteRegister(REG_CMD, CMD_GPMU_MODE_NORM);
    __delay_ms(80);    
    //start fast offset calibration
    IMU_6DOF_WriteRegister(REG_CMD, CMD_START_FOC);
    __delay_ms(80);
    
    //change sampling from 100Hz (0x28) to 200Hz (0x29)
    IMU_6DOF_WriteRegister(0x40, 0x29);
    //single & double tap interrupt MAP to INT1 pin (INT2 Curiosity)
    IMU_6DOF_WriteRegister(0x55, 0x30);  
    // LATCHED interrupt (must be cleared)
    IMU_6DOF_WriteRegister(0x54, 0x0F);  
    //enable output INT1, active HIGH, push-pull
    IMU_6DOF_WriteRegister(0x53, 0x0A);  
    
    //to enable interrupts, call module function IMU_6DOF_SetInterruptEnable
    
    //interrupt enable for tap and double tap
    //IMU_6DOF_WriteRegister(REG_INT_EN, BIT_INT_EN_S_TAP | BIT_INT_EN_D_TAP);  
}

// Read the Y axis value from the accelerometer.
int16_t IMU_6DOF_ReadYAcc(void)
{
    int16_t retval;
    uint8_t values[2];
    
    IMU_6DOF_ReadDataBlock(0x14, values, 2);
    
    retval = ( (int16_t)values[0] | ( (int16_t)values[1] << 8 ) );
    return retval;    
}


int16_t IMU_6DOF_ReadXAcc(void)
{
    int16_t retval;
    uint8_t values[2];
    
    IMU_6DOF_ReadDataBlock(0x12, values, 2);
    
    retval = ( (int16_t)values[0] | ( (int16_t)values[1] << 8 ) );
    return retval;    
}


int16_t IMU_6DOF_ReadZAcc(void)
{
    int16_t retval;
    uint8_t values[2];
    
    IMU_6DOF_ReadDataBlock(0x16, values, 2);
    
    retval = ( (int16_t)values[0] | ( (int16_t)values[1] << 8 ) );
    return retval;    
}

int16_t IMU_6DOF_ReadXGyr(void)
{
    int16_t retval;
    uint8_t values[2];
    
    IMU_6DOF_ReadDataBlock(0x0C, values, 2);
    
    retval = ( (int16_t)values[0] | ( (int16_t)values[1] << 8 ) );
    return retval;    
}

// Read the rotation rate around the pitch axis (left) from the gyro
int16_t IMU_6DOF_ReadYGyr(void)
{
    uint8_t values[2];
    IMU_6DOF_ReadDataBlock(0x0E, values, 2);
    
    return ((int16_t)( values[0] | ( values[1] << 8 ) ));
}

/* Read the acceleration along the roll axis (backwards) */
int16_t IMU_6DOF_ReadZGyr(void)
{
    int16_t retval;
    uint8_t values[2];
    
    IMU_6DOF_ReadDataBlock(0x10, values, 2);
    
    retval = ( (int16_t)values[0] | ( (int16_t)values[1] << 8 ) );
    return retval;    
}