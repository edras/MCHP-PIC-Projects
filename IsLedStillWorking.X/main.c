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

/*
    Main application
*/

bool positive_logic = true;
bool debug = false;
bool printInfo = false;

int16_t offset = 0;
int16_t gain = 0;
int8_t temperature = 20;
char ledError = 0;
float rdsOn = 40;

#define P_Current_num (3.3/4095)
#define P_Current_den 0.00498
#define N_Current (3.3/4095)/0.00548

typedef struct{
    uint8_t  latState   :1;
    uint8_t  upperCross :1;
    uint8_t  lowerCross :1;
    uint16_t adcResult;
    int16_t  error;
    int16_t  setPoint;
    int16_t  upperThreshold;
    int16_t  lowerThreshold;
} ADC_DATA;

ADC_DATA adcData;

void printHeader(void)
{
    printf("\033[2J");      //Clear screen
    printf("\033[0;0f");    //return cursor to 0,0
    printf("\033[?25l");    //disable cursor
    
    printf("------------------------------------------------------------------\r\n");
    printf("PIC18F57Q43 Curiosity Development Board Demo                      \r\n");
    printf("SingleWire LED verification                                       \r\n");
    printf("------------------------------------------------------------------\r\n");
    printf("C - Clear screen \r\n");
    printf("D - Toggle Debug mode \r\n");
    printf("L - Toggle LED Logic \r\n");
    printf("\r\n");
}

static void printData(void)
{
    if(printInfo == false) return;
    printInfo = false;
    
    printf("\033[8;0f\n");    //move cursor to row 8, column 0 (after header)

    if(ledError > 0)
        printf("LED state: defect    \r\n");
    else
        printf("LED state: working   \r\n");
    printf("Positive logic: %d\r\n", positive_logic);
    printf("Temperature: %d   \r\n", temperature);    
    if(positive_logic)
        printf("P-MOS Rds_on: %.2f\r\n", rdsOn);
    else
        printf("N-MOS Rds_on: %.2f\r\n", rdsOn);
    
    if(debug)
    {
        printf("\n**********\n");
        printf("LED Lat %d\n", adcData.latState);
        printf("SetPoint %d      \n", adcData.setPoint);
        printf("ADC Result %d    \n", adcData.adcResult);
        printf("Error %d         \n\n", adcData.error);
        printf("Lower Threshold: %d      \n", adcData.lowerThreshold);
        printf("Crossed Lower Threshold: %d    \n", adcData.lowerCross);
        printf("**********\n");        
    }
}

void readDIAValues(void)
{
    gain = DeviceID_Read(DIA_TSHR1);
    offset = DeviceID_Read(DIA_TSHR3);
}

void calcTemperature(void)
{
    ADTIE = 0;
    ADREF |= 3;
    ADCON3bits_t tmpADCON = ADCON3bits;
    ADCON3bits.TMD = 0; // no threshold interrupt
    
    ADCC_GetSingleConversion(channel_Temp);
    int24_t temp = (int24_t)ADCC_GetConversionResult() * gain;
    temp /= 256;
    temp += offset;
    temperature = (int16_t)(temp / 10);
    
    ADCON3bits = tmpADCON;
    ADREF &= 0xFC;
    ADTIE = 1;
}

void Led_Callback()
{
    BuiltIn_LED_Toggle();
    LED_ref_Toggle();
    calcTemperature();
    if(ledError > 0) ledError--;
    printInfo = true;
    
    ADCC_DefineSetPoint(LED_ref_LAT?4095:0);
    ADCC_DischargeSampleCapacitor();
    if(positive_logic == LED_ref_LAT)
    {
        ADCC_GetSingleConversion(LED_ref);
        adcData.latState = LED_ref_LAT;
        adcData.setPoint = LED_ref_LAT?4095:0;
        adcData.adcResult = ADCC_GetConversionResult();
        adcData.error = (int16_t)ADCC_GetErrorCalculation();
        adcData.upperCross = ADCC_HasErrorCrossedUpperThreshold();
        adcData.lowerCross = ADCC_HasErrorCrossedLowerThreshold();
        if(positive_logic)
        {
            rdsOn = 3.3 - ((float)adcData.adcResult * P_Current_num);
            rdsOn /= P_Current_den; 
        }
        else 
            rdsOn = (float)adcData.adcResult * N_Current;
    }
}

void Led_ThresholdISR()
{
    ledError = 5;
}

void setThresholds()
{
    if(positive_logic)
    {
        adcData.lowerThreshold = -100;
        ADCON3bits.TMD = 2; // ADERR > ADLTH
    }
    else
    {
        adcData.lowerThreshold = 20;
        ADCON3bits.TMD = 1; // ADERR < ADLTH
    }
    ADCC_SetLowerThreshold((uint16_t)adcData.lowerThreshold);
}

int main(void)
{
    SYSTEM_Initialize();
    
    // Builtin LED has negative logic
    BuiltIn_LED_SetLow();
    LED_ref_LAT = positive_logic;
    LED_ref_SetDigitalOutput();         
    setThresholds();
    
    readDIAValues();
    Timer0_OverflowCallbackRegister(Led_Callback);
    ADCC_SetADTIInterruptHandler(Led_ThresholdISR);

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 
    
    printHeader();

    while(1)
    {
        if(UART1_IsRxReady())
        {
            uint8_t command = UART1_Read();
            switch(command)
            {
                case 'D':
                    debug ^= 1;
                case 'C':
                    printHeader();
                    printInfo = true;
                    break;
                case 'L': 
                    positive_logic ^= 1;
                    setThresholds();
                    break;
                default: break;
            }
        }
        printData();
    }    
}