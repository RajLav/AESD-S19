/*
 * Alert_Task.c
 *
 *  Created on: Apr 10, 2019
 *      Author: mentor
 */

#include "includes.h"
void Alert_Task(void *pvParameters)
{
    static struct structure_sent alert_info;
    while(1)
    {
        if(*((uint8_t*)pvParameters)==1)
        {
           taskENTER_CRITICAL();
          //strcpy(alert_info.string, "Alert");
          UARTprintf("Alert is there\n");
          *((uint8_t*)pvParameters)=0;
//
          taskEXIT_CRITICAL();
          //vTaskDelay(100);
        }
//        else
//        {
//            (*((uint8_t*)pvParameters)=0);
//        }

//        if(xQueueSend(log_q,(void *)&alert_info, 0) != pdTRUE)
//         {
//           UARTprintf("\nLog Error");
//         }

        vTaskDelay(100);
    }
}

