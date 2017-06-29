/*************************************
    Filename:   main.c

    Creator:    Daniel Langevin, Yang Hu,
    Date:       2017

*************************************/

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define GREEN GPIO_PIN_3
#define BLUE GPIO_PIN_2
#define RED GPIO_PIN_1

extern int fib(int n);
void blink(int n, int color);
void blinkAll(int n);
char num2Morse(int n);


// Main function.
int main(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    int n = fib(24);    // Calculate the Fibonacci number
    blinkAll(n);        // Blink all the digits
    return 0;
}

// Function to blink every digit of an integer (base-10)
void blinkAll(int n){

    int x = n;
    int mag = 1;
    int color = 0;

    while(x > 0){
        x = x / 10;
        mag = mag * 10;
    }
    while(mag > 1){
        mag = mag / 10;
        x = n / mag;
        blink(x,color);         // Blink the digit
        n = n % mag;
        color = (color+1)%2;    // Toggle the color
    }
}

// Function that links a single digit in Morse code
void blink(int n, int color){

    volatile uint32_t ui32Loop;     // Loop counter
    int i;                          // Loop counter


    ;while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, BLUE|RED);

    char pattern = num2Morse(n);    // Convert the decimal digit into Morse code.

    // Loop through the 5 dots/dashes
    for(i = 0; i < 5; i++){

        int bit = pattern >> (4-i);     // Shift bits
        int state = bit & 0b1;          // Mask bits

        if(color == 1) GPIOPinWrite(GPIO_PORTF_BASE, BLUE, BLUE);   // Turn on blue LED
        else GPIOPinWrite(GPIO_PORTF_BASE, RED, RED);               // Turn on red LED

        if(state == 1){
            SysCtlDelay(4000000);      // Dash, so long wait...........
        }
        else{
            SysCtlDelay(1000000);      // Dot, so short wait...
        }

        if(color == 1) GPIOPinWrite(GPIO_PORTF_BASE, BLUE, 0x0);    // Turn off blue LED
        else GPIOPinWrite(GPIO_PORTF_BASE, RED, 0x0);               // Turn off red LED

        SysCtlDelay(2000000);      // Wait a bit between each dot/dash

    }

    SysCtlDelay(10000000);     // Extra long wait between digits

}

// Convert n to Morse code binary.
char num2Morse(int n){

    // Converts n to a 5-bit string.
    switch(n){
        case 0: return 0b11111;
        case 1: return 0b01111;
        case 2: return 0b00111;
        case 3: return 0b00011;
        case 4: return 0b00001;
        case 5: return 0b00000;
        case 6: return 0b10000;
        case 7: return 0b11000;
        case 8: return 0b11100;
        case 9: return 0b11110;
        default: return 0;
    }

}
