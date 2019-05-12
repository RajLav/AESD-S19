/*
 * UartInitialisation.c
 *
 *  Created on: Apr 10, 2019
 *      Author: mentor
 */

#include "includes.h"

void uart_on()
{
    // Set up the UART which is connected to the virtual COM port
         UARTStdioConfig(0, 115200, SYSTEM_CLOCK);
}



