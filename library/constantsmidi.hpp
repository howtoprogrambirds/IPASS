#ifndef CONSTANTSMIDI_HPP
#define CONSTANTSMIDI_HPP

#include "stdint.h"

///@file

constexpr uint8_t VS1053_BANK_DEFAULT       = 0x00;
constexpr uint8_t VS1053_BANK_DRUMS1        = 0x78;
constexpr uint8_t VS1053_BANK_DRUMS2        = 0x7F;
constexpr uint8_t VS1053_BANK_MELODY        = 0x79;

constexpr uint8_t MIDI_NOTE_ON              = 0x90;
constexpr uint8_t MIDI_NOTE_OFF             = 0x80;
constexpr uint8_t MIDI_CHAN_MSG             = 0xB0;
constexpr uint8_t MIDI_CHAN_BANK            = 0x00;
constexpr uint8_t MIDI_CHAN_VOLUME          = 0x07;
constexpr uint8_t MIDI_CHAN_PROGRAM         = 0xC0;
#endif