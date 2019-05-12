/*
 * LedTask.c
 *
 *  Created on: Apr 10, 2019
 *      Author: mentor
 */


#include "includes.h"


void demoLEDTask(void *pvParameters)
{
   // UARTprintf("\nDemoLEDTask Started");
    //static uint8_t led_taskmanager=0;
    uint32_t cntr = 0;
    static uint8_t temperory_flag;
    temperory_flag = false;
    static struct structure_sent led_info;
    while(1)
    {
     // led_taskmanager = xTaskGetTickCount();
      if((xTaskGetTickCount()%50) == 0)
        {
            led_info.tick_function_return_value = xTaskGetTickCount();
            cntr = cntr + 1;
            led_info.state_change = cntr;
            strcpy(led_info.my_name, "RajLavingia");
            if(temperory_flag==true)
            {
                temperory_flag = false;
                LEDWrite(0x02, 0x02);
                LEDWrite(0x01, 0x01);
            }
            else
            {
                temperory_flag = true;
                LEDWrite(0x02, 0x00);
                LEDWrite(0x01, 0x00);
            }
            if(xQueueSend(log_q,(void *)&led_info, 0) != pdTRUE)
             {
               UARTprintf("\nLog Error");
             }

            vTaskDelay(1);
        }
    }
}
