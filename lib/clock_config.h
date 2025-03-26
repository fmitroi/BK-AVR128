/**
 * @file clock_config.h
 * @author Florin (enhanced by Grok)
 * @brief Clock frequency configuration for the ATmega128.
 */

 #ifndef CLOCK_CONFIG_H
 #define CLOCK_CONFIG_H
 
 /**
  * @brief CPU clock frequency in Hz.
  * @note Default set to 8 MHz; adjust as needed for your BK-AVR128 setup.
  */
 #ifndef F_CPU
 #define F_CPU 8000000UL
 #endif
 
 #endif // CLOCK_CONFIG_H