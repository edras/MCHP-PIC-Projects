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

/* Create a pointer of type TMR_INTERFACE and assign it to the address of the Timer0 TMR_INTERFACE struct.
This enables us to get access the portable API interface, which ensures that it's easy to change the peripheral instance the timer runs on. */
const struct TMR_INTERFACE *Timer = &Timer0;

#define TMR0_8BITS

#ifdef TMR0_8BITS
#define LED_100ms (0x2F)
#define LED_500ms (0xF1)
#else
#define LED_100ms (0xF3E4)
#define LED_500ms (0xC374)
#endif

volatile bool CHANGE_PERIOD = false;
volatile bool PERIOD_100ms = true;  /*Global variable to check the current period value*/

void Timer_Callback(void)
{
    LED_Toggle();
}

void SW_Callback(void)
{
    CHANGE_PERIOD = true;
}

void Timer_Change_Frequency(void){
    Timer->Stop();
    if(PERIOD_100ms)
    {
        TMR0 = 0x0;   //Restart the timer
        Timer->PeriodCountSet(LED_500ms);
        PERIOD_100ms = false;
    }
    else
    {
        TMR0 = 0x0;   //Restart the timer
        Timer->PeriodCountSet(LED_100ms);
        PERIOD_100ms = true;
    }
    Timer->Start();
}

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();
    Timer->TimeoutCallbackRegister(Timer_Callback);
    RB4_SetInterruptHandler(SW_Callback);             /* Select for SW pin you are using */
    
    INTERRUPT_GlobalInterruptEnable();
    
    while(1)
    {
        if(CHANGE_PERIOD)
        {
            Timer_Change_Frequency();
            __delay_ms(100);    //De-bounce delay
            CHANGE_PERIOD = false;
        }
    }
}

