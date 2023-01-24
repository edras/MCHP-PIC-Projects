/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

#define TASK_FULL 0xFF

/* 
 * File:   tasks.h
 * Author: Dr. Edras Pacola
 * Comments: Tasks running at defined period in milliseconds. How to use it:
 *    1. Call Task_synch each 1 ms
 *    2. Register the task at program beginning or when needed.
 *    3. Call Task_execute inside the main loop
 *    To register a task:
 *      a. define a delay to start the task. delay = 0 start task immediately.
 *      b. define a reload time to repeat the task. reload = 0 execute the task
 *         only once and the resources for the task are released.
 *      c. pass a function pointer with no parameter and now return as a task.
 *         i.e.: void doSomething(void)
 *      Example: execute doSomething immediately and repeat it each 50ms:
 *      - Task_register(0, 50, doSomething);
 *      Example: execute doSomething after 100 ms and repeat it each 200ms:
 *      - Task_register(100, 200, doSomething);
 *      Example: execute doSomething only once after 200 ms:
 *      - Task_register(200, 0, doSomething);
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TASKS_H
#define	TASKS_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

void Task_execute(void);
void Task_delete(uint8_t task_idx);
void Task_modify(uint8_t task_idx, uint16_t reload);
void Task_synch(void);
uint8_t Task_register(uint16_t delay, uint16_t reload, void (* task)(void));


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* TASKS_H */

