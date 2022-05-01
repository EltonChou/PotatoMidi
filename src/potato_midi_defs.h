#ifndef POTATOMIDI_DEFS_H_
#define POTATOMIDI_DEFS_H_

#include <Arduino.h>

#ifndef HC165_LOAD_PIN
#define HC165_LOAD_PIN 2
#endif

#ifndef HC165_CLOCK_PIN
#define HC165_CLOCK_PIN 3
#endif

#ifndef HC165_LATCH_PIN
#define HC165_LATCH_PIN 4
#endif

#ifndef HC165_SERIAL_DATA_IN_PIN
#define HC165_SERIAL_DATA_IN_PIN 5
#endif

#define HC165_CHAIN_COUNT 2
#define HC165_DATA_LENGTH 8 * HC165_CHAIN_COUNT

#ifndef HC595_LATCH_PIN
#define HC595_LATCH_PIN 6
#endif

#ifndef HC595_CLOCK_PIN
#define HC595_CLOCK_PIN 7
#endif

#ifndef HC595_SERIAL_DATA_OUT_PIN
#define HC595_SERIAL_DATA_OUT_PIN 8
#endif

#define HC595_CHAIN_COUNT 2
#define HC595_DATA_LENGTH 8 * HC595_CHAIN_COUNT

#ifndef HC4067_MUX_CHANNEL_AMOUNT_TO_USE
#define HC4067_MUX_CHANNEL_AMOUNT_TO_USE 16
#endif

#define HC4067_CHANNEL_COUNT HC4067_MUX_CHANNEL_AMOUNT_TO_USE - 1

#ifndef HC4067_MUX_DATA_PIN
#define HC4067_MUX_DATA_PIN A0
#endif

#ifndef HC4067_MUX_S0_PIN
#define HC4067_MUX_S0_PIN 9
#endif

#ifndef HC4067_MUX_S1_PIN
#define HC4067_MUX_S1_PIN 10
#endif

#ifndef HC4067_MUX_S2_PIN
#define HC4067_MUX_S2_PIN 11
#endif

#ifndef HC4067_MUX_S3_PIN
#define HC4067_MUX_S3_PIN 12
#endif

#define CONTROL_ON 127
#define CONTROL_OFF 0

typedef uint16_t LED_addr;
typedef uint16_t BTN_addr;
typedef uint8_t ControlNumber;

struct CCButton
{
    BTN_addr addr;
    LED_addr led_addr;
    ControlNumber control_number;
};

#endif