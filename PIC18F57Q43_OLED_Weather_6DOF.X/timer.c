/*
 * File:   timer.c
 * Author: M71906
 *
 * Created on January 19, 2023, 11:49 AM
 */


#include <xc.h>
#include "timer.h"

unsigned long millis = 0;

void TIMER_Callback(void)
{
    millis++;
}
    
unsigned long TIMER_getCurrentMillis()
{
    return millis;
}