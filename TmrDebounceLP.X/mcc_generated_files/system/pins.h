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
 * @version Driver Version  3.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

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

// get/set IO_RA0 aliases
#define SW0_TRIS                 TRISAbits.TRISA0
#define SW0_LAT                  LATAbits.LATA0
#define SW0_PORT                 PORTAbits.RA0
#define SW0_WPU                  WPUAbits.WPUA0
#define SW0_OD                   ODCONAbits.ODCA0
#define SW0_ANS                  ANSELAbits.ANSA0
#define SW0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define SW0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define SW0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define SW0_GetValue()           PORTAbits.RA0
#define SW0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define SW0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define SW0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define SW0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define SW0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define SW0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define SW0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define SW0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)
#define RA0_SetInterruptHandler  SW0_SetInterruptHandler
// get/set IO_RA1 aliases
#define LED0_TRIS                 TRISAbits.TRISA1
#define LED0_LAT                  LATAbits.LATA1
#define LED0_PORT                 PORTAbits.RA1
#define LED0_WPU                  WPUAbits.WPUA1
#define LED0_OD                   ODCONAbits.ODCA1
#define LED0_ANS                  ANSELAbits.ANSA1
#define LED0_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED0_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED0_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED0_GetValue()           PORTAbits.RA1
#define LED0_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED0_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED0_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define LED0_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define LED0_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define LED0_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define LED0_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define LED0_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
// get/set IO_RB4 aliases
#define IO_RB4_TRIS                 TRISBbits.TRISB4
#define IO_RB4_LAT                  LATBbits.LATB4
#define IO_RB4_PORT                 PORTBbits.RB4
#define IO_RB4_WPU                  WPUBbits.WPUB4
#define IO_RB4_OD                   ODCONBbits.ODCB4
#define IO_RB4_ANS                  ANSELBbits.ANSB4
#define IO_RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_RB4_GetValue()           PORTBbits.RB4
#define IO_RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_RB4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_RB4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_RB4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_RB4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_RB4_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IO_RB4_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)
// get/set IO_RB5 aliases
#define IO_RB5_TRIS                 TRISBbits.TRISB5
#define IO_RB5_LAT                  LATBbits.LATB5
#define IO_RB5_PORT                 PORTBbits.RB5
#define IO_RB5_WPU                  WPUBbits.WPUB5
#define IO_RB5_OD                   ODCONBbits.ODCB5
#define IO_RB5_ANS                  ANSELBbits.ANSB5
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
#define IO_RB5_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define IO_RB5_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)
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

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the SW0 pin functionality
 * @param none
 * @return none
 */
void SW0_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for SW0 pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for SW0 at application runtime.
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void SW0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for SW0 pin.
 *        This is a dynamic interrupt handler to be used together with the SW0_SetInterruptHandler() method.
 *        This handler is called every time the SW0 ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*SW0_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for SW0 pin. 
 *        This is a predefined interrupt handler to be used together with the SW0_SetInterruptHandler() method.
 *        This handler is called every time the SW0 ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void SW0_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/