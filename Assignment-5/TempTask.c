/*
 * TempTask.c
 *
 *  Created on: Apr 10, 2019
 *      Author: mentor
 */




#include "includes.h"

void temp_task(void *pvParameters)
{
   // UARTprintf("\nDemoTempTask Started");
    {
      static struct structure_sent temp_info;
      while(1)
        {
            if((xTaskGetTickCount())%1000 == 0)
            {
                temp_info.tick_function_return_value = xTaskGetTickCount();
                strcpy(temp_info.my_name, "NULL");
                Temperature_Final_Value(&Celsius);
                temp_info.temperature_value = Celsius;
                taskENTER_CRITICAL();
                   if(temp_info.temperature_value > 25.0000)
                   {

                     *((uint8_t*)pvParameters)=1;
                   }
                   else //if(temp_info.temperature_value <= 25.0000)
                   {
                       *((uint8_t*)pvParameters)=0;
                   }
                   taskEXIT_CRITICAL();
                if(xQueueSend(log_q,(void *)&temp_info, 0) != pdTRUE)
                {
                    UARTprintf("\nLog Error");
                }

                vTaskDelay(1);
            }
        }
    }
}


void Temperature_Final_Value(float *temp_final_Celsius)
{

    static struct structure_sent temp_info;
    ROM_I2CMasterSlaveAddrSet(I2C2_BASE, 0x48, true); //address of temp sensor
    ROM_I2CMasterDataPut(I2C2_BASE, 0x00); //in order to read from reg
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while(!ROM_I2CMasterBusy(I2C2_BASE));
    while(ROM_I2CMasterBusy(I2C2_BASE));
    temperature_data_celsius[0] = (uint8_t)ROM_I2CMasterDataGet(I2C2_BASE);
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
    temperature_data_celsius[1] = (uint8_t)ROM_I2CMasterDataGet(I2C2_BASE);
    ROM_I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    *temp_final_Celsius = (((temperature_data_celsius[0] << 8) | temperature_data_celsius[1]) >> 4) * 0.0625;
    temp_info.temperature_value = Celsius;
    float Temp_Fehrenheit = (*temp_final_Celsius * 1.8) + 32;
    float Temp_Kelvin = *temp_final_Celsius + 273.15;
   // UARTprintf("\n Temperature Value is %f",*temp_final_Celsius);


}
