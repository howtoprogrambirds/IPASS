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
//           File      : keymatrix.hpp
//           Part of   : C++ Lightmusic, syntherziser library include buzzer, keymatrix, max7219
//           Author    : Dylan van Eck
//           Github    : https://github.com/howtoprogrambirds/IPASS
//           Copyright : dylan.vaneck@student.hu.nl 2017
//
//                 Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
===================================================================================================*/

#ifndef KEYMATRIX_HPP
#define KEYMATRIX_HPP

#include "hwlib.hpp"

namespace lightmusic{
    
 /**
 * @class     keymatrix
 * @brief     Class for a keymatrix.
 *
 * @details   
 * keymatrix is a class with 5 functions,
 * who makes it possible to setup the keymatrix, 
 * scan the colums with using of shiftout function.
 * And to return the number of cols and rows
 */
    
class keymatrix {
    
private:
    hwlib::port_in_from_pins row;                               ///< Port_in_from_pins of al the row inputs
    int note;                                                   ///< Number of the first button's key
    int bits[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};    ///< Array uses for scanning the columns
    
protected:
    int num_rows;                                               ///< Number of all the rows  
    int num_cols;                                               ///< Number of all the colums
public:
    
    /**
    * @brief Constructor
    * @param row Port of al the row inputs
    * @param num_cols Number of all the colums
    * @param note Number of the first button's key
    * 
    * @details
    * sets row with param row, num_row with the number of the pins of row, num_cols with param num_cols
    */
    keymatrix(hwlib::port_in_from_pins & row, const int & num_cols, const int & note);
    
    /*****************
        FUNCTIONS     
    *****************/
    
    /**
     * @brief Sets every button of the matrix on false and gives his own key
     * @param note Number of the first button's key
     */
    void set( int note, bool keyPressed[9][17], uint8_t keyToMidiMap[9][17]);
    
    /**
     * @brief Shifts out a byte of data one bit at a time
     * @param dataPin The pin on which to output each bit
     * @param clockPin The pin to toggle once the dataPin has been set to correct value
     * @param val The data to shift out
     */
    void shiftOut(hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin, uint8_t val);
    
     /**
     * @brief Send to each column line a 1 
     * @param num_cols  ~ Number of all the colums
     * @param latchPin  ~ The pin which transfers the byte to the device(Key matrix)
     * @param dataPin   ~ The pin on which to output each bit
     * @param clockPin  ~ The pin to toggle once the dataPin has been set to correct value
     */
    void scanColumn(const int num_cols, hwlib::target::pin_out & latchPin, hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin);
    
    /**
     * @brief give the number of rows back
     * @return number of rows in the keymatrix
     */
    int getNum_rows();
    
    /**
     * @brief give the number of cols back
     * @return number of cols in the keymatrix
     */
    int getNum_cols();

};

}

#endif // KEYMATRIX_HPP
