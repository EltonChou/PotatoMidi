#ifndef POTATOMIDI_HC4067MUX_H_
#define POTATOMIDI_HC4067MUX_H_

#include "potato_midi_defs.h"

namespace hc4067_mux
{
    int read_channel_value(int channel);
    void setup();
};

#endif
