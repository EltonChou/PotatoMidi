#include "hc165_controller.h"

void hc165_controller::setup()
{
    pinMode(HC165_LOAD_PIN, OUTPUT);
    pinMode(HC165_CLOCK_PIN, OUTPUT);
    pinMode(HC165_LATCH_PIN, OUTPUT);
    pinMode(HC165_SERIAL_DATA_IN_PIN, INPUT);

    digitalWrite(HC165_CLOCK_PIN, LOW);
    digitalWrite(HC165_LATCH_PIN, HIGH);
}

void hc165_controller::load()
{
    digitalWrite(HC165_LOAD_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(HC165_LOAD_PIN, HIGH);
    delayMicroseconds(5);
}

void hc165_controller::pulse()
{
    digitalWrite(HC165_CLOCK_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(HC165_CLOCK_PIN, HIGH);
    delayMicroseconds(5);
}

void hc165_controller::enable_clock()
{
    digitalWrite(HC165_LATCH_PIN, LOW);
}

void hc165_controller::disable_clock()
{
    digitalWrite(HC165_LATCH_PIN, HIGH);
}

uint8_t hc165_controller::read_shift(uint8_t bit_order)
{
    uint8_t val = shiftIn(HC165_SERIAL_DATA_IN_PIN, HC165_CLOCK_PIN, LSBFIRST);
    return val;
}
