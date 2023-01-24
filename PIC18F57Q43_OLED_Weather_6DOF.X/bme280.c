/*
 * File:   bme280.c
 * Author: M67732
 *
 * Created on July 22, 2022, 3:35 AM
 */


#include <xc.h>

#include "bme280.h"
#include "mcc_generated_files/system/system.h"

#include <stdio.h>

    /**
      Section: BME280 Macro Declarations
     */

    
    // Device Information
#define BME280_ADDR     			0x76
#define BME280_CHIP_ID  			0x60

    // Sensor Modes
#define BME280_SLEEP_MODE           0x00
#define BME280_FORCED_MODE          0x01
#define BME280_NORMAL_MODE          0x03
#define BME280_SOFT_RESET           0xB6

    // Oversampling Options
#define BME280_OVERSAMP_SKIPPED     0x00
#define BME280_OVERSAMP_X1          0x01
#define BME280_OVERSAMP_X2          0x02
#define BME280_OVERSAMP_X4          0x03
#define BME280_OVERSAMP_X8          0x04
#define BME280_OVERSAMP_X16         0x05

    // Standby Time
#define BME280_STANDBY_HALFMS   	0x00
#define BME280_STANDBY_63MS     	0x01
#define BME280_STANDBY_125MS    	0x02
#define BME280_STANDBY_250MS    	0x03
#define BME280_STANDBY_500MS    	0x04
#define BME280_STANDBY_1000MS   	0x05
#define BME280_STANDBY_10MS     	0x06
#define BME280_STANDBY_20MS     	0x07

    // Filter Coefficients
#define BME280_FILTER_COEFF_OFF     0x00
#define BME280_FILTER_COEFF_2       0x01
#define BME280_FILTER_COEFF_4       0x02
#define BME280_FILTER_COEFF_8       0x03
#define BME280_FILTER_COEFF_16      0x04

    // Register Addresses
#define BME280_ID_REG           0xD0 
#define BME280_RESET_REG        0xE0
#define BME280_CTRL_HUM_REG     0xF2
#define BME280_STATUS_REG       0xF3 
#define BME280_CTRL_MEAS_REG    0xF4   
#define BME280_CONFIG_REG       0xF5 
#define BME280_PRESS_MSB_REG    0xF7
#define BME280_PRESS_LSB_REG    0xF8
#define BME280_PRESS_XLSB_REG   0xF9 
#define BME280_TEMP_MSB_REG     0xFA
#define BME280_TEMP_LSB_REG     0xFB 
#define BME280_TEMP_XLSB_REG    0xFC 
#define BME280_HUM_MSB_REG      0xFD  
#define BME280_HUM_LSB_REG      0xFE

    // Sensor Data Read Bytes
#define BME280_PRESS_MSB        0
#define BME280_PRESS_LSB        1
#define BME280_PRESS_XLSB       2
#define BME280_TEMP_MSB         3
#define BME280_TEMP_LSB         4
#define BME280_TEMP_XLSB        5
#define BME280_HUM_MSB          6
#define BME280_HUM_LSB          7
#define BME280_DATA_FRAME_SIZE  8

    // Factory Calibration Parameters
#define BME280_CALIB_DT1_LSB_REG    0x88
#define BME280_CALIB_DT1_MSB_REG    0x89
#define BME280_CALIB_DT2_LSB_REG    0x8A
#define BME280_CALIB_DT2_MSB_REG    0x8B
#define BME280_CALIB_DT3_LSB_REG    0x8C
#define BME280_CALIB_DT3_MSB_REG    0x8D
#define BME280_CALIB_DP1_LSB_REG    0x8E
#define BME280_CALIB_DP1_MSB_REG    0x8F
#define BME280_CALIB_DP2_LSB_REG    0x90
#define BME280_CALIB_DP2_MSB_REG    0x91
#define BME280_CALIB_DP3_LSB_REG    0x92
#define BME280_CALIB_DP3_MSB_REG    0x93
#define BME280_CALIB_DP4_LSB_REG    0x94
#define BME280_CALIB_DP4_MSB_REG    0x95
#define BME280_CALIB_DP5_LSB_REG    0x96
#define BME280_CALIB_DP5_MSB_REG    0x97
#define BME280_CALIB_DP6_LSB_REG    0x98
#define BME280_CALIB_DP6_MSB_REG    0x99
#define BME280_CALIB_DP7_LSB_REG    0x9A
#define BME280_CALIB_DP7_MSB_REG    0x9B
#define BME280_CALIB_DP8_LSB_REG    0x9C
#define BME280_CALIB_DP8_MSB_REG    0x9D
#define BME280_CALIB_DP9_LSB_REG    0x9E
#define BME280_CALIB_DP9_MSB_REG    0x9F
#define BME280_CALIB_DH1_REG        0xA1
#define BME280_CALIB_DH2_LSB_REG    0xE1
#define BME280_CALIB_DH2_MSB_REG    0xE2
#define BME280_CALIB_DH3_REG        0xE3
#define BME280_CALIB_DH4_MSB_REG    0xE4
#define BME280_CALIB_DH4_LSB_REG    0xE5
#define BME280_CALIB_DH5_MSB_REG    0xE6
#define BME280_CALIB_DH6_REG        0xE7

    /**
     Section: Macro Declarations for reuse
     */
#define DEFAULT_STANDBY_TIME    BME280_STANDBY_HALFMS
#define DEFAULT_FILTER_COEFF    BME280_FILTER_COEFF_OFF
#define DEFAULT_TEMP_OSRS       BME280_OVERSAMP_X1
#define DEFAULT_PRESS_OSRS      BME280_OVERSAMP_X1
#define DEFAULT_HUM_OSRS        BME280_OVERSAMP_X1
#define DEFAULT_SENSOR_MODE     BME280_FORCED_MODE

/**
  Section: Variable Definitions
 */



typedef union {

    struct {
        uint8_t mode : 2;
        uint8_t osrs_P : 3;
        uint8_t osrs_T : 3;
    };
    uint8_t ctrlMeasReg;
} bme280_ctrl_meas_t;

typedef union {

    struct {
        uint8_t spi3w_en : 1;
        uint8_t filter : 3;
        uint8_t t_sb : 3;
    };
    uint8_t configReg;
} bme280_config_t;

typedef struct {
    uint16_t dig_T1;
    int dig_T2;
    int dig_T3;
    uint16_t dig_P1;
    int dig_P2;
    int dig_P3;
    int dig_P4;
    int dig_P5;
    int dig_P6;
    int dig_P7;
    int dig_P8;
    int dig_P9;
    uint8_t dig_H1;
    int dig_H2;
    uint8_t dig_H3;
    int dig_H4;
    int dig_H5;
    signed char dig_H6;
} bme280_calibration_param_t;

bme280_config_t bme280_config;
uint8_t bme280_ctrl_hum;
bme280_ctrl_meas_t bme280_ctrl_meas;
bme280_calibration_param_t calibParam;
long sensor_T, sensor_H, sensor_P, t_fine;
BME280_P_UNIT press_unit = KPA;
BME280_T_UNIT temp_unit = C;

/*
 * Function prototypes
 */

void BME280_readFactoryCalibrationParams(void);
void BME280_config(uint8_t sbtime, uint8_t coeff);
void BME280_ctrl_meas(uint8_t osrs_T, uint8_t osrs_P, uint8_t mode);
void BME280_ctrl_hum(uint8_t osrs_H);
long BME280_compensateTemperature(void);
uint32_t BME280_compensatePressure(void);
uint32_t BME280_compensateHumidity(void);

uint8_t I2C_ReadRegister(uint8_t register_add)
{
    uint8_t returnValue = 0x00;

    while(I2C1_IsBusy());
    if(I2C1_WriteRead(BME280_ADDR, &register_add, 1, &returnValue, 1))
    {
        while(I2C1_IsBusy());
    }
    
    return returnValue;    
}

void I2C_WriteRegister(uint8_t register_add, uint8_t data)
{
    uint8_t data_block[2];
    data_block[0] = register_add;
    data_block[1] = data;
    
    while(I2C1_IsBusy());
    if(I2C1_Write(BME280_ADDR, data_block, 2))
    {
        while(I2C1_IsBusy());
    }    
}

void I2C_ReadDataBlock(uint8_t register_add, uint8_t *data, size_t length)
{
    while(I2C1_IsBusy());
    if(I2C1_WriteRead(BME280_ADDR, &register_add, 1, data, length))
    {
        while(I2C1_IsBusy())
        {
            if(I2C1_ErrorGet() != I2C_ERROR_NONE)
            {
                printf("Error reading BME280 I2C");
                __delay_ms(1000);
            }
        }
    }
}

uint8_t BME280_getID(void) {
    return I2C_ReadRegister(BME280_ID_REG);
}

void BME280_reset(void) {
    I2C_WriteRegister(BME280_RESET_REG, BME280_SOFT_RESET);
}

void BME280_sleep(void) {
    bme280_ctrl_meas.mode = BME280_SLEEP_MODE;
    I2C_WriteRegister(BME280_CTRL_MEAS_REG, bme280_ctrl_meas.ctrlMeasReg);
}

void BME280_readFactoryCalibrationParams(void) {
    uint8_t paramBuff[24];
    I2C_ReadDataBlock(BME280_CALIB_DT1_LSB_REG, paramBuff, 24);
    calibParam.dig_T1 = (((uint16_t) paramBuff[1]) << 8) + paramBuff[0];
    calibParam.dig_T2 = (((int) paramBuff[3]) << 8) + paramBuff[2];
    calibParam.dig_T3 = (((int) paramBuff[5]) << 8) + paramBuff[4];
    calibParam.dig_P1 = (((uint16_t) paramBuff[7]) << 8) + paramBuff[6];
    calibParam.dig_P2 = (((int) paramBuff[9]) << 8) + paramBuff[8];
    calibParam.dig_P3 = (((int) paramBuff[11]) << 8) + paramBuff[10];
    calibParam.dig_P4 = (((int) paramBuff[13]) << 8) + paramBuff[12];
    calibParam.dig_P5 = (((int) paramBuff[15]) << 8) + paramBuff[14];
    calibParam.dig_P6 = (((int) paramBuff[17]) << 8) + paramBuff[16];
    calibParam.dig_P7 = (((int) paramBuff[19]) << 8) + paramBuff[18];
    calibParam.dig_P8 = (((int) paramBuff[21]) << 8) + paramBuff[20];
    calibParam.dig_P9 = (((int) paramBuff[23]) << 8) + paramBuff[22];

    calibParam.dig_H1 = (uint8_t) I2C_ReadRegister(BME280_CALIB_DH1_REG);

    I2C_ReadDataBlock(BME280_CALIB_DH2_LSB_REG, paramBuff, 7);
    calibParam.dig_H2 = (((int) paramBuff[1]) << 8) + paramBuff[0];
    calibParam.dig_H3 = (uint8_t) paramBuff[2];
    calibParam.dig_H4 = (((int) paramBuff[3]) << 4) | (paramBuff[4] & 0xF);
    calibParam.dig_H5 = (((int) paramBuff[5]) << 4) | (paramBuff[4] >> 4);
    calibParam.dig_H6 = (signed char) paramBuff[6];
}

void BME280_config(uint8_t sbtime, uint8_t coeff) {
    bme280_config.t_sb = sbtime; // Set standby time;
    bme280_config.filter = coeff; // Set filter coefficient;
}

void BME280_ctrl_meas(uint8_t osrs_T, uint8_t osrs_P, uint8_t mode) {
    bme280_ctrl_meas.osrs_T = osrs_T; // Set oversampling temperature;
    bme280_ctrl_meas.osrs_P = osrs_P; // Set oversampling pressure;
    bme280_ctrl_meas.mode = mode; // Set sensor mode;
}

void BME280_ctrl_hum(uint8_t osrs_H) {
    bme280_ctrl_hum = osrs_H; // Set oversampling humidity;
}

void BME280_init(void)
{
    BME280_reset();
    __delay_ms(50);
    BME280_readFactoryCalibrationParams();
    BME280_config(BME280_STANDBY_HALFMS, BME280_FILTER_COEFF_OFF);
    BME280_ctrl_meas(BME280_OVERSAMP_X1, BME280_OVERSAMP_X1, BME280_FORCED_MODE);
    BME280_ctrl_hum(BME280_OVERSAMP_X1);
    
    I2C_WriteRegister(BME280_CONFIG_REG, bme280_config.configReg);
    I2C_WriteRegister(BME280_CTRL_HUM_REG, bme280_ctrl_hum);
    I2C_WriteRegister(BME280_CTRL_MEAS_REG, bme280_ctrl_meas.ctrlMeasReg);   
}

/* After calling this function, wait for conversion to be read before read */
void BME280_startMeasurements(void) {
    bme280_ctrl_meas.mode = BME280_FORCED_MODE;
    I2C_WriteRegister(BME280_CTRL_MEAS_REG, bme280_ctrl_meas.ctrlMeasReg);
}

void BME280_readMeasurements(void) {

    uint8_t sensorData[BME280_DATA_FRAME_SIZE];

    I2C_ReadDataBlock(BME280_PRESS_MSB_REG, sensorData, BME280_DATA_FRAME_SIZE);
    
    sensor_H = (long)(
            ((uint32_t) sensorData[BME280_HUM_MSB] << 8) |
            sensorData[BME280_HUM_LSB]);

    sensor_T = (long)(
            ((uint32_t) sensorData[BME280_TEMP_MSB] << 12) |
            (((uint32_t) sensorData[BME280_TEMP_LSB] << 4) |
            ((uint32_t) sensorData[BME280_TEMP_XLSB] >> 4)));

    sensor_P = (long)(
            ((uint32_t) sensorData[BME280_PRESS_MSB] << 12) |
            (((uint32_t) sensorData[BME280_PRESS_LSB] << 4) |
            ((uint32_t) sensorData[BME280_PRESS_XLSB] >> 4)));
}

void BME280_setPressureUnity(BME280_P_UNIT unity)
{
    press_unit = unity;
}

void BME280_setTempUnity(BME280_T_UNIT unity)
{
    temp_unit = unity;
}

float BME280_getTemperature(void) {
    float temperature = (float) BME280_compensateTemperature() / 100;
    if(temp_unit == K)
    {
        return temperature + 273.15F;
    }
    else if(temp_unit == F)
    {
        return (temperature * 9/5) + 32;
    }
    return temperature;
}

float BME280_getPressure(void) {
    float pressure = (float) BME280_compensatePressure() / 1000;
    if(press_unit == PA)
    {
        return pressure * 1000;
    }
    else if(press_unit == INHG)
    {
        return pressure * 0.295301F;        
    }
    else if(press_unit == PSI)
    {
        return pressure * 0.145038F;
    }
    return pressure;
}

float BME280_getHumidity(void) {
    float humidity = (float) BME280_compensateHumidity() / 1024;
    return humidity;
}

/* 
 * Returns temperature in DegC, resolution is 0.01 DegC. 
 * Output value of "5123" equals 51.23 DegC.  
 */
long BME280_compensateTemperature(void) {
    long tempV1, tempV2, t;
    
    tempV1 = ((((sensor_T >> 3) - ((long) calibParam.dig_T1 << 1))) * 
            ((long) calibParam.dig_T2)) >> 11;
    
    tempV2 = (((((sensor_T >> 4) - ((long) calibParam.dig_T1)) * 
            ((sensor_T >> 4) - ((long) calibParam.dig_T1))) >> 12) *
            ((long) calibParam.dig_T3)) >> 14;
    
    t_fine = tempV1 + tempV2;
    t = (t_fine * 5 + 128) >> 8;
    
    return t;
}

/* 
 * Returns pressure in Pa as unsigned 32 bit integer. 
 * Output value of "96386" equals 96386 Pa = 96.386 kPa 
 */
uint32_t BME280_compensatePressure(void) {
    long pressV1, pressV2;
    uint32_t p;

    pressV1 = (((long) t_fine) >> 1) - (long) 64000;
    pressV2 = (((pressV1 >> 2) * (pressV1 >> 2)) >> 11) * ((long) calibParam.dig_P6);
    pressV2 = pressV2 + ((pressV1 * ((long) calibParam.dig_P5)) << 1);
    pressV2 = (pressV2 >> 2)+(((long) calibParam.dig_P4) << 16);
    pressV1 = (((calibParam.dig_P3 * (((pressV1 >> 2) * (pressV1 >> 2)) >> 13)) >> 3) +
            ((((long) calibParam.dig_P2) * pressV1) >> 1)) >> 18;
    pressV1 = ((((32768 + pressV1))*((long) calibParam.dig_P1)) >> 15);

    if (pressV1 == 0) {
        return 0;
    }

    p = (uint32_t)((((long)1048576 - sensor_P)-(pressV2 >> 12)) * 3125);
    if (p < 0x80000000) 
    {
        p = (p << 1) / ((uint32_t) pressV1);
    } 
    else 
    {
        p = (p / (uint32_t) pressV1) * 2;
    }

    pressV1 = (((long) calibParam.dig_P9) * ((long) (((p >> 3) * (p >> 3)) >> 13))) >> 12;
    pressV2 = (((long) (p >> 2)) * ((long) calibParam.dig_P8)) >> 13;
    p = (uint32_t) ((long) p + ((pressV1 + pressV2 + calibParam.dig_P7) >> 4));

    return p;
}

uint32_t BME280_compensateHumidity(void) {
    long humV;
    uint32_t h;

    humV = (t_fine - ((long) 76800));
    humV = (((((sensor_H << 14) - (((long) calibParam.dig_H4) << 20) - (((long) calibParam.dig_H5) * humV)) +
            ((long) 16384)) >> 15) * (((((((humV * ((long) calibParam.dig_H6)) >> 10) *
            (((humV * ((long) calibParam.dig_H3)) >> 11) + ((long) 32768))) >> 10) +
            ((long) 2097152)) * ((long) calibParam.dig_H2) + 8192) >> 14));
    humV = (humV - (((((humV >> 15) * (humV >> 15)) >> 7) * ((long) calibParam.dig_H1)) >> 4));
    humV = (humV < 0 ? 0 : humV);
    humV = (humV > 419430400 ? 419430400 : humV);

    h = (uint32_t) (humV >> 12);
    return h;
}

