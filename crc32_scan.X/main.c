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
#include "mcc_generated_files/system/system.h"
#include "inttypes.h"

/*
    Main application
*/
bool scan_ready = false;
uint16_t timer = 0;
uint16_t led_timer = 0;

void SCAN_CustomIntHandler(void)
{
    TMR1_Stop();
    scan_ready = true;
    CRC_StopScanner();
}

void TMR0_IntHandler(void)
{
    if(led_timer > 0) led_timer--;
    else
    {
        led_timer = 500;
        LED_Toggle();
    }
}

const uint8_t data8[] = {0x55, 0x66, 0x77, 0x88};
const uint16_t data16[] = {0x6C01, 0x9300};

void crc_shift8_data(void)
{
    // Enable the CRC module
    CRCCON0bits.CRCEN = 1;
    
    // Set initial remainder
    CRCCON0bits.SETUP = 0x00;   // Access to CRCOUT possible
    CRCOUTT = 0xFF;
    CRCOUTU = 0xFF;
    CRCOUTH = 0xFF;
    CRCOUTL = 0xFF;
    
    // Set the polynomial
    CRCCON0bits.SETUP = 0x02;   // Access to CRCXOR possible
    CRCXORT = 0x04;
    CRCXORU = 0xC1;
    CRCXORH = 0x1D;
    CRCXORL = 0xB7;
    
    CRCCON0bits.SETUP = 0x00;   // Restore access to CRCOUT
    
    CRCCON1bits.PLEN = 31;
    CRCCON2bits.DLEN = 7;       // 8 bits
    
    CRCCON0bits.ACCM = 1;       // data augmented with 0s
    CRCCON0bits.SHIFTM = 1;     // shift right
    CRCCON0bits.GO = 1;
    
    for(uint8_t  i=0; i < sizeof(data8) ; i++)
    {
        while(CRCCON0bits.FULL);        
        CRCDATAL = data8[i];
    }
    
    while(CRCCON0bits.BUSY);
    
    bool reverse_val = true;
    uint32_t xor_val = 0xFFFFFFFF;
    uint32_t result = CRC_GetCalculatedResult(reverse_val, xor_val);
    
    printf("data8: [0x55, 0x66, 0x77, 0x88]\n");
    printf("data8 CRC32 Result: 0x%08" PRIx32 "\n", result);
    printf("data8 CRCOUT: 0x%02x%02x%02x%02x\n\n", CRCOUTT, CRCOUTU, CRCOUTH, CRCOUTL);
 
}

void crc_shift16_data(void)
{
    // Enable the CRC module
    CRCCON0bits.CRCEN = 1;
    
    // Set initial remainder
    CRCCON0bits.SETUP = 0x00;   // Access to CRCOUT possible
    CRCOUTT = 0xFF;
    CRCOUTU = 0xFF;
    CRCOUTH = 0xFF;
    CRCOUTL = 0xFF;
    
    // Set the polynomial
    CRCCON0bits.SETUP = 0x02;   // Access to CRCXOR possible
    CRCXORT = 0x04;
    CRCXORU = 0xC1;
    CRCXORH = 0x1D;
    CRCXORL = 0xB7;
    
    CRCCON0bits.SETUP = 0x00;   // Restore access to CRCOUT
    
    CRCCON1bits.PLEN = 31;
    CRCCON2bits.DLEN = 0xF;     // 16 bits
    
    CRCCON0bits.ACCM = 1;       // data augmented with 0s
    CRCCON0bits.SHIFTM = 1;     // shift right
    CRCCON0bits.GO = 1;
    
    for(uint8_t  i=0; i<2 ; i++)
    {
        while(CRCCON0bits.FULL);        
        CRCDATAH = (data16[i] >> 8) & 0xFF;
        CRCDATAL = data16[i] & 0xFF;
    }
    
    while(CRCCON0bits.BUSY);
    
    bool reverse_val = true;
    uint32_t xor_val = 0xFFFFFFFF;
    uint32_t result = CRC_GetCalculatedResult(reverse_val, xor_val);
    
    printf("data16: [0x6C01, 0x9300]\n");
    printf("data16 CRC32 Result: 0x%08" PRIx32 "\n", result);
    printf("data16 CRCOUT: 0x%02x%02x%02x%02x\n\n", CRCOUTT, CRCOUTU, CRCOUTH, CRCOUTL); 
}

int main(void)
{
    SYSTEM_Initialize();
    
    TMR0_OverflowCallbackRegister(TMR0_IntHandler);

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 

    while(1)
    {
        if(SW0_GetValue() == 0)
        {
            printf("SW0 pressed!\n\n");
            while(SW0_GetValue() == 0);
            CRC_Initialize();
            CRC_SetScannerInterruptHandler(SCAN_CustomIntHandler);
            CRC_SetScannerAddressLimit(0x0000, 0x3FFB);
            TMR1_Start();
            CRC_StartScanner();
        }
        if(scan_ready)
        {
            scan_ready = false;
            uint32_t result = CRC_GetCalculatedResult(true, 0xFFFFFFFF);
            printf("Scan CRC Result: 0x%08" PRIx32 "\n", result);
            printf("Scan CRCOUT: 0x%02x%02x%02x%02x\n", CRCOUTT, CRCOUTU, CRCOUTH, CRCOUTL);
            uint32_t memory_crc = 0;
            for(uint8_t i=0; i<4; i++)
            {
                memory_crc <<= 8;                
                memory_crc |= FLASH_Read(0x3FFC + i) & 0xFF;
            }
            printf("CRC Stored in FLASH: 0x%08" PRIx32 "\n", memory_crc);
            printf("Time elapsed: %d ms \n\n", TMR1_Read());
            TMR1_Reload();
            crc_shift8_data();
            crc_shift16_data();
        }
    }    
}