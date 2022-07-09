#include "hc4067_mux.h"

int mux_channel[16][4] = {
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
    int s_pins[] = {
        HC4067_MUX_S0_PIN,
        HC4067_MUX_S1_PIN,
        HC4067_MUX_S2_PIN,
        HC4067_MUX_S3_PIN};

    for (int i; i < 4; i++)
    {
        // digitalWrite(s_pins[i], 0);
        digitalWrite(s_pins[i], mux_channel[channel][i]);
        delayMicroseconds(8);
    }
    // Serial.print("\tMUX CH: ");
    // Serial.print(channel);
    return analogRead(HC4067_MUX_DATA_PIN);
}

void hc4067_mux::setup()
{
    int s_pins[] = {
        HC4067_MUX_S0_PIN,
        HC4067_MUX_S1_PIN,
        HC4067_MUX_S2_PIN,
        HC4067_MUX_S3_PIN};

    pinMode(HC4067_MUX_DATA_PIN, INPUT);
    for (int i; i < 4; i++)
    {
        pinMode(s_pins[i], OUTPUT);
        digitalWrite(s_pins[i], LOW);
    }
}
