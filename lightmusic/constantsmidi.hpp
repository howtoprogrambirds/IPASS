/*===================================================================================================
//        ___               __      __                                            
//       /\_ \   __        /\ \    /\ \__                            __          
//       \//\ \ /\_\     __\ \ \___\ \ ,_\   ___ ___   __  __   ____/\_\    ___   
//         \ \ \\/\ \  /'_ `\ \  _ `\ \ \/ /' __` __`\/\ \/\ \ /',__\/\ \  /'___\ 
//          \_\ \\ \ \/\ \L\ \ \ \ \ \ \ \_/\ \/\ \/\ \ \ \_\ /\__, `\ \ \/\ \__/ 
//          /\____\ \_\ \____ \ \_\ \_\ \__\ \_\ \_\ \_\ \____\/\____/\ \_\ \____\
//          \/____/\/_/\/___L\ \/_/\/_/\/__/\/_/\/_/\/_/\/___/ \/___/  \/_/\/____/
//                       /\____/                                                  
//                       \_/__/                                                   
//
//           File      : constantmidi.hpp
//           Part of   : C++ Lightmusic, syntherziser library include buzzer, keymatrix, max7219
//           Author    : Dylan van Eck
//           Github    : https://github.com/howtoprogrambirds/IPASS
//           Copyright : dylan.vaneck@student.hu.nl 2017
//
//                 Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
===================================================================================================*/

#ifndef CONSTANTSMIDI_HPP
#define CONSTANTSMIDI_HPP

#include "stdint.h"

namespace constmidi{

///@file

// -----------------------------------------------------------------------------
///BANK - select which bank of sounds to use

constexpr uint8_t VS1053_BANK_DEFAULT       = 0x00;
constexpr uint8_t VS1053_BANK_DRUMS1        = 0x78;
constexpr uint8_t VS1053_BANK_DRUMS2        = 0x7F;
constexpr uint8_t VS1053_BANK_MELODY        = 0x79;

// -----------------------------------------------------------------------------
///STATUS midi messages - standard status midi messages

constexpr uint8_t STATUS_MIDI_NOTE_ON              = 0x90;
constexpr uint8_t STATUS_MIDI_NOTE_OFF             = 0x80;
constexpr uint8_t STATUS_MIDI_CHAN_MSG             = 0xB0;
constexpr uint8_t STATUS_MIDI_CHAN_BANK            = 0x00;
constexpr uint8_t STATUS_MIDI_CHAN_VOLUME          = 0x07;
constexpr uint8_t STATUS_MIDI_CHAN_PROGRAM         = 0xC0;

}

#endif //CONSTANTSMIDI_HPP