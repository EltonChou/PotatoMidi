#define HC165_LOAD_PIN 2
#define HC165_CLOCK_PIN 3
#define HC165_LATCH_PIN 4
#define HC165_SERIAL_DATA_IN_PIN 5

#define HC595_LATCH_PIN 6
#define HC595_CLOCK_PIN 7
#define HC595_SERIAL_DATA_OUT_PIN 8

#define HC4067_MUX_DATA_PIN A0
#define HC4067_MUX_S0_PIN 9
#define HC4067_MUX_S1_PIN 10
#define HC4067_MUX_S2_PIN 11
#define HC4067_MUX_S3_PIN 12
#define HC4067_MUX_CHANNEL_AMOUNT_TO_USE 16

#define MIDI_CHANNEL 1
#define POLL_DELAY_MSEC 10

#include <USB-MIDI.h>

#include "interface_controller.h"

using namespace interface_controller;

USBMIDI_CREATE_INSTANCE(0, MIDI);
midi::MidiInterface<usbMidi::usbMidiTransport> *midi_ptr = &MIDI;

GainController *gain_controller = new GainController();
ButtonController *btn_controller = new ButtonController();
LEDController *led_controller = new LEDController();

void handle_control_change(uint8_t channel, uint8_t control_number, uint8_t control_value)
{
  for (uint8_t i; i < HC595_DATA_LENGTH; ++i)
  {
    if (control_number == control_bottons[i].control_number)
    {
      if (control_value == CONTROL_ON)
      {
        led_controller->light_up(control_bottons[i].led_addr);
      }
      else
      {
        led_controller->light_off(control_bottons[i].led_addr);
      }
    }
  }
}

void setup()
{
  interface_controller::setup();

  Serial.begin(115200);
  midi_ptr->setHandleControlChange(handle_control_change);
  midi_ptr->begin(MIDI_CHANNEL);
}

void loop()
{
  midi_ptr->read();
  gain_controller->refresh(midi_ptr, MIDI_CHANNEL);
  btn_controller->refresh(midi_ptr, MIDI_CHANNEL);
  led_controller->refresh();
  delay(POLL_DELAY_MSEC);
}
