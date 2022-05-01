#include "hc4067_mux.h"

int hc4067_mux::read_channel_value(int channel)
{
    for (size_t i; i < sizeof(s_pins); i++)
    {
        digitalWrite(s_pins[i], mux_channel[channel][i]);
    }

    int val = analogRead(HC4067_MUX_DATA_PIN);

    return val;
}

void hc4067_mux::setup()
{
    pinMode(HC4067_MUX_DATA_PIN, INPUT);
    for (size_t i; i < sizeof(s_pins); i++)
    {
        pinMode(s_pins[i], OUTPUT);
    }
}
