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

int s_pins[] = {
    HC4067_MUX_S0_PIN,
    HC4067_MUX_S1_PIN,
    HC4067_MUX_S2_PIN,
    HC4067_MUX_S3_PIN};

int hc4067_mux::read_channel_value(int channel)
{
    digitalWrite(HC4067_MUX_S0_PIN, mux_channel[channel][0]);
    delayMicroseconds(10);
    digitalWrite(HC4067_MUX_S1_PIN, mux_channel[channel][1]);
    delayMicroseconds(10);
    digitalWrite(HC4067_MUX_S2_PIN, mux_channel[channel][2]);
    delayMicroseconds(10);
    digitalWrite(HC4067_MUX_S3_PIN, mux_channel[channel][3]);
    delayMicroseconds(10);

    return analogRead(HC4067_MUX_DATA_PIN);
}

void hc4067_mux::setup()
{
    pinMode(HC4067_MUX_S0_PIN, OUTPUT);
    pinMode(HC4067_MUX_S1_PIN, OUTPUT);
    pinMode(HC4067_MUX_S2_PIN, OUTPUT);
    pinMode(HC4067_MUX_S3_PIN, OUTPUT);
}
