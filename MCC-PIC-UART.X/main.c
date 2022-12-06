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
#include <string.h>

#define MAX_COMMAND_LEN 8



/* Add the code snippet to the application code, e.g. main.c */
void UART_print_loop(uint8_t count)
{
    int i;
    for(i = 0; i < count; i++)
    {
        printf("%d. Hello World!\n",i);
    }
}

char msg[] = "Hello World!\r\n";
void UART_write_string(const char *msg)
{
    for(uint8_t i = 0; i < strlen(msg); i++)
    {
        while(!UART.IsTxReady());
        UART.Write(msg[i]);
    }
}

void UART_executeCommand(char *command)
{
    if(strcmp(command, "ON") == 0)
    {
        LED_SetLow();
        printf("OK, LED ON.\r\n");
    }
    else if (strcmp(command, "OFF") == 0)
    {
        LED_SetHigh();
        printf("OK, LED OFF.\r\n");
    }
    else
    {
        printf("Incorrect command.\r\n");
    }
}



/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 
    
    
    UART_print_loop(5); 
    UART_write_string(msg);
    UART_write_string("Hello there Curiosity Nano!\r\n");

    char command[MAX_COMMAND_LEN];
    uint8_t index = 0;
    char c;
    
    printf("In the terminal, send 'ON' to turn the LED on, and 'OFF' to turn it off.\r\n");
    printf("Note: commands 'ON' and 'OFF' are case sensitive.\r\n");
    
    while(1)
    {        
        while(!UART.IsRxReady());
        c = UART.Read();
        if(c != '\n' && c != '\r')
        {
            command[index++] = c;
            if((index) > MAX_COMMAND_LEN)
        {
            (index) = 0;
            }
        }
        if(c == '\n')
        {
            command[index] = '\0';
            index = 0;
            UART_executeCommand(command);
        }
    }


  
}