/*
 * File:   timer.c
 * Author: M71906
 *
 * Created on January 19, 2023, 11:49 AM
 */


#include <xc.h>
#include <stddef.h>
#include "tasks.h"

#define MAX_TASKS 10

typedef struct {
    uint16_t delay;
    uint16_t reload;
    uint8_t trigger;
    void (*taskHandler)(void);
} Task;

Task tasks[MAX_TASKS];

void Task_synch(void)
{
    for(uint8_t i = 0; i<MAX_TASKS; i++)
    {
        if(tasks[i].taskHandler)
        {
            if(tasks[i].delay > 0) tasks[i].delay--;
            if(tasks[i].delay == 0)
            {
                tasks[i].delay = tasks[i].reload;
                tasks[i].trigger = 1;
            }            
        }
    }
}

uint8_t Task_register(uint16_t delay, uint16_t reload, void (* task)(void))
{
    for(uint8_t i = 0; i<MAX_TASKS; i++)
    {
        if(tasks[i].taskHandler == NULL)
        {
            tasks[i].delay = delay;
            tasks[i].reload = reload;
            tasks[i].trigger = 0;
            tasks[i].taskHandler = task;
            return i;
        }
    }
    return TASK_FULL;
}

void Task_delete(uint8_t task_idx)
{
    if(task_idx < MAX_TASKS)
    {
        tasks[task_idx].taskHandler = NULL;
        tasks[task_idx].trigger = 0;        
    }        
}

void Task_modify(uint8_t task_idx, uint16_t reload)
{
    if(task_idx < MAX_TASKS)
    {
        tasks[task_idx].reload = reload;
    }        
}

void Task_execute(void)
{
    for(uint8_t i = 0; i<MAX_TASKS; i++)
    {
        if(tasks[i].taskHandler && tasks[i].trigger)
        {
            tasks[i].trigger = 0;
            // if we have a valid function pointer, call the function
            if(tasks[i].taskHandler)
            {
                tasks[i].taskHandler();
            }            
            // if it is a single-run task, erase the function pointer
            if(tasks[i].reload == 0)
            {
                tasks[i].taskHandler = NULL;
            }
        }
    }    
}