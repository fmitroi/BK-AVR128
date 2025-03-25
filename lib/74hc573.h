#ifndef HC573_H  
#define HC573_H

// Define symbols before they’re used
#define LATCH_DDR       DDRF
#define LATCH_PORT      PORTF
#define LATCH_OUT1      PF1
#define LATCH_OUT2      PF2
#define LATCH_OUT3      PF3

// Function declarations
void LatchInit(void);

void LatchSegments_On(void);
void LatchSegments_Off(void);

void LatchDigits_On(void);
void LatchDigits_Off(void);

void LatchLeds_On(void);
void LatchLeds_Off(void);      

#endif