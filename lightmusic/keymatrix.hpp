/**
 *  \file       keymatrix.hpp
 *  \author     Dylan van Eck
 *  \date       2017
 *  \version    1.0
 *  
 *  \brief      headerfile of the class keymatrix
 * 
 */

#ifndef KEYMATRIX_HPP
#define KEYMATRIX_HPP

#include "hwlib.hpp"

//          Copyright Dylan van Eck 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


/**
 *  \class     keymatrix
 *  \brief     Class with a keymatrix.
 *  \details   It has one function who sets the keymatrix. So, every button has the value false and has its own note
 */

class keymatrix
{
private:
    hwlib::port_in_from_pins row;                               ///< Port_in_from_pins of al the row inputs
    int note;                                                   ///< Number of the first button's key
    int bits[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};    ///< Array uses for scanning the columns
    
protected:
    int num_rows;                   ///< Number of all the rows  
    int num_cols;                   ///< Number of all the colums
public:
    
    /**
     * @param row           ~ port of al the row inputs
     * @param num_cols      ~ Number of all the colums
     * @param note          ~ Number of the first button's key
     */
    //Default Constructor
    keymatrix(hwlib::port_in_from_pins & row, const int & num_cols, const int & note);
    
    /**
     * @brief Sets every button of the matrix on false and gives his own key
     * @param note ~ Number of the first button's key
     */
    void set( int note, bool keyPressed[9][17], uint8_t keyToMidiMap[9][17]);
    
    /**
     * @brief Shifts out a byte of data one bit at a time
     * @param dataPin   ~ The pin on which to output each bit
     * @param clockPin  ~ The pin to toggle once the dataPin has been set to correct value
     * @param val       ~ The data to shift out
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
    
    int getNum_rows();
    
    int getNum_cols();

};

#endif // KEYMATRIX_HPP
