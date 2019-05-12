/* FreeRTOS 8.2 Tiva Demo
 *
 * main.c
 *
 * Andy Kobyljanec
 * Reference : https://e2e.ti.com/support/microcontrollers/other/f/908/t/468677 for I2C communication
 * Demo Code of Timers from TI
 * if project shows negative temperature, try rebuilding the project after doing clean
 * This is a simple demonstration project of FreeRTOS 8.2 on the Tiva Launchpad
 * EK-TM4C1294XL.  TivaWare driverlib sourcecode is included.
 */

#include "includes.h"

uint8_t temp_var = 0;

int main(void)
{

    // Initialize system clock to 120 MHz
    uint32_t output_clock_rate_hz;
    output_clock_rate_hz = ROM_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),SYSTEM_CLOCK);
    ASSERT(output_clock_rate_hz == SYSTEM_CLOCK);
    // Initialize the GPIO pins for the Launchpad
    PinoutSet(0,0);
    uart_on(); //uart initialisation
    i2c_init(); //I2C initialisation by portb and temp i2c by address0x48
    xTaskCreate(logger, (const portCHAR *)"Logs",600, NULL, 1, NULL); //logger task initiated
    xTaskCreate(demoLEDTask, (const portCHAR *)"LEDs",600, NULL, 1, NULL); //led task initiated
    xTaskCreate(temp_task, (const portCHAR *)"Temp",600, (void*)&temp_var, 1, NULL); //temp task initiated
    xTaskCreate(Alert_Task, (const portCHAR *)"Alert",600, (void*)&temp_var, 1, NULL); //temp task initiated

    vTaskStartScheduler();
    return 0;
}


void __error__(char *pcFilename, uint32_t ui32Line)
{
    // Place a breakpoint here to capture errors until logging routine is finished
    while (1)
    {
    }
}

