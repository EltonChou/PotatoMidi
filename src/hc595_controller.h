
#ifndef POTATOMIDI_HC595CONTROLLER_H_
#define POTATOMIDI_HC595CONTROLLER_H_

#include "potato_midi_defs.h"

namespace hc595_controller
{
    void setup();
    void pulse();
    void store_data();
    void write_shift(uint8_t data, uint8_t bit_order = MSBFIRST);
}

#endif
