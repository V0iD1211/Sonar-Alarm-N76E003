#include <stdio.h>
#include "N76E003.h"
#include "Function_Define.h"

// crude delay (~1 ms per loop, adjust if needed)
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 123; j++);
}

void main(void)
{
    // Configure P1.4 as Quasi-bidirectional (default after reset, but explicitly clear mode bits)
    P14_PushPull_Mode;
  
    
    P1_4 = 0;
    
    while (1)
    {
        // LED ON: drive P1.4 low
        P1_4= 0;
        delay_ms(500);
        
        // LED OFF: drive P1.4 high
        P1_4 = 1;
        delay_ms(500);
        
    }
}
