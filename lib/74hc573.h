/**
 * @file 74hc573.h
 * @author Florin (enhanced by Grok)
 * @brief Library for controlling the 74HC573 latch on the BK-AVR128 board.
 * @details Manages three latch outputs (PF1, PF2, PF3) for segments, digits, and LEDs.
 */

 #ifndef HC573_H
 #define HC573_H
 
 #include <avr/io.h>
 
 // Latch Pin Definitions
 #define LATCH_DDR   DDRF    ///< Data Direction Register for latch
 #define LATCH_PORT  PORTF   ///< Output Port for latch
 #define LATCH_OUT1  PF1     ///< Latch output 1 (segments)
 #define LATCH_OUT2  PF2     ///< Latch output 2 (digits)
 #define LATCH_OUT3  PF3     ///< Latch output 3 (LEDs)
 
 /**
  * @brief Initialize the 74HC573 latch.
  * @note Configures PF1, PF2, PF3 as outputs.
  */
 void LatchInit(void);
 
 /**
  * @brief Enable the segments latch.
  * @note Sets PF1 HIGH to latch segment data.
  */
 void LatchSegments_On(void);
 
 /**
  * @brief Disable the segments latch.
  * @note Sets PF1 LOW.
  */
 void LatchSegments_Off(void);
 
 /**
  * @brief Enable the digits latch.
  * @note Sets PF2 HIGH to latch digit selection.
  */
 void LatchDigits_On(void);
 
 /**
  * @brief Disable the digits latch.
  * @note Sets PF2 LOW.
  */
 void LatchDigits_Off(void);
 
 /**
  * @brief Enable the LEDs latch.
  * @note Sets PF3 HIGH to latch LED states.
  */
 void LatchLeds_On(void);
 
 /**
  * @brief Disable the LEDs latch.
  * @note Sets PF3 LOW.
  */
 void LatchLeds_Off(void);
 
 #endif // HC573_H