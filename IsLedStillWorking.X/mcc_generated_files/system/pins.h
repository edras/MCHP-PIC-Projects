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
� [2022] Microchip Technology Inc. and its subsidiaries.

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
#define LED_ref_TRIS                 TRISAbits.TRISA0
#define LED_ref_LAT                  LATAbits.LATA0
#define LED_ref_PORT                 PORTAbits.RA0
#define LED_ref_WPU                  WPUAbits.WPUA0
#define LED_ref_OD                   ODCONAbits.ODCA0
#define LED_ref_ANS                  ANSELAbits.ANSELA0
#define LED_ref_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LED_ref_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LED_ref_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LED_ref_GetValue()           PORTAbits.RA0
#define LED_ref_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LED_ref_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LED_ref_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define LED_ref_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define LED_ref_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define LED_ref_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define LED_ref_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define LED_ref_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)
   
// get/set RA1 aliases
#define LED_drv_TRIS                 TRISAbits.TRISA1
#define LED_drv_LAT                  LATAbits.LATA1
#define LED_drv_PORT                 PORTAbits.RA1
#define LED_drv_WPU                  WPUAbits.WPUA1
#define LED_drv_OD                   ODCONAbits.ODCA1
#define LED_drv_ANS                  ANSELAbits.ANSELA1
#define LED_drv_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED_drv_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED_drv_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED_drv_GetValue()           PORTAbits.RA1
#define LED_drv_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED_drv_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED_drv_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define LED_drv_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define LED_drv_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define LED_drv_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define LED_drv_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define LED_drv_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)
   
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
#define BuiltIn_LED_TRIS                 TRISFbits.TRISF3
#define BuiltIn_LED_LAT                  LATFbits.LATF3
#define BuiltIn_LED_PORT                 PORTFbits.RF3
#define BuiltIn_LED_WPU                  WPUFbits.WPUF3
#define BuiltIn_LED_OD                   ODCONFbits.ODCF3
#define BuiltIn_LED_ANS                  ANSELFbits.ANSELF3
#define BuiltIn_LED_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define BuiltIn_LED_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define BuiltIn_LED_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define BuiltIn_LED_GetValue()           PORTFbits.RF3
#define BuiltIn_LED_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define BuiltIn_LED_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define BuiltIn_LED_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define BuiltIn_LED_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define BuiltIn_LED_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define BuiltIn_LED_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define BuiltIn_LED_SetAnalogMode()      do { ANSELFbits.ANSELF3 = 1; } while(0)
#define BuiltIn_LED_SetDigitalMode()     do { ANSELFbits.ANSELF3 = 0; } while(0)
   
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