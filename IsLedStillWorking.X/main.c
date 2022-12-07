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
© [2022] Microchip Technology Inc. and its subsidiaries.

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

/*
    Main application
*/

bool positive_logic = true;
bool debug = false;

void printHeader()
{
    printf("\033[2J");      //Clear screen
    printf("\033[0;0f");    //return cursor to 0,0
    printf("\033[?25l");    //disable cursor
    printf("Press T to switch LED Logic, D to switch debug\n");
    printf("Positive logic: %d\n", positive_logic);
    printf("Debug: %d\n", debug);    
}

void clearline()
{
    printf("\033[0;1f");    //return cursor to 0,0
}


void Led_Callback()
{
    BuiltIn_LED_Toggle();
    LED_ref_Toggle();
    ADCC_DefineSetPoint(LED_ref_LAT?4095:0);
    ADCC_DischargeSampleCapacitor();
    ADCC_GetSingleConversion(LED_ref);
    if(debug == true)
    {
        printf("LED Lat %d\n", LED_ref_LAT);
        printf("ADC Result %d\n", ADCC_GetConversionResult());
        printf("SetPoint %d\n", LED_ref_LAT?4095:0);
        printf("Error %d\n", ADCC_GetErrorCalculation());
        printf("Upper %d\n", ADCC_HasErrorCrossedUpperThreshold());
        printf("Lower %d\n", ADCC_HasErrorCrossedLowerThreshold());
        printf("**********\n");
    }
}

void Led_ThresholdISR()
{
    printf("LED always off!\n");    
}

void setThresholds()
{
    // Normal Operation if Error > Upper or Error < Lower
    if(positive_logic)
    {
        ADCC_SetUpperThreshold((uint16_t)-1);
        ADCC_SetLowerThreshold((uint16_t)-100);
    }
    else
    {
        ADCC_SetUpperThreshold(20);
        ADCC_SetLowerThreshold(1);
    }
}

int main(void)
{
    SYSTEM_Initialize();
    
    // Builtin LED has negative logic
    BuiltIn_LED_SetLow();
    LED_ref_LAT = positive_logic;
    LED_ref_SetDigitalOutput();         
    setThresholds();
    
    Timer0_OverflowCallbackRegister(Led_Callback);
    ADCC_SetADTIInterruptHandler(Led_ThresholdISR);

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 
    
    printHeader();

    while(1)
    {
        if(UART1_IsRxReady())
        {
            uint8_t command = UART1_Read();
            switch(command)
            {
                case 'T': 
                    positive_logic ^= 1;
                    printf("Switch Logic - Positive:%d\n", positive_logic);
                    setThresholds();
                    break;
                case 'D':
                    debug ^= 1;
                    printf("Debug: %d\n", debug);
                    break;
                default: break;
            }
        }
    }    
}