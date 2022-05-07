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
#define POLL_DELAY_MSEC 5

#include <USB-MIDI.h>

#include "interface_controller.h"

using namespace interface_controller;

USBMIDI_CREATE_INSTANCE(0, MIDI);

interface_controller::GainController *gain_controller;
interface_controller::ButtonController *btn_controller;
interface_controller::LEDController *led_controller;

void handle_control_change(midi::Channel channel, uint8_t control_number, uint8_t control_value)
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
  MIDI.setHandleControlChange(handle_control_change);
  MIDI.begin(MIDI_CHANNEL);
}

void loop()
{
  MIDI.read();
  gain_controller->refresh(MIDI, MIDI_CHANNEL);
  btn_controller->refresh(MIDI, MIDI_CHANNEL);
  led_controller->refresh();
  delay(POLL_DELAY_MSEC);
}
