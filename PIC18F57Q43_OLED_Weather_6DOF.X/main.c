 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "bme280.h"
#include "bmi160.h"
#include "oled.h"
#include "logo.h"
#include "timer.h"

/*
    Main application
*/

#define BME280_READING_TIME 1000
#define LED_TOGGLE_TIME     500
#define WEATHER_PRINT_TIME  3000
#define IMU_6DOF_TIME       1000

unsigned long bme280Time = 0;
unsigned long ledToggleTime = 0;
unsigned long weatherPrintTime = 0;
unsigned long imu6DofTime = 0;

void readWeatherData(void)
{
    unsigned long currentMillis = TIMER_getCurrentMillis();
    if(currentMillis > bme280Time)
    {
        bme280Time = currentMillis + BME280_READING_TIME;
        BME280_readMeasurements();
        BME280_startMeasurements();
    }
}

void toggleLed(void)
{
    unsigned long currentMillis = TIMER_getCurrentMillis();
    if(currentMillis > ledToggleTime)
    {
        ledToggleTime = currentMillis + LED_TOGGLE_TIME;
        LED_Toggle();
    }    
}

void printWeatherData(void)
{
    unsigned long currentMillis = TIMER_getCurrentMillis();
    char buffer[20];
    
    if(currentMillis > weatherPrintTime)
    {
        weatherPrintTime = currentMillis + WEATHER_PRINT_TIME;
        float moisture = BME280_getHumidity();
        float temperature = BME280_getTemperature();
        float pressure = BME280_getPressure();
        printf("T:%.2fC H:%.1f%% P:%.2fKPa\r\n", 
                temperature, moisture, pressure);
        sprintf(buffer, "T:%.1fC H:%.1f%%", temperature, moisture);
        OLED_Puts(0, 0, buffer);
        sprintf(buffer, "P:%.2fKPa", pressure);
        OLED_Puts(0, 1, buffer);
    }       
}

void print6DOFData(void)
{
    unsigned long currentMillis = TIMER_getCurrentMillis();
    
    if(currentMillis > imu6DofTime)
    {
        imu6DofTime = currentMillis + IMU_6DOF_TIME;
        int16_t xAcc = IMU_6DOF_ReadXAcc();
        int16_t yAcc = IMU_6DOF_ReadYAcc();
        int16_t zAcc = IMU_6DOF_ReadZAcc();
        printf("Accel x:%d y:%d z:%d\r\n",  xAcc, yAcc, zAcc);
        //sprintf(buffer, "T:%.1fC H:%.1f%%", temperature, moisture);
        //OLED_Puts(0, 0, buffer);
        //sprintf(buffer, "P:%.2fKPa", pressure);
        //OLED_Puts(0, 1, buffer);
    }       
}

void printUart2Oled()
{
    char buffer[16];
    if(UART1_IsRxReady())
    {   
        uint8_t ptr = 0;
        uint8_t rx_char = 0;
        uint16_t timeout = 0;
        OLED_Puts(0, 4, "                ");
        while(rx_char != '\n')
        {
            if(UART1_IsRxReady())
            {
                rx_char = UART1_Read();
                if(rx_char == '\r' || rx_char == '\n') continue;
                buffer[ptr++] = rx_char;                
                ptr &= 0x0F;                
            }
            else
            {
                timeout++;
                if(timeout == 0) return;
            }
        }
        buffer[ptr] = 0x00;
        OLED_Puts(0, 4, buffer);
        while(UART1_IsRxReady()) UART1_Read();
    }    
}

int main(void)
{
    SYSTEM_Initialize();

    INTERRUPT_GlobalInterruptEnable(); 
    
    Timer0_OverflowCallbackRegister(TIMER_Callback);

    BME280_init();
    BME280_setPressureUnity(KPA);
    BME280_setTempUnity(C);
    
    IMU_6_DOF_Init();
    
    OLED_Initialize();
    OLED_PrintCuriosityLogo();
    OLED_Clear();
    
    while(1)
    {
        readWeatherData();
        printWeatherData();
        print6DOFData();
        printUart2Oled();
        toggleLed();
    }    
}