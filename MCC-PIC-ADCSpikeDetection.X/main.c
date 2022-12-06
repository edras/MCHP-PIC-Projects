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
volatile bool SEND_FRAME = false;

void ADCC_Callback_SpikeThreashold(void){
    DataStreamer.adcResult_lastSpike = ADCC_GetConversionResult();
    DataStreamer.adcSpikeCount++;
    LED_Toggle();
    DebugIO_Toggle();
    SEND_FRAME = true;
}

void Timer_Callback_100ms(void){
    ADCC_DischargeSampleCapacitor();         //Discharge capacitor voltage by connecting the VSS channel
    DataStreamer.adcResult =  ADCC_GetSingleConversion(POT);
    SEND_FRAME = true;
}


/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();
    
    DataStreamer.adcSpikeCount = 0;
    DataStreamer.adcResult_lastSpike = 0;
    DataStreamer.adcResult = 0;

    Timer->TimeoutCallbackRegister(Timer_Callback_100ms);
    ADCC_SetADTIInterruptHandler(ADCC_Callback_SpikeThreashold);
    INTERRUPT_GlobalInterruptEnable();

    while(1)
    {
        if(SEND_FRAME){
            WriteFrame();
            SEND_FRAME = false;
        }
    }
}

