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

// get/set RB1 aliases
#define IO_RB1_TRIS                 TRISBbits.TRISB1
#define IO_RB1_LAT                  LATBbits.LATB1
#define IO_RB1_PORT                 PORTBbits.RB1
#define IO_RB1_WPU                  WPUBbits.WPUB1
#define IO_RB1_OD                   ODCONBbits.ODCB1
#define IO_RB1_ANS                  ANSELBbits.ANSELB1
#define IO_RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define IO_RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define IO_RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define IO_RB1_GetValue()           PORTBbits.RB1
#define IO_RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define IO_RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define IO_RB1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define IO_RB1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define IO_RB1_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define IO_RB1_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define IO_RB1_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define IO_RB1_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)
   
// get/set RB2 aliases
#define IO_RB2_TRIS                 TRISBbits.TRISB2
#define IO_RB2_LAT                  LATBbits.LATB2
#define IO_RB2_PORT                 PORTBbits.RB2
#define IO_RB2_WPU                  WPUBbits.WPUB2
#define IO_RB2_OD                   ODCONBbits.ODCB2
#define IO_RB2_ANS                  ANSELBbits.ANSELB2
#define IO_RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define IO_RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define IO_RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define IO_RB2_GetValue()           PORTBbits.RB2
#define IO_RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define IO_RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define IO_RB2_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define IO_RB2_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define IO_RB2_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define IO_RB2_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define IO_RB2_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define IO_RB2_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)
   
// get/set RB3 aliases
#define OLED_DATA_TRIS                 TRISBbits.TRISB3
#define OLED_DATA_LAT                  LATBbits.LATB3
#define OLED_DATA_PORT                 PORTBbits.RB3
#define OLED_DATA_WPU                  WPUBbits.WPUB3
#define OLED_DATA_OD                   ODCONBbits.ODCB3
#define OLED_DATA_ANS                  ANSELBbits.ANSELB3
#define OLED_DATA_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define OLED_DATA_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define OLED_DATA_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define OLED_DATA_GetValue()           PORTBbits.RB3
#define OLED_DATA_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define OLED_DATA_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define OLED_DATA_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define OLED_DATA_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define OLED_DATA_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define OLED_DATA_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define OLED_DATA_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define OLED_DATA_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)
   
// get/set RB5 aliases
#define IO_RB5_TRIS                 TRISBbits.TRISB5
#define IO_RB5_LAT                  LATBbits.LATB5
#define IO_RB5_PORT                 PORTBbits.RB5
#define IO_RB5_WPU                  WPUBbits.WPUB5
#define IO_RB5_OD                   ODCONBbits.ODCB5
#define IO_RB5_ANS                  ANSELBbits.ANSELB5
#define IO_RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IO_RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IO_RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IO_RB5_GetValue()           PORTBbits.RB5
#define IO_RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IO_RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define IO_RB5_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define IO_RB5_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define IO_RB5_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define IO_RB5_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define IO_RB5_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define IO_RB5_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)
   
// get/set RC4 aliases
#define IO_RC4_TRIS                 TRISCbits.TRISC4
#define IO_RC4_LAT                  LATCbits.LATC4
#define IO_RC4_PORT                 PORTCbits.RC4
#define IO_RC4_WPU                  WPUCbits.WPUC4
#define IO_RC4_OD                   ODCONCbits.ODCC4
#define IO_RC4_ANS                  ANSELCbits.ANSELC4
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_RC4_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_RC4_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define IO_RC4_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define IO_RC4_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define IO_RC4_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)
   
// get/set RC6 aliases
#define IO_RC6_TRIS                 TRISCbits.TRISC6
#define IO_RC6_LAT                  LATCbits.LATC6
#define IO_RC6_PORT                 PORTCbits.RC6
#define IO_RC6_WPU                  WPUCbits.WPUC6
#define IO_RC6_OD                   ODCONCbits.ODCC6
#define IO_RC6_ANS                  ANSELCbits.ANSELC6
#define IO_RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define IO_RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define IO_RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define IO_RC6_GetValue()           PORTCbits.RC6
#define IO_RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define IO_RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define IO_RC6_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define IO_RC6_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define IO_RC6_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define IO_RC6_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define IO_RC6_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define IO_RC6_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)
   
// get/set RC7 aliases
#define RST2_TRIS                 TRISCbits.TRISC7
#define RST2_LAT                  LATCbits.LATC7
#define RST2_PORT                 PORTCbits.RC7
#define RST2_WPU                  WPUCbits.WPUC7
#define RST2_OD                   ODCONCbits.ODCC7
#define RST2_ANS                  ANSELCbits.ANSELC7
#define RST2_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RST2_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RST2_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RST2_GetValue()           PORTCbits.RC7
#define RST2_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RST2_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RST2_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define RST2_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define RST2_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define RST2_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define RST2_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RST2_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)
   
// get/set RD6 aliases
#define CS2_TRIS                 TRISDbits.TRISD6
#define CS2_LAT                  LATDbits.LATD6
#define CS2_PORT                 PORTDbits.RD6
#define CS2_WPU                  WPUDbits.WPUD6
#define CS2_OD                   ODCONDbits.ODCD6
#define CS2_ANS                  ANSELDbits.ANSELD6
#define CS2_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define CS2_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define CS2_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define CS2_GetValue()           PORTDbits.RD6
#define CS2_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define CS2_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define CS2_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define CS2_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define CS2_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define CS2_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define CS2_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define CS2_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)
   
// get/set RE2 aliases
#define ACC_INT_TRIS                 TRISEbits.TRISE2
#define ACC_INT_LAT                  LATEbits.LATE2
#define ACC_INT_PORT                 PORTEbits.RE2
#define ACC_INT_WPU                  WPUEbits.WPUE2
#define ACC_INT_OD                   ODCONEbits.ODCE2
#define ACC_INT_ANS                  ANSELEbits.ANSELE2
#define ACC_INT_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define ACC_INT_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define ACC_INT_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define ACC_INT_GetValue()           PORTEbits.RE2
#define ACC_INT_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define ACC_INT_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define ACC_INT_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define ACC_INT_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define ACC_INT_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define ACC_INT_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define ACC_INT_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define ACC_INT_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)
   
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
#define LED_TRIS                 TRISFbits.TRISF3
#define LED_LAT                  LATFbits.LATF3
#define LED_PORT                 PORTFbits.RF3
#define LED_WPU                  WPUFbits.WPUF3
#define LED_OD                   ODCONFbits.ODCF3
#define LED_ANS                  ANSELFbits.ANSELF3
#define LED_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define LED_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define LED_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define LED_GetValue()           PORTFbits.RF3
#define LED_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define LED_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define LED_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELFbits.ANSELF3 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELFbits.ANSELF3 = 0; } while(0)
   
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