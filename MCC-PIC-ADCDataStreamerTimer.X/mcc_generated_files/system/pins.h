/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.0
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 aliases
#define POT_TRIS                 TRISAbits.TRISA0
#define POT_LAT                  LATAbits.LATA0
#define POT_PORT                 PORTAbits.RA0
#define POT_WPU                  WPUAbits.WPUA0
#define POT_OD                   ODCONAbits.ODCA0
#define POT_ANS                  ANSELAbits.ANSELA0
#define POT_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define POT_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define POT_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define POT_GetValue()           PORTAbits.RA0
#define POT_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define POT_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define POT_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define POT_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define POT_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define POT_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define POT_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define POT_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)
   
// get/set RB4 aliases
#define LED_TRIS                 TRISBbits.TRISB4
#define LED_LAT                  LATBbits.LATB4
#define LED_PORT                 PORTBbits.RB4
#define LED_WPU                  WPUBbits.WPUB4
#define LED_OD                   ODCONBbits.ODCB4
#define LED_ANS                  ANSELBbits.ANSELB4
#define LED_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define LED_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define LED_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define LED_GetValue()           PORTBbits.RB4
#define LED_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define LED_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define LED_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)
   
// get/set RF0 aliases
#define IO_RF0_TRIS                 TRISFbits.TRISF0
#define IO_RF0_LAT                  LATFbits.LATF0
#define IO_RF0_PORT                 PORTFbits.RF0
#define IO_RF0_WPU                  WPUFbits.WPUF0
#define IO_RF0_OD                   ODCONFbits.ODCF0
#define IO_RF0_ANS                  ANSELFbits.ANSELF0
#define IO_RF0_SetHigh()            do { LATFbits.LATF0 = 1; } while(0)
#define IO_RF0_SetLow()             do { LATFbits.LATF0 = 0; } while(0)
#define IO_RF0_Toggle()             do { LATFbits.LATF0 = ~LATFbits.LATF0; } while(0)
#define IO_RF0_GetValue()           PORTFbits.RF0
#define IO_RF0_SetDigitalInput()    do { TRISFbits.TRISF0 = 1; } while(0)
#define IO_RF0_SetDigitalOutput()   do { TRISFbits.TRISF0 = 0; } while(0)
#define IO_RF0_SetPullup()          do { WPUFbits.WPUF0 = 1; } while(0)
#define IO_RF0_ResetPullup()        do { WPUFbits.WPUF0 = 0; } while(0)
#define IO_RF0_SetPushPull()        do { ODCONFbits.ODCF0 = 0; } while(0)
#define IO_RF0_SetOpenDrain()       do { ODCONFbits.ODCF0 = 1; } while(0)
#define IO_RF0_SetAnalogMode()      do { ANSELFbits.ANSELF0 = 1; } while(0)
#define IO_RF0_SetDigitalMode()     do { ANSELFbits.ANSELF0 = 0; } while(0)
   
// get/set RF1 aliases
#define IO_RF1_TRIS                 TRISFbits.TRISF1
#define IO_RF1_LAT                  LATFbits.LATF1
#define IO_RF1_PORT                 PORTFbits.RF1
#define IO_RF1_WPU                  WPUFbits.WPUF1
#define IO_RF1_OD                   ODCONFbits.ODCF1
#define IO_RF1_ANS                  ANSELFbits.ANSELF1
#define IO_RF1_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define IO_RF1_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define IO_RF1_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define IO_RF1_GetValue()           PORTFbits.RF1
#define IO_RF1_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define IO_RF1_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define IO_RF1_SetPullup()          do { WPUFbits.WPUF1 = 1; } while(0)
#define IO_RF1_ResetPullup()        do { WPUFbits.WPUF1 = 0; } while(0)
#define IO_RF1_SetPushPull()        do { ODCONFbits.ODCF1 = 0; } while(0)
#define IO_RF1_SetOpenDrain()       do { ODCONFbits.ODCF1 = 1; } while(0)
#define IO_RF1_SetAnalogMode()      do { ANSELFbits.ANSELF1 = 1; } while(0)
#define IO_RF1_SetDigitalMode()     do { ANSELFbits.ANSELF1 = 0; } while(0)
   
// get/set RF3 aliases
#define DebugIO_TRIS                 TRISFbits.TRISF3
#define DebugIO_LAT                  LATFbits.LATF3
#define DebugIO_PORT                 PORTFbits.RF3
#define DebugIO_WPU                  WPUFbits.WPUF3
#define DebugIO_OD                   ODCONFbits.ODCF3
#define DebugIO_ANS                  ANSELFbits.ANSELF3
#define DebugIO_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define DebugIO_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define DebugIO_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define DebugIO_GetValue()           PORTFbits.RF3
#define DebugIO_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define DebugIO_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define DebugIO_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define DebugIO_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define DebugIO_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define DebugIO_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define DebugIO_SetAnalogMode()      do { ANSELFbits.ANSELF3 = 1; } while(0)
#define DebugIO_SetDigitalMode()     do { ANSELFbits.ANSELF3 = 0; } while(0)
   
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/