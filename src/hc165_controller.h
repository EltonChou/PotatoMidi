#ifndef POTATOMIDI_HC165CONTROLLER_H_
#define POTATOMIDI_HC165CONTROLLER_H_

#include "potato_midi_defs.h"

namespace hc165_controller
{
    void setup();
    void load();
    void pulse();
    void enable_clock();
    void disable_clock();
    uint8_t read_shift(uint8_t bitOrder = MSBFIRST);
}

#endif