/**
 * @file 74hc573.c
 * @author Florin (enhanced by Grok)
 * @brief Implementation of 74HC573 latch control functions.
 */

 #include "74hc573.h"
 #include <avr/io.h>
 
 void LatchInit(void) {
     LATCH_DDR |= (1 << LATCH_OUT1) | (1 << LATCH_OUT2) | (1 << LATCH_OUT3); // Outputs
     LATCH_PORT &= ~((1 << LATCH_OUT1) | (1 << LATCH_OUT2) | (1 << LATCH_OUT3)); // All LOW initially
 }
 
 void LatchSegments_On(void) {
     LATCH_PORT |= (1 << LATCH_OUT1);
 }
 
 void LatchSegments_Off(void) {
     LATCH_PORT &= ~(1 << LATCH_OUT1);
 }
 
 void LatchDigits_On(void) {
     LATCH_PORT |= (1 << LATCH_OUT2);
 }
 
 void LatchDigits_Off(void) {
     LATCH_PORT &= ~(1 << LATCH_OUT2);
 }
 
 void LatchLeds_On(void) {
     LATCH_PORT |= (1 << LATCH_OUT3);
 }
 
 void LatchLeds_Off(void) {
     LATCH_PORT &= ~(1 << LATCH_OUT3);
 }