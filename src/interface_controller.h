#ifndef POTATOMIDI_INTERFACECONTROLLER_H_
#define POTATOMIDI_INTERFACECONTROLLER_H_

#include "USB-MIDI.h"

#include "potato_midi_defs.h"

// https://stackoverflow.com/questions/37074763/arduino-class-array-member

namespace interface_controller
{
    const CCButton control_bottons[16] = {
        {0x8000, 0x8000, 30},
        {0x4000, 0x4000, 31},
        {0x2000, 0x2000, 32},
        {0x1000, 0x1000, 33},
        {0x0800, 0x0800, 34},
        {0x0400, 0x0400, 35},
        {0x0200, 0x0200, 36},
        {0x0100, 0x0100, 37},
        {0x0080, 0x0080, 38},
        {0x0040, 0x0040, 39},
        {0x0020, 0x0020, 40},
        {0x0010, 0x0010, 41},
        {0x0008, 0x0008, 42},
        {0x0004, 0x0004, 43},
        {0x0002, 0x0002, 44},
        {0x0001, 0x0001, 45},
    };

    void setup();

    class InterfaceController
    {
    public:
        InterfaceController(){};
        ~InterfaceController(){};
        virtual void refresh(midi::MidiInterface<usbMidi::usbMidiTransport> *midi_interface, midi::Channel inChannel){};
    };

    class GainController : public InterfaceController
    {
    private:
        int gain_volumes[HC4067_MUX_CHANNEL_AMOUNT_TO_USE];

    public:
        GainController();
        ~GainController(){};
        void refresh(midi::MidiInterface<usbMidi::usbMidiTransport> *midi_interface, midi::Channel inChannel) override;
    };

    class ButtonController : public InterfaceController
    {
    private:
        uint16_t old_btn_state = 0x0000;

    public:
        ButtonController(){};
        ~ButtonController(){};
        void refresh(midi::MidiInterface<usbMidi::usbMidiTransport> *midi_interface, midi::Channel inChannel) override;
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
