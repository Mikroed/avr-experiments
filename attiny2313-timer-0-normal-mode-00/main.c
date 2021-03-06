/*
 * attiny2313-timer-0-normal-mode-00.c
 *
 * Created: 16.05.2020 16:55:37
 * Author : mikroed
 * 
 * Настройки FUSE BIT
 * HF: 0xDF
 * LF: 0x42
 * EF: 0xFF
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// обработчик прерывания переполнения счетчика таймера 0
ISR (TIMER0_OVF_vect) {
    PORTD ^= (1 << PIND0);  // переключаем сигнал на ножке PD0
}

// обработчик совпадения счетчика таймера 0 с регистром совпадения A
ISR (TIMER0_COMPA_vect) {
    PORTD ^= (1 << PIND1);  // переключаем сигнал на ножке PD1
}

// обработчик совпадения счетчика таймера 0 с регистром совпадения B
ISR (TIMER0_COMPB_vect) {
    PORTD ^= (1 << PIND2);  // переключаем сигнал на ножке PD2
}

int main (void)
{
    DDRD   = 0x17;          // конфигурируем на выход ножки 0, 1, 2 и 5 порта D
    DDRB   = 0x02;          // конфигурируем на выход ножку 2 порта B

    PORTD  = 0x00;          // задаем порт D
    PORTB  = 0x00;          // задаем порт B

    OCR0A  = 205;           // задаем значение для регистра сравнения A таймера 0
    OCR0B  = 155;           // задаем значение для регистра сравнения B таймера 0

    // разрешаем прерывания при совпадении с регистрами сравнения и при переполнении таймера
    TIMSK  = (1 << TOIE0) | (1 << OCIE0A) | (1 << OCIE0B);

    // запускаем таймер 0 с предделителем частоты 1024
    // FUSE BIT выставлены на работу кристалла от внутреннего генератора с частотой 4MHz и делением на 8
    // то есть по факту микроконтроллер работает на частоте 500000Hz
    // учитывая предделитель таймер будет работать с частотой ~488HZ
    // максимальное значение 8-битного счетчика - 255
    // следовательно прерывания будут вызываться раз в ~0.5 секунд
    TCCR0B = (1 << CS02) | (1 << CS00);

    // разрешаем прерывания
    sei();

    // бесконечный цикл
    while (1)
    {
        // впадаем в спячку
        sleep_mode();
    }
}
