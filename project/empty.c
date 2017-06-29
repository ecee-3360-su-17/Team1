/*
 *  ======== empty.c ========
 */

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SDSPI.h>
// #include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>

/* Board Header file */
#include "Board.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASKSTACKSIZE   768

Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];

Task_Struct task1Struct;
Char task1Stack[TASKSTACKSIZE];

Task_Struct senderFxnStruct;
Char senderFxnStack[TASKSTACKSIZE];

typedef struct MsgObj {
    char *val;            // Message value
} MsgObj, *Msg;

Void senderFxn(UArg arg0, UArg arg1)
{
    char input;
    UART_Handle uart;
    UART_Params uartParams;

    const char redMsg[] = "\fred LED is on\r\n";
    const char blueMsg[] = "\fblue LED is on\r\n";
    const char greenMsg[] = "\fgreen LED is on\r\n";
    const char onMsg[] = "\fgreen LED is on\r\n";
    const char offMsg[] = "\fgreen LED is on\r\n";

    const char message[] = "\fwelcome\r\n";


       /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    //uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 9600;
    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL) {
       System_abort("Error opening the UART");
    }

    UART_write(uart, message, sizeof(message));

    //Mailbox_Handle mbxHandle = (Mailbox_Handle)arg0;

    char *buffer = (char*)malloc(50);
    int cnt;

    while(1){    // While the input character is not empty...

            UART_read(uart, &input, 1);      // Read character from UART.
            UART_write(uart, &input, 1);
            if(input == '\r'){
                //UART_write(uart, redPrompt, sizeof(redPrompt));

                if(strcmp("red",buffer)){
                    UART_write(uart, redMsg, sizeof(redMsg));
                }
                if(strcmp("blue",buffer)){
                    UART_write(uart, blueMsg, sizeof(blueMsg));
                }
                if(strcmp("green",buffer)){
                    UART_write(uart, greenMsg, sizeof(greenMsg));
                }
                if(strcmp("on",buffer)){
                    UART_write(uart, onMsg, sizeof(onMsg));
                }
                if(strcmp("off",buffer)){
                    UART_write(uart, offMsg, sizeof(offMsg));
                }


                cnt = 0;
                free(buffer);
                buffer = (char*)malloc(50);

            }
            if(cnt < 50){
                //buffer[cnt] = input;            // Copy into out buffer.
                cnt++;                          // Increment count.
            }


    }

        //Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);

}

Void reciverFxn(UArg arg0, UArg arg1)
{
    Mailbox_Handle mbxHandle = (Mailbox_Handle)arg0;
    while (1) {
      MsgObj msg;
      Mailbox_pend(mbxHandle, &msg, BIOS_WAIT_FOREVER);
      //if(msg.val % 10 == 0)
        //exciting operation here for when val %10 == 0
    }
}




Void heartBeatFxn(UArg arg0, UArg arg1)
{
    while (1) {
        if((int)arg0 == 0){
            Task_sleep((UInt)1000);
            GPIO_toggle(Board_LED0);
        }
        if((int)arg0 == 1){
            Task_sleep((UInt)100);
            GPIO_toggle(Board_LED2);
        }
    }
}

Void echoFxn(UArg arg0, UArg arg1)
{
    char input;
    UART_Handle uart;
    UART_Params uartParams;
    const char echoPrompt[] = "\fEchoing characters:\r\n";

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 9600;
    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL) {
        System_abort("Error opening the UART");
    }

    UART_write(uart, echoPrompt, sizeof(echoPrompt));

    /* Loop forever echoing */
    while (1) {
        UART_read(uart, &input, 1);
        UART_write(uart, &input, 1);
    }
}



/*
 *  ======== main ========
 */
int main(void)
{
    //Task_Params taskParams;
    //Task_Params taskParams1;
    Task_Params senderFxnParams;

    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    // Board_initI2C();
    // Board_initSDSPI();
    // Board_initSPI();
    Board_initUART();
    // Board_initUSB(Board_USBDEVICE);
    // Board_initWatchdog();
    // Board_initWiFi();

    //senderFxn((UArg)1,(UArg)1);

    /* Construct heartBeat Task  thread
    Task_Params_init(&taskParams);
    taskParams.arg0 = 0;
    taskParams.instance->name = "heartbeat";
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task0Stack;
    Task_construct(&task0Struct, (Task_FuncPtr)heartBeatFxn, &taskParams, NULL);
    */

    /* Construct echoFxn Task thread
    Task_Params_init(&taskParams1);
    taskParams1.arg0 = 1;
    taskParams1.stackSize = TASKSTACKSIZE;
    taskParams1.stack = &task1Stack;
    Task_construct(&task1Struct, (Task_FuncPtr)heartBeatFxn, &taskParams1, NULL);
    */

    /* Construct senderFxn task thread */
    Task_Params_init(&senderFxnParams);
    senderFxnParams.arg0 = 1;
    senderFxnParams.stackSize = TASKSTACKSIZE;
    senderFxnParams.stack = &senderFxnStack;
    Task_construct(&senderFxnStruct, (Task_FuncPtr)senderFxn, &senderFxnParams, NULL);

    /* Turn on user LED */
    GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Starting the example\nSystem provider is set to SysMin. "
                  "Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
