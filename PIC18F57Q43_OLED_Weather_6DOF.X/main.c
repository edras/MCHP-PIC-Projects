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
#include "tasks.h"
#include "app.h"

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();

    INTERRUPT_GlobalInterruptEnable(); 
    
    Timer0_OverflowCallbackRegister(Task_synch);

    BME280_init();
    BME280_setPressureUnity(KPA);
    BME280_setTempUnity(C);
    
    IMU_6DOF_Init();
    IMU_6DOF_SetInterruptEnable(true);
    INT2_SetInterruptHandler(IMU_6DOF_InterruptHandler);
    
    OLED_Initialize();
    OLED_PrintCuriosityLogo();
    OLED_Clear();
    
    printHeader();
    
    Task_register(0, BME280_READING_TIME, readWeatherData);
    Task_register(0, LED_TOGGLE_TIME, toggleLed);
    Task_register(0, BUBBLE_TIME, scrollBubble);
    Task_register(100, IMU_6DOF_TIME, print6DOFData);
    Task_register(1000, WEATHER_PRINT_TIME, printWeatherData);
    
    while(1)
    {
        Task_execute();
        readUartCommand();
        handleClick();
    }    
}