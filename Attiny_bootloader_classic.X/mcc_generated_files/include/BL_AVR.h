/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef BL_AVR_H_
#define BL_AVR_H_

#include <stdint.h>
#include <avr/io.h>

#define  READ_VERSION                           (0)
#define  READ_FLASH                             (1)
#define  WRITE_FLASH                            (2)
#define  ERASE_FLASH                            (3)
#define  READ_EE_DATA                           (4)
#define  WRITE_EE_DATA                          (5)
#define  READ_CONFIG                            (6)
#define  WRITE_STATUS                           (7)
#define  CALC_CHECKSUM                          (8)
#define  RESET_DEVICE                           (9)


#define ERROR_INVALID_COMMAND                   (0xFF)
#define ERROR_ADDRESS_OUT_OF_RANGE              (0xFE)
#define COMMAND_PROCESSED_SUCCESSFULLY          (0x01)
#define COMMAND_PROCESSED_SUCCESSFULLY_SPECIAL  (0x02)
#define COMMAND_PROCESSING_ERROR                (0xFD)

#define IO_ENTRY_PIN_RUN_BL                     (0)
#define BL_HEADER                               (9)

#define  BL_INDICATOR_ON()                      BL_INDICATOR_SetLow()
#define  BL_INDICATOR_OFF()                     BL_INDICATOR_SetHigh()

#define  BOOTLOADER_ENTRY_IO()                  BL_ENTRY_GetValue()
#define  IO_PIN_ENTRY_RUN_APP                   (1)
#define  IO_PIN_ENTRY_RUN_BL                    (0)

typedef union
{
    struct
    {
        uint8_t     command;
        uint16_t    data_length;
        uint8_t     EE_key_1;
        uint8_t     EE_key_2;
        uint8_t     address_L;
        uint8_t     address_H;
        uint8_t     address_U;
        uint8_t     address_E;
        uint8_t     data[PROGMEM_PAGE_SIZE];
    };
    uint8_t  buffer[PROGMEM_PAGE_SIZE + BL_HEADER];
}frame_t;

void BL_BOOTLOADER_Initialize(void);

#endif /* BL_AVR_H_ */