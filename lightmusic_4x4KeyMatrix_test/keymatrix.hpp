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

namespace lightMusic{
    
 /**
 * @class     keyMatrix
 * @brief     Class for a keyMatrix.
 *
 * @details   
 * keyMatrix is a class with 5 functions,
 * which makes it possible to setup the keyMatrix, 
 * scan the colums by using the shiftout function.
 * And to return the number of cols and rows
 */
    
class keyMatrix {
    
private:
    hwlib::target::pin_in row1;
    hwlib::target::pin_in row2;
    hwlib::target::pin_in row3;
    hwlib::target::pin_in row4;                                 ///< all pin_in of al the row inputs
    int note;                                                   ///< Number of the first button's key
    int bits[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};    ///< Array uses for scanning the columns
    bool keyPressed[8][8];                                      ///< Bool used for detection of a pushed button or releaved button
    int quantOfPresButtons = 0;                                 ///< How many buttons are pressed, default 0
    bool rowValue[4] = {0};
protected:
    int numRows = 4;                                           ///< Number of all the rows  
    int numCols;                                               ///< Number of all the colums
public:
    
    /**
    * @brief Constructor
    * @param row Port of al the row inputs
    * @param numCols Number of all the colums
    * @param note Number of the first button's key
    * 
    * @details
    * sets row with param row, num_row with the number of the pins of row, num_cols with param num_cols
    */
    keyMatrix(hwlib::target::pin_in & row1, hwlib::target::pin_in & row2, hwlib::target::pin_in & row3, hwlib::target::pin_in & row4, const int & numCols);
    
    /*****************
        FUNCTIONS     
    *****************/
    
     /**
     * @brief Send to each column line a 1 
     * @param numCols Number of all the colums
     * @param latchPin The pin which transfers the byte to the device(Key matrix)
     * @param dataPin The pin on which to output each bit
     * @param clockPin The pin to toggle once the dataPin has been set to correct value
     */
    void scanColumn(const int numCols, hwlib::target::pin_out & latchPin, hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin);
    
    /*****************
     GETTERS/SETTERS     
    *****************/
    
    /**
     * @brief give the value of the row in a array
     * @return array of row values
     */
    bool* getRowValue();
    
    /**
     * @brief give the number of rows back
     * @return number of rows in the keymatrix
     */
    int getNumRows();
    
    /**
     * @brief give the number of cols back
     * @return int of cols in the keymatrix
     */
    int getNumCols();
    
    /**
     * @brief get the value of a keypressed on a given location
     * @param rowctr which row
     * @param colctr which column
     * @return bool of a the given location of the keypressed
     */
    bool getKeyPressed(int rowCtr, int colCtr);
    
    /**
     * @brief set the given data to keypressed on a given location
     * @param rowctr which row
     * @param colctr which column
     * @param data the data(true or false)
     */
    void setKeyPressed(int rowctr, int colctr, bool data);
    
    /**
     * @brief get the value of a keytomidimap on a given location
     * @param rowctr which row
     * @param colctr which column
     * @return int of the key on the given location
     */
    int getKeyToMidiMap(int rowctr, int colctr);
    
    /**
     * @brief get the value of a keytomidimap on a given location
     * @param rowctr which row
     * @param colctr which column
     * @return uint8_t of the key on the given location
     */
    uint8_t getKeyToMidiMap8t(int rowctr, int colctr);
    
    /**
     * @brief set the velocity by "min/max number + velocity"
     * @param number how many numbers it wil change
     * @param minMax minus(false) or plus(true)
     */
    void minMaxVelocity(int number, bool minMax);
    
    /**
     * @brief get the velocity
     * @return int velocity
     */
    int getVelocity();
    
    /**
     * @brief set 1 minus/plus the int quantOfPressKeys
     * @param minMax minus(false) or plus(true
     */
    void minMaxQuantOfPresKeys(bool minMax);
    
    /**
     * @brief get int quantofpreskeys
     * @return int quantofpreskeys
     */
    int getQuantOfPresKeys();


};

}

#endif // KEYMATRIX_HPP
