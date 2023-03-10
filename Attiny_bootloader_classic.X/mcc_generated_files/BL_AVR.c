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

#include "include/BL_AVR.h"
#include "mcc.h"
#include <stdlib.h>
#include <util/delay.h>
#include <stdbool.h>
#include <string.h>

/* Fuse configuration
* BOOTEND sets the size (end) of the boot section in blocks of 256 bytes.
* APPEND = 0x00 defines the section from BOOTEND*256 to end of Flash as application code.
* Remaining fuses have default configuration.
*/
// E.G. : FUSE.BOOTEND = 0x08 --> .text = 0x400 | .text = 800 [Offset App]
#define START_OF_APP                            (FUSE.BOOTEND * 256)

#define STX                                     (0x55)
#define	MINOR_VERSION                           (0x00)       
#define	MAJOR_VERSION                           (0x01)
#define NO_APPLICATION                          (0xFF)
#define APPLICATION_VALID                       (0x42)

#define CRC_RESULT                              (CRCSCAN_STATUS)
#define CRC_START_SCAN                          (1 << CRCSCAN_ENABLE_bp)

#define USART_rx_ready()                        USART0_IsRxReady()
#define USART_read()                            USART0_Read()
#define USART_write(data)                       USART0_Write(data)
#define USART_is_tx_busy()                      USART0_IsTxReady()

#define Read_Flash(adr)                         FLASH_ReadFlashByte(adr)
#define Write_Flash(adr, data, size, buf)       FLASH_WriteFlashBlock(adr, data, size, buf)
#define Erase_Flash(adr)                        FLASH_EraseFlashPage(adr)
#define Read_EEPROM(adr)                        FLASH_ReadEepromByte(adr)
#define Write_EEPROM(adr, data, size)           FLASH_WriteEepromBlock(adr, data, size)
#define Write_Status(adr, buf, data)            FLASH_WriteFlashByte(adr, buf, data)

typedef void(*app_t)(void);

static void BL_runBootloader(void);
static bool BL_Bootload_Required (void);
static void BL_checkResetDevice(void);

static uint8_t  BL_Get_Version_Data(void);
static uint8_t  BL_Read_Flash(void);
static uint8_t  BL_Write_Flash(void);
static uint8_t  BL_Erase_Flash(void);
static uint8_t  BL_Read_EE_Data(void);
static uint8_t  BL_Write_EE_Data(void);
static uint8_t  BL_Read_Config(void);
static uint8_t  BL_Write_App_Status(void);
static uint8_t  BL_Calc_Checksum(void);
static uint8_t  BL_Reset(void);
static uint8_t BL_ProcessBootBuffer (void);
static void BL_sendResponse(uint8_t msgLength);

static bool resetPending = false;
static bool capturedSynchByte = false;
static frame_t frame;

void BL_BOOTLOADER_Initialize (void)
{
    resetPending = false;
    /* Initialize system for AVR GCC support, expects r1 = 0 */
    asm("clr r1");

    BL_INDICATOR_OFF();
    if (BL_Bootload_Required())
    {
        _delay_ms(200);
        BL_INDICATOR_ON();
        BL_runBootloader();     // generic comms layer
    }

    app_t app = (app_t)(START_OF_APP / sizeof(app_t));
    app();	
}

// *****************************************************************************
static bool BL_Bootload_Required (void)
{
    // ******************************************************************
    //  Check an IO pin to force entry into bootloader
    // ******************************************************************

    // #info  "You may need to add additional delay here between enabling weak pullups and testing the pin."
    for (uint8_t i = 0; i != 0xFF; i++)
    {
        asm("nop");
    }

    if (BOOTLOADER_ENTRY_IO() == IO_ENTRY_PIN_RUN_BL)
    {
        return (true);
    }

    // ******************************************************************
    // Check the 'Reset Vector' reset vector for code to initiate bootloader
    // This section reads the application start (Reset Vector) which exist
    // on device at end of BOOT space. 
    // Check confirms (1st) byte of APPLICATION is BLANK (NO_APPLICATION). 
    // if (true) Bootloader will Run.
    // ******************************************************************
    if (Read_Flash(START_OF_APP) == NO_APPLICATION)
    {	
        return (true);
    }
    // ******************************************************************
    // Application is Valid | Release Bootloader control
    // ******************************************************************
    return (false);
}

static uint8_t  BL_ProcessBootBuffer(void)
{
    uint8_t   len;

    // ***********************************************
    // Test the command field and sub-command.
    // ***********************************************
    switch (frame.command)
    {
        case    READ_VERSION:
            len = BL_Get_Version_Data();
        break;
        case    READ_FLASH:
            len =  BL_Read_Flash();
        break;
        case    WRITE_FLASH:
            len = BL_Write_Flash();
        break;
        case    ERASE_FLASH:
            len = BL_Erase_Flash();
        break;
        case    READ_EE_DATA:
            len = BL_Read_EE_Data();
        break;
        case    WRITE_EE_DATA:
            len = BL_Write_EE_Data();
        break;
        case    READ_CONFIG:
            len = BL_Read_Config();
        break;
            case WRITE_STATUS:
            len = BL_Write_App_Status();
        break;
        case    CALC_CHECKSUM:
            frame.data[0] = ERROR_INVALID_COMMAND;
            len = BL_HEADER + 1;
        break;
        case    RESET_DEVICE:
            len = BL_Reset();
        break;
        default:
            frame.data[0] = ERROR_INVALID_COMMAND;
            len = BL_HEADER + 1;
        break;
    }
    return (len);
}

static void BL_runBootloader(void)
{
    uint8_t msg_length = 0;
    uint8_t index = 0;

    while (1)
    {		
        BL_checkResetDevice();
        index = 0;  //Point to the buffer
        msg_length = BL_HEADER;  // message has 9 bytes of overhead (Opcode + Length + Address)	
        memset(frame.buffer,0,sizeof(frame));	// Clear Buffer

        while(index < msg_length)
        {		
            frame.buffer[index] = USART_read();

            if (capturedSynchByte == true)		// Synch | AutoBaud captured; Process Data
            {
                index++;
                if (index == 5)
                {
                    if ((frame.command == WRITE_FLASH)
                    || (frame.command == WRITE_EE_DATA)
                    || (frame.command == WRITE_STATUS))
                    {
                        msg_length += frame.data_length;
                    }
                }
            }
            else
            {
                if (frame.buffer[index] == STX)         // Throwaway anything but Synch Byte | AutoBaud
                {
                    capturedSynchByte = true;		// Synch Byte | AutoBaud Ch captured
                }
            }
        }

        if (frame.command == WRITE_FLASH)
        {
            BL_checkResetDevice();
        }

        msg_length = BL_ProcessBootBuffer ();

        if (msg_length > 0)
        {
            BL_sendResponse(msg_length);            // Send Response
            while(USART_is_tx_busy());              // Wait to finish response

            index = 0;
            capturedSynchByte = false;              // Prepare for next message
            memset(frame.buffer,0,sizeof(frame));   // Clear Buffer
        }
    }
}

static void BL_checkResetDevice(void)
{
    if (resetPending)
    {
        _delay_ms(3);
        ccp_write_io((void *)&RSTCTRL.SWRR, RSTCTRL_SWRE_bm);
    }
}

static void BL_sendResponse(uint8_t msgLength)
{
    uint8_t index = 0;

    USART_write(STX);	// Send Synch Byte
    while (index < msgLength)
    {
        USART_write(frame.buffer[index++]);
    }
}

// ***********************************************
// Commands
// ***********************************************

// **************************************************************************************
// Get Bootloader Version Information
//        Cmd     Length----------------   Address---------------
// In:   [<0x00> <0x00><0x00><0x00><0x00> <0x00><0x00><0x00><0x00>]
// OUT:  [<0x00> <0x00><0x00><0x00><0x00> <0x00><0x00><0x00><0x00> <VERL><VERH>]
// ***********************************************
static uint8_t  BL_Get_Version_Data(void)
{
    uint8_t dataIndex = 0;
	
    volatile uint32_t memSize = PROGMEM_SIZE;
    volatile uint16_t pageSize = PROGMEM_PAGE_SIZE;
    volatile uint32_t partSize = 0;

    partSize = (memSize/((uint32_t)pageSize));

    frame.data[dataIndex++] = MINOR_VERSION;
    frame.data[dataIndex++] = MAJOR_VERSION;
    frame.data[dataIndex++] = BL_HEADER;
    frame.data[dataIndex++] = FUSE.BOOTEND;
    frame.data[dataIndex++] = FUSE.APPEND;
    frame.data[dataIndex++] =  (uint8_t)(partSize & 0xFF);
    frame.data[dataIndex++] =  (uint8_t)((partSize >> 8) & 0xFF);
    frame.data[dataIndex++] =  (uint8_t)((partSize >> 16) & 0xFF);
    frame.data[dataIndex++] =  (uint8_t)((partSize >> 24) & 0xFF);
    frame.data[dataIndex++] = SIGROW.DEVICEID0;
    frame.data[dataIndex++] = SIGROW.DEVICEID1;
    frame.data[dataIndex++] = SIGROW.DEVICEID2;
    frame.data[dataIndex++] = (uint8_t)(PROGMEM_PAGE_SIZE & 0xFF);
    frame.data[dataIndex++] = (uint8_t)((PROGMEM_PAGE_SIZE >> 8) & 0xFF);
    frame.data[dataIndex++] = SIGROW.SERNUM0;
    frame.data[dataIndex++] = SIGROW.SERNUM1;
    frame.data[dataIndex++] = SIGROW.SERNUM2;
    frame.data[dataIndex++] = SIGROW.SERNUM3;
    frame.data[dataIndex++] = SIGROW.SERNUM4;
    frame.data[dataIndex++] = SIGROW.SERNUM5;
    frame.data[dataIndex++] = SIGROW.SERNUM6;
    frame.data[dataIndex++] = SIGROW.SERNUM7;
    frame.data[dataIndex++] = SIGROW.SERNUM8;
    frame.data[dataIndex++] = SIGROW.SERNUM9;

    return  (BL_HEADER + dataIndex);   
}

// *********************************************************************************************************************
// Request Flash Read over range using Bootloader
// [<CMD><Data Length(Low, High) Bytes to Read><unused><unused><Address(Low,High,Upper,Extended)to Start Reading From>]
// IN: [<0x01><DataLengthL><DataLengthH><unused><unused><ADDRL><ADDRH><ADDRU><ADDRE>...]
// OUT: [<0x01><DataLengthL><DataLengthH><unused><unused><ADDRL><ADDRH><ADDRU><ADDRE><DATA>...]
// *********************************************************************************************************************
static uint8_t BL_Read_Flash(void)
{
    uint8_t dataIndex;
    uint16_t adr = ( ( (uint16_t)frame.address_H << 8) 
                    | frame.address_L);

    for (dataIndex = 0; dataIndex < frame.data_length; dataIndex++)
    {
        frame.data[dataIndex] = Read_Flash(adr);
        ++adr;
    }

    return (frame.data_length + BL_HEADER);
}

// ********************************************************************************************************************
// Request Flash Write over range, with supplied data using Bootloader
// [<CMD><Data Length(Low, High) Bytes to Write><unused><unused><Address(Low,High,Upper,Extended)to Start Writing To>]
// IN: [<0x02><DataLengthL><DataLengthH><unused><unused><ADDRL><ADDRH><ADDRU><ADDRE><DATA>...]
// OUT: [<0x02><DataLengthL><DataLengthH><unused><unused><ADDRL><ADDRH><ADDRU><ADDRE><STATUS_RESPONSE>...]
// ********************************************************************************************************************
static uint8_t BL_Write_Flash(void)
{
    nvmctrl_status_t status;
    uint8_t dataIndex = 0;
    uint16_t adr = ( ( (uint16_t)frame.address_H << 8) 
                    | frame.address_L);

    if (adr < START_OF_APP)
    {
        frame.data[dataIndex++] = ERROR_ADDRESS_OUT_OF_RANGE;
        return (BL_HEADER + dataIndex);
    }

    status = Write_Flash(adr, frame.data, frame.data_length, NULL);

    if (status != NVM_OK)
    {
        frame.data[dataIndex++] = COMMAND_PROCESSING_ERROR;
    }
    else
    {
        frame.data[dataIndex++] = COMMAND_PROCESSED_SUCCESSFULLY;
    }

    return (BL_HEADER + dataIndex);
}

// *********************************************************************************************************************
// Request Flash Memory Erase over range using Bootloader
// Erases data_length rows from program memory
// [<CMD><Data Length(Low, High) Bytes to Erase><unused><unused><Address(Low,High,Upper,Extended)to Start Erasing From>]
// IN: [<0x03><DataLengthL><DataLengthH><unused><unused><ADDRL><ADDRH><ADDRU><ADDRE>...]
// OUT: [<0x03><DataLengthL><DataLengthH><unused><unused><ADDRL><ADDRH><ADDRU><ADDRE><STATUS_RESPONSE>...]
// *********************************************************************************************************************
static uint8_t BL_Erase_Flash(void)
{
    nvmctrl_status_t status = NVM_BUSY;
    uint8_t dataIndex = 0;
    uint16_t adr = 0;

    adr = START_OF_APP;

    while (adr < FLASHEND)
    {
        status = Erase_Flash(adr);
        adr += PROGMEM_PAGE_SIZE;
    }

    if (status != NVM_OK)
    {
        frame.data[dataIndex++] = COMMAND_PROCESSING_ERROR;
    }
    else
    {
        frame.data[dataIndex++] = COMMAND_PROCESSED_SUCCESSFULLY_SPECIAL;
    }

    return (BL_HEADER + dataIndex);
}

// *********************************************************************************************************************
// Request Reading EEPROM data over range using Bootloader
// [<CMD><Data Length(Low, High) Bytes to Read><unused><unused><Address(Low,High,Upper,Extended)to Start Reading From>]
// IN: [<0x04><DataLengthL><DataLengthH><unused><unused><ADDRL><ADDRH><ADDRU><ADDRE>...]
// OUT: [<0x04><DataLengthL><DataLengthH><unused><unused><ADDRL><ADDRH><ADDRU><ADDRE><DATA>...]
// *********************************************************************************************************************
static uint8_t BL_Read_EE_Data(void)
{
    uint8_t dataIndex;
    uint8_t adr ;
    adr = frame.address_L;

    for (dataIndex = 0; dataIndex < frame.data_length; dataIndex++)
    {
        frame.data[dataIndex] = Read_EEPROM(adr);
        ++adr;
    }

    return (frame.data_length + BL_HEADER);
}

// ********************************************************************************************************************
// Request EEPROM Writing over range, with supplied data using Bootloader
// [<CMD><Data Length(Low, High) Bytes to Write><unused><unused><Address(Low,High,Upper,Extended)to Start Writing To>]
// IN: [<0x05><DataLengthL><DataLengthH><unused><unused><ADDRL><ADDRH><ADDRU><ADDRE><DATA>...]
// OUT: [<0x05><DataLengthL><DataLengthH><unused><unused><ADDRL><ADDRH><ADDRU><ADDRE><STATUS_RESPONSE>...]
// ********************************************************************************************************************
static uint8_t  BL_Write_EE_Data(void)
{
    nvmctrl_status_t status;
    uint8_t dataIndex = 0;

    uint8_t adr ;
    adr = frame.address_L;

    status = Write_EEPROM(adr, frame.data, frame.data_length);

    if (status != NVM_OK)
    {
        frame.data[dataIndex++] = COMMAND_PROCESSING_ERROR;
    }
    else
    {
        frame.data[dataIndex++] = COMMAND_PROCESSED_SUCCESSFULLY;
    }

    return (BL_HEADER + dataIndex);
}

// **************************************************************************************
// Request Read device FUSE setting using bootloader
// In:	[<0x06><DataLengthL><unused> <unused><unused> <ADDRL><ADDRH><ADDRU><unused>...]
// OUT:	[9 byte header + data ]
// **************************************************************************************
static uint8_t BL_Read_Config(void)
{
    uint8_t dataIndex = 0;
   
    frame.data[dataIndex++] = FUSE.WDTCFG;
    frame.data[dataIndex++] = FUSE.BODCFG;
    frame.data[dataIndex++] = FUSE.OSCCFG;
    frame.data[dataIndex++] = FUSE.reserved_1[0];
//    frame.data[dataIndex++] = FUSE.TCD0CFG;
    frame.data[dataIndex++] = FUSE.SYSCFG0;
    frame.data[dataIndex++] = FUSE.SYSCFG1;
    frame.data[dataIndex++] = FUSE.APPEND;
    frame.data[dataIndex++] = FUSE.BOOTEND;

// 9 byte header + data 
    return (BL_HEADER + dataIndex);           
}

// **************************************************************************************
// Request Wrtie device FUSE setting using bootloader
// In:	[<0x07><DataLengthL><unused> <unused><unused> <ADDRL><ADDRH><ADDRU><unused>...]
// OUT:	[9 byte header + Status]
// **************************************************************************************
static uint8_t BL_Write_App_Status (void)
{
    nvmctrl_status_t status;
    uint8_t dataIndex = 0;
    status = Write_Status(FLASHEND, NULL, frame.data[dataIndex]);

    if (status != NVM_OK)
    {
        frame.data[dataIndex++] = COMMAND_PROCESSING_ERROR;
    }
    else
    {
        frame.data[dataIndex++] = COMMAND_PROCESSED_SUCCESSFULLY;
    }
    return (BL_HEADER + dataIndex);           
}

// **************************************************************************************
// Calculate Checksum
// In:	[<0x08><DataLengthL><DataLengthH> <unused><unused> <ADDRL><ADDRH><ADDRU><unused>...]
// OUT:	[9 byte header + CRC_STATUS]
// **************************************************************************************
static uint8_t BL_Calc_Checksum(void)
{
    uint8_t dataIndex = 0;

    frame.data[dataIndex++] = CRC_RESULT;
    return (BL_HEADER + dataIndex);
}

// **************************************************************************************
// Reset
// In:   [<0x09> <0x00><0x00> <0x00><0x00> <0x00><0x00><0x00><0x00>]
// OUT:	[9 byte header] + [ChecksumL + ChecksumH]
// **************************************************************************************
static uint8_t BL_Reset(void)
{
    uint8_t dataIndex = 0;
    resetPending = true;
    frame.data[dataIndex ++] = COMMAND_PROCESSED_SUCCESSFULLY;
    return (BL_HEADER + dataIndex);
}