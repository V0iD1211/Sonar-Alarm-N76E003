#include <stdio.h>
#include "N76E003.h"
#include "Function_Define.h"

#define TRIG_PIN P1_0
#define ECHO_PIN P1_1

void Timer1_Init(void)
{
    TMOD |= 0x10;     // Timer1 in Mode1 (16-bit)
    TH1 = 0;
    TL1 = 0;
}

void delay_us(unsigned int us)
{
    unsigned char i;
    while (us--)
    {
        for (i = 0; i < 4; i++);  // ~1 µs crude delay at 16MHz, adjust if needed
    }
}

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 123; j++);
}

unsigned int measure_distance_cm(void)
{
    unsigned int time;

    // Send 10us pulse to trigger
    TRIG_PIN = 1;
    delay_us(10);
    TRIG_PIN = 0;

    // Wait for echo to go high
    while (!ECHO_PIN);

    // Start timer
    TR1 = 1;
    TH1 = 0;
    TL1 = 0;

    // Wait for echo to go low
    while (ECHO_PIN);

    // Stop timer
    TR1 = 0;

    time = (TH1 << 8) | TL1;

    // Convert time to distance (in cm)
    return time / 58;  // Approximate formula for cm
}

void main(void)
{
    Timer1_Init();

    // Configure pins
    //P1M1 &= ~(1 << 0); P1M2 &= ~(1 << 0);  // TRIG: push-pull output
    //P1M1 |=  (1 << 1); P1M2 &= ~(1 << 1);  // ECHO: input mode
    
    P10_PushPull_Mode;
    P11_Input_Mode;
    P14_Quasi_Mode;
    
    P1_4 = 1;
   
    while (1)
    {
        unsigned int distance = measure_distance_cm();
        
        // Here you can do something with the distance
        // e.g., toggle LED, send via UART, etc.
        
        if (distance == 10 )
        {
          P1_4 = 0;
          delay_ms(1000);
          P1_4 = 1;
        }
        
        else
        { 
          P1_4 = 1;
        }

        delay_ms(250); // Wait before next reading
    }
}
