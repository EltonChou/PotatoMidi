#define MIDI_CHANNEL 1
#define POLL_DELAY_MSEC 20

#include <USB-MIDI.h>

#include "interface_controller.h"

using namespace interface_controller;


USBMIDI_CREATE_INSTANCE(0, MIDI);

GainController gain_controller;
ButtonController btn_controller;
LEDController led_controller;

void handle_control_change(uint8_t channel, uint8_t control_number, uint8_t control_value)
{
  led_controller.update_state(channel, control_number, control_value);
  led_controller.refresh();
}

void setup()
{
  interface_controller::setup();

  Serial.begin(115200);
  MIDI.begin(MIDI_CHANNEL);
}

void loop()
{
  MIDI.read();
  gain_controller.refresh(MIDI, MIDI_CHANNEL);
  btn_controller.refresh(MIDI, MIDI_CHANNEL);

  delay(POLL_DELAY_MSEC);
}
