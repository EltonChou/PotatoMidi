#ifndef POTATOMIDI_INTERFACECONTROLLER_H_
#define POTATOMIDI_INTERFACECONTROLLER_H_

#include <USB-MIDI.h>

#include "potato_midi_defs.h"

// https://stackoverflow.com/questions/37074763/arduino-class-array-member

namespace interface_controller
{
    void setup();

    class InterfaceController
    {
    public:
        InterfaceController(){};
        ~InterfaceController(){};
        virtual void refresh(midi::MidiInterface<usbMidi::usbMidiTransport> &midi_interface, midi::Channel inChannel){};
    };

    class GainController : public InterfaceController
    {
    private:
        int gain_volumes[HC4067_MUX_CHANNEL_AMOUNT_TO_USE];

    public:
        GainController();
        ~GainController(){};
        void refresh(midi::MidiInterface<usbMidi::usbMidiTransport> &midi_interface, midi::Channel inChannel) override;
    };

    class ButtonController : public InterfaceController
    {
    private:
        uint16_t old_btn_state = 0x0000;

    public:
        ButtonController(){};
        ~ButtonController(){};
        void refresh(midi::MidiInterface<usbMidi::usbMidiTransport> &midi_interface, midi::Channel inChannel) override;
    };

    class LEDController
    {
    private:
        uint16_t led_state = 0x0000;

    public:
        LEDController(){};
        ~LEDController(){};
        inline void light_up(LED_addr led_addr) { led_state |= led_addr; };
        inline void light_off(LED_addr led_addr) { led_state &= ~(led_addr); };
        void refresh();
        void update_state(uint8_t channel, uint8_t control_number, uint8_t control_value);
    };

}

#endif
