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
//           File      : constantmax7219.hpp
//           Part of   : C++ Lightmusic, syntherziser library include buzzer, keymatrix, max7219
//           Author    : Dylan van Eck
//           Github    : https://github.com/howtoprogrambirds/IPASS
//           Copyright : dylan.vaneck@student.hu.nl 2017
//
//                 Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
===================================================================================================*/

#ifndef CONSTANTSMAX7219_HPP
#define CONSTANTSMAX7219_HPP

#include "stdint.h"

namespace constmax7219{
    
///@file

// -----------------------------------------------------------------------------
///NO-OP register address - If this is send as an address to a max7218 it changes nothing, 
///if you overlook the data which is sent to the same chip.

constexpr uint8_t MAX7219_REG_NO_OP                         = 0x00;  

// -----------------------------------------------------------------------------
///DIGIT register addresses - are addressed directly so that individual digits 
///can be updated and retain data, digits(1-8).

constexpr uint8_t MAX7219_REG_DIGIT1                        = 0x01;
constexpr uint8_t MAX7219_REG_DIGIT2                        = 0x02;
constexpr uint8_t MAX7219_REG_DIGIT3                        = 0x03;
constexpr uint8_t MAX7219_REG_DIGIT4                        = 0x04;
constexpr uint8_t MAX7219_REG_DIGIT5                        = 0x05;
constexpr uint8_t MAX7219_REG_DIGIT6                        = 0x06;
constexpr uint8_t MAX7219_REG_DIGIT7                        = 0x07;
constexpr uint8_t MAX7219_REG_DIGIT8                        = 0x08; 

// -----------------------------------------------------------------------------
///CONTROL register addresses - consist of decode mode, display intensity,
///scan limit (number of scanned digits), shutdown, and display test (all LEDs on).

constexpr uint8_t MAX7219_REG_DECODE                        = 0x09;
constexpr uint8_t MAX7219_REG_INTENSITY                     = 0x0A;
constexpr uint8_t MAX7219_REG_SCAN_LIMIT                    = 0x0B;
constexpr uint8_t MAX7219_REG_SHUTDOWN                      = 0x0C;
constexpr uint8_t MAX7219_REG_DISPLAYTEST                   = 0x0F;

// -----------------------------------------------------------------------------
///DECODE register data - sets BCD code B (0-9, E, H, L, P, and -) 
///or no-decode operation for each digit.

constexpr uint8_t MAX7219_DATA_DECODE_NO_DECODE             = 0x00;
constexpr uint8_t MAX7219_DATA_DECODE_CODE_B1               = 0x01;
constexpr uint8_t MAX7219_DATA_DECODE_CODE_B2               = 0x0F;
constexpr uint8_t MAX7219_DATA_DECODE_CODE_B_ALL            = 0xFF;

// -----------------------------------------------------------------------------
///INTENSITY register data - control the display brightness.

constexpr uint8_t MAX7219_DATA_INTENSITY_LVL1               = 0x00;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL2               = 0x01;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL3               = 0x02;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL4               = 0x03;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL5               = 0x04;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL6               = 0x05;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL7               = 0x06;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL8               = 0x07;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL9               = 0x08;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL10              = 0x09;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL11              = 0x0A;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL12              = 0x0B;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL13              = 0x0C;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL14              = 0x0D;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL15              = 0x0E;
constexpr uint8_t MAX7219_DATA_INTENSITY_LVL16              = 0x0F;

// -----------------------------------------------------------------------------
///SCAN LIMIT register data - sets how many digits are displayed, from 1 to 8.

constexpr uint8_t MAX7219_DATA_SCAN_LIMIT1                  = 0x00;
constexpr uint8_t MAX7219_DATA_SCAN_LIMIT2                  = 0x01;
constexpr uint8_t MAX7219_DATA_SCAN_LIMIT3                  = 0x02;
constexpr uint8_t MAX7219_DATA_SCAN_LIMIT4                  = 0x03;
constexpr uint8_t MAX7219_DATA_SCAN_LIMIT5                  = 0x04;
constexpr uint8_t MAX7219_DATA_SCAN_LIMIT6                  = 0x05;
constexpr uint8_t MAX7219_DATA_SCAN_LIMIT7                  = 0x06;
constexpr uint8_t MAX7219_DATA_SCAN_LIMIT8                  = 0x07;

// -----------------------------------------------------------------------------
///SHUTDOWN register data - makes it possible to shut the max7219 down.

constexpr uint8_t MAX7219_DATA_SHUTDOWN_SHUTDOWN              = 0x00;
constexpr uint8_t MAX7219_DATA_SHUTDOWN_NORMAL_OPERATION      = 0x01;

// -----------------------------------------------------------------------------
///DISPLAY TEST register data - operates in two modes: normal and display test. 
///Display-test mode turns all LEDs.

constexpr uint8_t MAX7219_DATA_TEST_NORMAL_OPERATION        = 0x00;
constexpr uint8_t MAX7219_DATA_TEST_DISPLAY_TEST            = 0x01;

// -----------------------------------------------------------------------------
///MEASUREMENTS - size of the led matrix (example: 8x8), the quantity of max7219

constexpr uint8_t LEDMATRIX_SIZE                            = 8;
constexpr uint8_t MAX7219_QUANTITY                          = 4;

}

#endif //CONSTANTSMAX7219_HPP