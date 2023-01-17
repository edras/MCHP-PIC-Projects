/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BME280_H
#define	BME280_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include "constants.h"

/**
  Section: BME280 Sensor Driver APIs
 */

char str_temp[30];
char str_press[30];
char str_hum[30];
char str_light[30];

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

uint8_t BME280_getID(void);
void BME280_reset(void);
void BME280_sleep(void);
void BME280_readFactoryCalibrationParams(void);
void BME280_config(uint8_t sbtime, uint8_t coeff);
void BME280_ctrl_meas(uint8_t osrs_T, uint8_t osrs_P, uint8_t mode);
void BME280_ctrl_hum(uint8_t osrs_H);
void BME280_init(void);
void BME280_initializeSensor(void);
void BME280_startForcedSensing(void);
void BME280_readMeasurements(void);
void BME280_readMeasurements(void);
float BME280_getTemperature(void);
float BME280_getHumidity(void);
float BME280_getPressure(void);
static long BME280_compensateTemperature(void);
uint32_t BME280_compensatePressure(void);
uint32_t BME280_compensateHumidity(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */


