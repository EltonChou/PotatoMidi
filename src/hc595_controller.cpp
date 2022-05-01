#include "hc595_controller.h"

void hc595_controller::setup()
{
    pinMode(HC595_CLOCK_PIN, OUTPUT);
    pinMode(HC595_LATCH_PIN, OUTPUT);
    pinMode(HC595_SERIAL_DATA_OUT_PIN, OUTPUT);
}

void hc595_controller::pulse()
{
    digitalWrite(HC595_CLOCK_PIN, LOW);
    digitalWrite(HC595_CLOCK_PIN, HIGH);
}

void hc595_controller::store_data()
{
    digitalWrite(HC595_LATCH_PIN, LOW);
    digitalWrite(HC595_LATCH_PIN, HIGH);
}

void hc595_controller::write_shift(uint8_t data, uint8_t bit_order)
{
    shiftOut(HC595_SERIAL_DATA_OUT_PIN, HC595_CLOCK_PIN, bit_order, data);
}
