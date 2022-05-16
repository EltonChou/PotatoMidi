#include <USB-MIDI.h>

#include "hc4067_mux.h"
#include "hc165_controller.h"
#include "hc595_controller.h"
#include "interface_controller.h"

using interface_controller::ButtonController;
using interface_controller::GainController;
using interface_controller::LEDController;

GainController::GainController()
{
    for (uint8_t i = 0; i < HC4067_CHANNEL_COUNT; ++i)
    {
        this->gain_volumes[i] = 0;
    }
}

void GainController::refresh(
    midi::MidiInterface<usbMidi::usbMidiTransport> *midi_interface,
    midi::Channel inChannel)
{
    for (uint8_t channel = 0; channel < HC4067_CHANNEL_COUNT; ++channel)
    {
        uint8_t strip_val = constrain(hc4067_mux::read_channel_value(channel) / 8, 0, 127);
        if (this->gain_volumes[channel] != strip_val)
        {
            this->gain_volumes[channel] = strip_val;
            midi_interface->sendControlChange(channel, strip_val, inChannel);
        }
        delayMicroseconds(8);
    }
}

void ButtonController::refresh(
    midi::MidiInterface<usbMidi::usbMidiTransport> *midi_interface,
    midi::Channel inChannel)
{
    uint16_t current_btn_state;
    uint16_t pressed_btn_state;

    hc165_controller::disable_clock();
    hc165_controller::load();
    hc165_controller::enable_clock();
    current_btn_state = uint16_t(hc165_controller::read_shift(LSBFIRST)) << 8;
    current_btn_state |= uint16_t(hc165_controller::read_shift(LSBFIRST));

    if (current_btn_state != this->old_btn_state)
    {
        pressed_btn_state = (this->old_btn_state ^ current_btn_state) & this->old_btn_state;
        if (pressed_btn_state)
        {
            for (uint8_t i = 0; i < HC165_DATA_LENGTH; ++i)
            {
                CCButton the_button = control_bottons[i];
                if (pressed_btn_state & the_button.addr)
                {
                    midi_interface->sendControlChange(
                        the_button.control_number, CONTROL_ON, inChannel);
                }
            }
        }
        this->old_btn_state = current_btn_state;
    }
}

void LEDController::refresh()
{
    hc595_controller::write_shift(uint8_t(this->led_state), LSBFIRST);
    hc595_controller::write_shift(uint8_t(this->led_state >> 8), LSBFIRST);
    hc595_controller::store_data();
}

void LEDController::update_state(uint8_t channel, uint8_t control_number, uint8_t control_value)
{
    for (uint8_t i; i < HC595_DATA_LENGTH; ++i)
    {
        if (control_number == control_bottons[i].control_number)
        {
            if (control_value == CONTROL_ON)
            {
                this->light_up(control_bottons[i].led_addr);
            }
            else
            {
                this->light_off(control_bottons[i].led_addr);
            }
        }
    }
}

void interface_controller::setup()
{
    hc165_controller::setup();
    hc595_controller::setup();
    hc4067_mux::setup();
}
