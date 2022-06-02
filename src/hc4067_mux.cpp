#include "hc4067_mux.h"

const int s_pins[4] = {
    HC4067_MUX_S0_PIN,
    HC4067_MUX_S1_PIN,
    HC4067_MUX_S2_PIN,
    HC4067_MUX_S3_PIN};

const int mux_channel[16][4] = {
    // {S0, S1, S2, S3,}
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 1, 0},
    {1, 0, 1, 0},
    {0, 1, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 0, 1},
    {1, 1, 0, 1},
    {0, 0, 1, 1},
    {1, 0, 1, 1},
    {0, 1, 1, 1},
    {1, 1, 1, 1}};

int hc4067_mux::read_channel_value(int channel)
{
    for (int i; i < 4; i++)
    {
        digitalWrite(s_pins[i], mux_channel[channel][i]);
    }

    int val = analogRead(HC4067_MUX_DATA_PIN);

    return val;
}

void hc4067_mux::setup()
{
    pinMode(HC4067_MUX_DATA_PIN, INPUT);
    for (int i; i < 4; i++)
    {
        pinMode(s_pins[i], OUTPUT);
    }
}
