/*
 * File:   timer0_hal.c
 * Author: Antoine Polo
 *
 * Created on March 29, 2026, 10:54 AM
 * 
 * MIT License
 * 
 * Copyright (c) 2020 Devilbinder (Binder Tronics) https://bindertronics.com/ (Original ATmega328p implementation)
 * Copyright (c) 2026 Antoine Polo (ATtiny13 adaptation & Atomic safety)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0_hal.h"

volatile static uint32_t millis_c = 0;                                          // La variable est static et donc lisible uniquement par ce fichier

ISR(TIM0_COMPA_vect)
{
    millis_c++;                                                                 // S'incrémente toutes les millisecondes
}

void timer0_init(void)
{
    TCCR0A = (1 << WGM01);                                                      // Mode clear timer on compare

    OCR0A = 149;                                                                // Il va donc ce reset dès qu'il atteint la valeur de OCR0A
                                                                                // (9 600 000 / 64) / 1000 = 150 cycles. On met 149 (car on compte le 0)

    TIMSK0 |= (1 << OCIE0A);                                                    // Active l'intéruption de comparaison, on execute l'ISR

    TCCR0B |= (1 << CS01) | (1 << CS00);                                        // Prescaler de 64, un seul battement d'horloge tout les 64 cycles processeur
}

uint8_t millis_end(uint32_t start_time, uint32_t delay_time)                    // Fonction qui vérifie si un délais est écouler depuis start_time
{
    return ((millis() - start_time) >= delay_time);
}

uint32_t millis(void)                                                           // Fonction qui renvoie le nombre de millisecondes depuis le démarrage
{
    return millis_c;
}
