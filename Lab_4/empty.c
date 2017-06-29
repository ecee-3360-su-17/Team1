
/*============================*/
/*           empty.c          */
/*============================*/

/* XDCtools header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>

/* TI-RTOS header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Board header file */
#include "Board.h"

/* Other headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definitions */
#define TASKSTACKSIZE 768
#define NUMMSGS 3

/* Declare task structs */
Task_Struct senderFxnStruct;        // Sender function
Char senderFxnStack[TASKSTACKSIZE];
Task_Struct recieverFxnStruct;      // Reciever function
Char recieverFxnStack[TASKSTACKSIZE];

/* Message struct definition */
typedef struct MsgObj {
    int val;            // Message value is an integer code
} MsgObj, *Msg;

Void senderFxn(UArg arg0, UArg arg1)
{
    /* Messages */
    const char redMsg[] = "\fRed LED toggled\r\n";
    const char blueMsg[] = "\fBlue LED toggled\r\n";
    const char greenMsg[] = "\fGreen LED toggled\r\n";
    const char onMsg[] = "\fLEDs are on\r\n";
    const char offMsg[] = "\fLEDs are off\r\n";
    const char message[] = "\fEnter a command: \r\n";

    char input;         // Used to store UART input
    UART_Handle uart;
    UART_Params uartParams;

    /* Create a UART */
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

    UART_write(uart, message, sizeof(message));     // Opening message

    Mailbox_Handle mbxHandle = (Mailbox_Handle)arg0;

    char *buffer = (char*)malloc(5);    // Allocate memory for buffer
    int cnt = 0;                        // Initialize counter to zero

    while(1){    // While the input character is not empty...

        UART_read(uart, &input, 1);      // Read character from UART.
        UART_write(uart, &input, 1);
        if(input == '\r'){
            /* RED */
            if(!strcmp("red",buffer)){
                UART_write(uart, redMsg, sizeof(blueMsg));
                MsgObj msg;
                msg.val = 0;
                Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);
            }
            /* BLUE */
            if(!strcmp("blue",buffer)){
                UART_write(uart, blueMsg, sizeof(blueMsg));
                MsgObj msg;
                msg.val = 1;
                Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);
            }
            /* GREEN */
            if(!strcmp("green",buffer)){
                UART_write(uart, greenMsg, sizeof(greenMsg));
                MsgObj msg;
                msg.val = 2;
                Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);
            }
            /* ON */
            if(!strcmp("on",buffer)){
                UART_write(uart, onMsg, sizeof(onMsg));
                MsgObj msg;
                msg.val = 4;
                Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);
            }
            /* OFF */
            if(!strcmp("off",buffer)){
                UART_write(uart, offMsg, sizeof(offMsg));
                MsgObj msg;
                msg.val = 3;
                Mailbox_post(mbxHandle, &msg, BIOS_WAIT_FOREVER);
            }

            /* Reset buffer */
            cnt = 0;
            buffer = (char*)calloc(5,sizeof(char*));    // Allocate and clear

        }
        else if((cnt < 5)){
            buffer[cnt] = input;    // Copy into out buffer.
            cnt++;                  // Increment count.
        }
    }

}

/* Function to receive messages from mailbox and control LEDs */
Void recieverFxn(UArg arg0, UArg arg1)
{

    Mailbox_Handle mbxHandle = (Mailbox_Handle)arg0;
    while(1){
        MsgObj msg;
        Mailbox_pend(mbxHandle, &msg, BIOS_WAIT_FOREVER);
        /* RED */
        if(msg.val == 0) GPIO_toggle(Board_LED2);
        /* BLUE */
        if(msg.val == 1) GPIO_toggle(Board_LED0);
        /* GREEN */
        if(msg.val == 2) GPIO_toggle(Board_LED1);
        /* ON */
        if(msg.val == 3){
            GPIO_write(Board_LED0,0x0);
            GPIO_write(Board_LED1,0x0);
            GPIO_write(Board_LED2,0x0);
        }
        /* OFF */
        if(msg.val == 4){
            GPIO_write(Board_LED0,1);
            GPIO_write(Board_LED1,1);
            GPIO_write(Board_LED2,1);
        }

    }

}

/*============= main ============*/

int main(void)
{
    Task_Params senderFxnParams;
    Task_Params recieverFxnParams;

    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    Board_initUART();

    Mailbox_Struct mbxStruct;

    Mailbox_Params mbxParams;
    Mailbox_Params_init(&mbxParams);
    Mailbox_construct(&mbxStruct,sizeof(MsgObj), 2, &mbxParams, NULL);

    Mailbox_Handle mbxHandle = Mailbox_handle(&mbxStruct);


    Task_Params_init(&senderFxnParams);
    senderFxnParams.arg0 = (UArg)mbxHandle;
    senderFxnParams.stackSize = TASKSTACKSIZE;
    senderFxnParams.stack = &senderFxnStack;
    Task_construct(&senderFxnStruct, (Task_FuncPtr)senderFxn, &senderFxnParams, NULL);

    Task_Params_init(&recieverFxnParams);
    recieverFxnParams.arg0 = (UArg)mbxHandle;
    recieverFxnParams.stackSize = TASKSTACKSIZE;
    recieverFxnParams.stack = &recieverFxnStack;
    Task_construct(&recieverFxnStruct, (Task_FuncPtr)recieverFxn, &recieverFxnParams, NULL);


    /* Turn on user LED */
    //GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Starting the example\nSystem provider is set to SysMin. "
                  "Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
