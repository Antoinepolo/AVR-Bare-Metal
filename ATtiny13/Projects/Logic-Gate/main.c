/*
 * File:   main.c
 * Author: Antoine Polo
 *
 * Created on March 20, 2026, 10:07 PM
 */


#include <avr/io.h>

#define BTN_MASK ((1 << PB0) | (1 << PB1) | (1 << PB2))                         // Masque : PB0-2 à 1

int main(void)
{
    DDRB |= (1 << PB3);                                                         // PB3 en sortie
    DDRB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));                            // PB0-2 en entrée
    PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);                              // PB0-2 en pull-up
    
    while(1)
    {
        if (!(PINB & BTN_MASK) == 0)                                            // Si PINA & MASQUE == 0 alors
                                                                                // Ex : PINB = 0b00000000 & 0b00000111 (masque) = 0 (tout appuyé)
        {
            PORTB |= (1 << PB3);                                                // Met la sortie PB3 a haut
        }
        else
        {
            PORTB &= ~(1 << PB3);                                               // Met la sortie PB3 a bas
        }
    }
}
