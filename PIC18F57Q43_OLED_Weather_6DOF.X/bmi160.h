/* 
 * File:   IMU_6DOF.h
 * Author: M44307
 *
 * Created on March 20, 2018, 7:54 AM
 */

#ifndef IMU_6DOF_H
#define	IMU_6DOF_H
#include <stdint.h>

void IMU_6_DOF_Init(void);

int16_t IMU_6DOF_ReadPitchRate(void);
int16_t IMU_6DOF_ReadYawAcc(void);
int16_t IMU_6DOF_ReadRollAcc(void);

int16_t IMU_6DOF_ReadXRate(void);
int16_t IMU_6DOF_ReadYRate(void);
int16_t IMU_6DOF_ReadZRate(void);

int16_t IMU_6DOF_ReadXAcc(void);
int16_t IMU_6DOF_ReadYAcc(void);
int16_t IMU_6DOF_ReadZAcc(void);



#endif	/* IMU_6DOF_H */