#define MIDI_CHANNEL 1
#define POLL_DELAY_MSEC 30
#define get_midi_val(v) (constrain(v >> 3, 0, 127))

#include <USB-MIDI.h>

#include "hc4067_mux.h"
#include "interface_controller.h"

using namespace interface_controller;

int gain_volumes[HC4067_MUX_CHANNEL_AMOUNT_TO_USE] = {0, 0, 0, 0, 0, 0, 0, 0};

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
  // gain_controller.refresh(MIDI, MIDI_CHANNEL);
  btn_controller.refresh(MIDI, MIDI_CHANNEL);

  for (uint8_t channel = 0; channel < HC4067_MUX_CHANNEL_AMOUNT_TO_USE; ++channel)
  {
    // Serial.print("CH: ");
    // Serial.print(channel);
    int a_val = hc4067_mux::read_channel_value(channel);
    uint8_t strip_val = get_midi_val(a_val);
    if (gain_volumes[channel] != strip_val)
    {
      gain_volumes[channel] = strip_val;
      MIDI.sendControlChange(channel, strip_val, MIDI_CHANNEL);
      // Serial.print("\tVol: ");
      // Serial.print(strip_val);
    }
    // Serial.println();
    // delay(200);
  }

  delay(POLL_DELAY_MSEC);
}
