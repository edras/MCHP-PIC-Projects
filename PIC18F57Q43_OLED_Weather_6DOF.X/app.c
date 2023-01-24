/*
 * File:   app.c
 * Author: M71906
 *
 * Created on 23. Januar 2023, 12:48
 */

#include "mcc_generated_files/system/system.h"
#include "app.h"
#include "bme280.h"
#include "bmi160.h"
#include "oled.h"
#include "tasks.h"
#include <string.h>

/* private variable */
int16_t xAccBall = 0;

/* private function prototypes */
void print2Oled(char * buffer);
void getStringBuffer(char * buffer);
void dump6DOF(void);
void get6DOF(char * buffer);
void set6DOF(char * buffer);
void cmd6DOF(char * buffer);
void changeOLEDContrast(IMU_6DOF_Click *click);
void printClickResult(IMU_6DOF_Click *click);
void clearClick(void);

/* function implementations */
void readWeatherData(void)
{
    BME280_readMeasurements();
    BME280_startMeasurements();
}

void toggleLed(void)
{
    LED_Toggle();
}

void printHeader(void)
{
    printf("\033[2J");      //Clear screen
    printf("\033[0;0f");    //return cursor to 0,0
    printf("\033[?25l");    //disable cursor
    
    printf("------------------------------------------------------------------\r\n");
    printf("PIC18F57Q43 Curiosity Development Board Demo                      \r\n");
    printf("1[Weather (BME280)] 2[OLEDW 96x96] 3[IMU_6DOF 2]                  \r\n");
    printf("------------------------------------------------------------------\r\n");
    printf("c - Clear screen \r\n");
    printf("> - Send text to OLED, ex: >Show this!\r\n");
    printf("6 [ ] [...] - Interact with 6DOF sensor:\r\n");
    printf("   r        - reset \r\n");
    printf("   d        - dump memory \r\n");
    printf("   g R      - get memory data at R address: 6 g 00\r\n");
    printf("   s R D:   - set memory data at R address: 6 s 7E B0 (reset)\r\n");
    printf("\r\n");
}

void printWeatherData(void)
{
    unsigned buffer[20];
    float moisture = BME280_getHumidity();
    float temperature = BME280_getTemperature();
    float pressure = BME280_getPressure();
    printf("\033[12;0f\n");  //cursor to row 11, column 0 (after header)
    printf("Weather\t\tT: %.2fC \tH: %.1f%% \tP: %.2fKPa      \r\n", 
            temperature, moisture, pressure);
    sprintf((char*)buffer, "T:%.1fC H:%.1f%%", temperature, moisture);
    OLED_Puts(0, 0, (char*)buffer);
    sprintf((char*)buffer, "P:%.2fKPa", pressure);
    OLED_Puts(0, 1, (char*)buffer);
}

void print6DOFData(void)
{
    int16_t xAcc = IMU_6DOF_ReadXAcc();
    int16_t yAcc = IMU_6DOF_ReadYAcc();
    int16_t zAcc = IMU_6DOF_ReadZAcc();
    int16_t xGyr = IMU_6DOF_ReadXGyr();
    int16_t yGyr = IMU_6DOF_ReadYGyr();
    int16_t zGyr = IMU_6DOF_ReadZGyr();
    printf("\033[13;0f\n");  //cursor to row 11, column 0 (after weather data)
    printf("Accelerometer \tx:%+6d \ty:%+6d \tz:%+6d   \r\n",  xAcc, yAcc, zAcc);
    printf("Gyroscope \tx:%+6d \ty:%+6d \tz:%+6d       \r\n",  xGyr, yGyr, zGyr);
}

void print2Oled(char * buffer)
{
    OLED_Puts(0, 4, "                ");
    for(uint8_t i=1; i<0x0F; i++)
    {
        buffer[i-1] = buffer[i];
        if(buffer[i-1] == '\n')
        {
            buffer[i] = 0x00;
            break;
        }
    }
    OLED_Puts(0, 4, buffer);
}

void getStringBuffer(char * buffer)
{
    uint8_t ptr = 0;
    uint8_t rx_char = 0;
    uint16_t timeout = 0;
    buffer[0] = 0x00;
    while(rx_char != '\n')
    {
        if(UART1_IsRxReady())
        {
            rx_char = UART1_Read();
            if(rx_char == '\r') continue;
            buffer[ptr++] = rx_char;                
            ptr &= 0x0F;                
        }
        else
        {
            timeout++;
            if(timeout == 0) return;
        }
    } 
    while(UART1_IsRxReady()) UART1_Read();
}

void dump6DOF(void)
{
    uint8_t buffer[IMU_6DOF_TABLE_SIZE+1];
    IMU_6DOF_ReadDataBlock(0, buffer, IMU_6DOF_TABLE_SIZE);
    printf("\033[16;0f\n");  //cursor to row 14, column 0 (after weather data)
    printf("Dumping 6DOF Register Table\r\n");
    printf("Address\tValue\r\n");
    for(int8_t i = IMU_6DOF_TABLE_SIZE; i>-1; i--)
    {
        printf("%#X\t%#X\r\n", i, buffer[i]);
    }
}

void get6DOF(char * buffer)
{
    char hexString[3];
    uint8_t reg = 0;
    hexString[0] = buffer[4];
    hexString[1] = buffer[5];
    hexString[2] = 0x00;
    reg = (uint8_t)strtol(hexString, NULL, 16);
    if(reg > IMU_6DOF_TABLE_SIZE) reg = IMU_6DOF_TABLE_SIZE;
    printf("\033[16;0f\n");  //cursor to row 14, column 0 (after weather data)
    printf("Reading 6DOF Register\r\n");
    printf("[%#X]: %#X           \r\n", reg, IMU_6DOF_ReadRegister(reg));
}

void set6DOF(char * buffer)
{
    char hexString[3];
    uint8_t reg = 0;
    uint8_t val = 0;
    uint8_t old_val = 0;
    hexString[0] = buffer[4];
    hexString[1] = buffer[5];
    hexString[2] = 0x00;
    reg = (uint8_t)strtol(hexString, NULL, 16);
    if(reg > IMU_6DOF_TABLE_SIZE) reg = IMU_6DOF_TABLE_SIZE;
    hexString[0] = buffer[4];
    hexString[1] = buffer[5];
    hexString[2] = 0x00;
    reg = (uint8_t)strtol(hexString, NULL, 16);
    if(reg > IMU_6DOF_TABLE_SIZE) reg = IMU_6DOF_TABLE_SIZE;
    hexString[0] = buffer[7];
    hexString[1] = buffer[8];
    val = (uint8_t)strtol(hexString, NULL, 16);
    old_val = IMU_6DOF_ReadRegister(reg);
    IMU_6DOF_WriteRegister(reg, val);
    printf("\033[16;0f\n");  //cursor to row 14, column 0 (after weather data)
    printf("Setting 6DOF Register\r\n");
    printf("[%#X]: %#X -> %#X\r\n", reg, old_val, IMU_6DOF_ReadRegister(reg));    
}

void cmd6DOF(char * buffer)
{
    switch(buffer[2])
    {
        case 'r': IMU_6DOF_Init();  break;
        case 'd': dump6DOF();       break;
        case 'g': get6DOF(buffer);  break;
        case 's': set6DOF(buffer);  break;
        default: return;
    }    
}

void readUartCommand()
{
    char buffer[16];
    if(UART1_IsRxReady())
    {   
        getStringBuffer(buffer);
        switch(buffer[0])
        {
            case 0: return; // end-of-string
            case 'c': printHeader();      break;
            case '>': print2Oled(buffer); break;
            case '6': cmd6DOF(buffer);    break;
        }
    }
}

void changeOLEDContrast(IMU_6DOF_Click *click)
{
    if(click->double_tap && click->x)
    {        
        uint8_t contrast = OLED_GetContrast();
        uint8_t step = 30;
        if(click->sign) contrast += step; 
        else            contrast -= step;
        if(contrast > 220) contrast = 220;
        if(contrast < step)  contrast = 30;
        OLED_SetContrast(contrast);
    }
}

void printClickResult(IMU_6DOF_Click *click)
{
    char result[6] = "      ";
    if(click->sign)
    {
        if(click->double_tap)
        {
            if      (click->x) strcpy(result, " >> ");
            else if (click->y) strcpy(result, "//\\\\");
            else if (click->z) strcpy(result, "((-))");
        }            
        else
        {
            if      (click->x) strcpy(result, "  > ");
            else if (click->y) strcpy(result, "  /\\");
            else if (click->z) strcpy(result, " (-)");
        }
    }
    else
    {
        if(click->double_tap)
        {
            if      (click->x) strcpy(result, " << ");
            else if (click->y) strcpy(result, "\\\\//");
            else if (click->z) strcpy(result, "((+))");
        }            
        else
        {
            if      (click->x) strcpy(result, "  < ");
            else if (click->y) strcpy(result, " \\/");
            else if (click->z) strcpy(result, " (+)");
        }
    }
    printf("\033[15;0f\n"); 
    printf("Click Interrupt: %s", result);
    OLED_Puts(5, 2, result);    
}

void clearClick(void)
{
    printf("\033[15;0f\n"); 
    printf("                         ");
    OLED_Puts(5, 2, "     ");    
}

void handleClick(void)
{
    IMU_6DOF_Click click;
    if(IMU_6DOF_checkInterrupt(&click))
    {
        printClickResult(&click);
        changeOLEDContrast(&click);
        Task_register(IMU_6DOF_CLICK_TIME, 0, clearClick);
    }    
}

void scrollBubble(void)
{
    int16_t temp = IMU_6DOF_ReadXAcc();
    temp /= 341;
    temp += 48;
    if(temp < 0) temp = 0;
    if(temp > 91) temp = 91;
    if(temp != xAccBall)
    {
        OLED_DrawChar((uint8_t)xAccBall, 3, ' ');
        xAccBall = temp;
        OLED_DrawChar((uint8_t)xAccBall, 3, 'o');
    }        
}
