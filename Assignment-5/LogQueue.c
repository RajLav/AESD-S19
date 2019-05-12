/*
 * LogQueue.c
 *
 *  Created on: Apr 10, 2019
 *      Author: mentor
 */

#include "includes.h"

void logger(void *pvParameters)
{
    char Text_Print[200];
    static struct structure_sent log_info;
    log_q = xQueueCreate(10, sizeof(struct structure_sent));
    if(log_q == 0)
    {
     UARTprintf("\nLOG Queue Creation Failed");
    }
    else
    {
     UARTprintf("\nLOG Queue Created");
    }
    while(1)
    {
        if(xQueueReceive(log_q, (void *)&log_info, 100) == pdTRUE)
        {
            if(strcmp(log_info.my_name, "NULL") == 0)
            {
                snprintf(Text_Print, sizeof(Text_Print), "\nTempe: %f Ticks: %d", log_info.temperature_value, log_info.tick_function_return_value);
            }
            else
            {
                snprintf(Text_Print, sizeof(Text_Print), "\nName: %s Toggle: %d Ticks: %d", log_info.my_name, log_info.state_change, log_info.tick_function_return_value);
            }
            UARTprintf(Text_Print);
        }
    }
}


