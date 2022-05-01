#ifndef POTATOMIDI_HC4067MUX_H_
#define POTATOMIDI_HC4067MUX_H_

#include "potato_midi_defs.h"

namespace hc4067_mux
{
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

    int read_channel_value(int channel);
    void setup();
};

#endif
