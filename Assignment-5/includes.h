//Includes
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "drivers/pinout.h"
#include "utils/uartstdio.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "driverlib/fpu.h"

// TivaWare includes
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#include "i2cm_drv.h"
#include "driverlib/i2c.h"
#include "inc/hw_i2c.h"

// FreeRTOS includes
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


//Function Prototypes
void demoLEDTask(void *pvParameters);
void i2c_init();
void temp_task(void *pvParameters);
void logger(void *pvParameters);
void __error__(char *pcFilename, uint32_t ui32Line);
void Alert_Task(void *pvParameters);


struct structure_sent{
    char my_name[10];
    uint32_t tick_function_return_value;
    uint32_t state_change;
    float temperature_value;
    char string[40];
    uint32_t flag_temp;
};

uint8_t temperature_data_celsius[30];
QueueHandle_t log_q;
float Celsius;
extern uint8_t temp_var;
//extern uint32_t cntr;
