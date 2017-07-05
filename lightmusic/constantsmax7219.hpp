
//          Copyright Dylan van Eck 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef CONSTANTSMAX7219_HPP
#define CONSTANTSMAX7219_HPP

#include "stdint.h"

///NO-OP registers uses for no change in the data
constexpr uint8_t MAX7219_REG_NO_OP         = 0x00;

 
constexpr uint8_t MAX7219_REG_DECODE        = 0x09;
constexpr uint8_t MAX7219_REG_INTENSITY     = 0x0A;
constexpr uint8_t MAX7219_REG_SCAN_LIMIT    = 0x0B;
constexpr uint8_t MAX7219_REG_SHUTDOWN      = 0x0C;
constexpr uint8_t MAX7219_REG_DISPLAYTEST   = 0x0F;

constexpr uint8_t MAX7219_NO_OP_DATA        = 0x00;
constexpr uint8_t MAX7219_COLUMN1           = 0x01;
constexpr uint8_t MAX7219_COLUMN2           = 0x02;
constexpr uint8_t MAX7219_COLUMN3           = 0x03;
constexpr uint8_t MAX7219_COLUMN4           = 0x04;
constexpr uint8_t MAX7219_COLUMN5           = 0x05;
constexpr uint8_t MAX7219_COLUMN6           = 0x06;
constexpr uint8_t MAX7219_COLUMN7           = 0x07;
constexpr uint8_t MAX7219_COLUMN8           = 0x08; 

constexpr uint8_t MAX7219_SCAN_LIMIT        = 0x07; 
constexpr uint8_t MAX7219_NORMAL_OPERATION  = 0x01;
constexpr uint8_t INTENSITY_LVL             = 0x01;
constexpr uint8_t LEDMATRIX_SIZE            = 8;
constexpr uint8_t LEDMATRIX_QUANTITY        = 4;
constexpr uint8_t PIXELBUFFER               = 0x00;
#endif