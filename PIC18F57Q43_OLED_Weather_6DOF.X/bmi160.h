/* 
 * File:   IMU_6DOF.h
 * Author: M44307
 *
 * Created on March 20, 2018, 7:54 AM
 */

#ifndef IMU_6DOF_H
#define	IMU_6DOF_H
#include <stdint.h>

#define IMU_6DOF_TABLE_SIZE 0x7E

typedef struct {
    unsigned int sign       : 1;
    unsigned int single_tap : 1;
    unsigned int double_tap : 1;
    unsigned int x          : 1;
    unsigned int y          : 1;
    unsigned int z          : 1;    
} IMU_6DOF_Click;

void IMU_6DOF_Init(void);

int16_t IMU_6DOF_ReadXGyr(void);
int16_t IMU_6DOF_ReadYGyr(void);
int16_t IMU_6DOF_ReadZGyr(void);

int16_t IMU_6DOF_ReadXAcc(void);
int16_t IMU_6DOF_ReadYAcc(void);
int16_t IMU_6DOF_ReadZAcc(void);

uint8_t IMU_6DOF_ReadRegister(uint8_t reg);
void IMU_6DOF_WriteRegister(uint8_t reg, uint8_t data);
void IMU_6DOF_ReadDataBlock(uint8_t regi, uint8_t *data, size_t length);

void IMU_6DOF_SetInterruptEnable(bool enable);
void IMU_6DOF_InterruptHandler(void);
bool IMU_6DOF_checkInterrupt(IMU_6DOF_Click *click);


#endif	/* IMU_6DOF_H */