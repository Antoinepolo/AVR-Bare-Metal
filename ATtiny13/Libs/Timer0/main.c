/*
 * File:   main.c
 * Author: antoinepolo
 *
 * Created on March 29, 2026, 11:04 AM
 *
 * ===========================================================================
 * Project Setup - ATtiny13
 * ===========================================================================
 * * Hardware :
 * -------------------
 * [PB0] ---> LED 1
 * [PB1] ---> LED 2
 * * Program Behavior :
 * ----------------------
 * LED 1 (PB0) : Blink with a frequency of 1.25 Hz)
 * LED 2 (PB1) : Blink with a frequency of 1.00 Hz)
 * Formula : f(Hz) = (1/millis x 2)
 * * Configuration bits :
 * ----------------------------------
 * - Clock Source : Internal RC 9.6 MHz
 * - CKDIV8       : Clear
 * - WDTON        : Clear
 * ===========================================================================
 */

#define F_CPU 9600000UL

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0_hal.h"

int main(void)
{
    uint32_t holder_PB0 = 0;                                // Stock le temps actuel pour PB0
    uint32_t holder_PB1 = 0;                                // Stock le temps actuel pour PB1
    
    DDRB |= (1 << PB0) | (1 << PB1);                        // PB0 et PB1 en sortie
    
    timer0_init();                                          // Démarre le timer
    
    sei();                                                  // Active les intteruptions
    
    PORTB &= ~((1 << PB0) | (1 << PB1));                    // PB0 et PB1 mis à l'état bas
    
    holder_PB0 = millis();                                  // Sauvegarde du temps actuel PB0
    holder_PB1 = millis();                                  // Sauvegarde du temps actuel PB1
    
    while(1)                                                // Boucle principale
    {
        if(millis_end(holder_PB0, 400))                     // C'est t'il écouller 400 milliseconde depuis holder_PB0 ?
        {
            PORTB ^= (1 << PB0);                            // Toggle PB0
            holder_PB0 = millis();                          // On reprend le temps actuel
        }
        
        if(millis_end(holder_PB1, 500))                     // C'est t'il écouller 500 milliseconde depuis holder_PB1 ?
        {
            PORTB ^= (1 << PB1);                            // Toggle PB1
            holder_PB1 = millis();                          // On reprend le temps actuel
        }
    }
}
