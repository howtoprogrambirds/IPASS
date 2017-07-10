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
//           File      : max7219.hpp
//           Part of   : C++ Lightmusic, syntherziser library include buzzer, keymatrix, max7219
//           Author    : Dylan van Eck
//           Github    : https://github.com/howtoprogrambirds/IPASS
//           Copyright : dylan.vaneck@student.hu.nl 2017
//
//                 Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
===================================================================================================*/

#ifndef MAX7219_HPP
#define MAX7219_HPP

#include "constantsmax7219.hpp"
#include "hwlib.hpp"

namespace lightmusic{
    
 /**
 * @class       max7219
 * @brief       Class to set and draw on the max7219 8x8 matrixes
 * 
 * @details     
 * max7219 is a class with 8 functions,
 * who makes it possible to set, draw and clear 8x8 matrixes
 */

class max7219{
private:
    hwlib::target::pin_out din;                                                                                                 ///<Pin dataIn
    hwlib::target::pin_out clk;                                                                                                 ///<Pin clock
    hwlib::target::pin_out load;                                                                                                ///<Pin load
    int outputmatrix[constmax7219::LEDMATRIX_SIZE+1][(constmax7219::LEDMATRIX_SIZE * constmax7219::MAX7219_QUANTITY)+1] = {0};  ///<The output matrix that writes to the max7219
    int sepnum[3] = {0};
public:

    /**
     * @brief Construtor
     * @param din Pin dataIn
     * @param clk Pin clock
     * @param load Pin load
     * 
     * @details
     * sets the din-outputpin, clock-outputpin, load/cs-outputpin
     */
    max7219(hwlib::target::pin_out din, hwlib::target::pin_out clk, hwlib::target::pin_out load);
    
    /*****************
        FUNCTIONS     
    *****************/
    
    /**
     * @brief Funtion Set a pixel on the outputmatrix
     * @param x         ~ Indicates the x-axis where the pixel have to be set
     * @param y         ~ Indicates the y-axis where the pixel have to be set
     * @param data      ~ Is the data that will be set on the location it is default 1
     */
    void setPixel(int x, int y, bool data);
    
    
    /**
     * @brief Funtion Set a pixel draw it direct after setting it on the outputmatrix
     * @param x         ~ Indicates the x-axis where the pixel have to be set
     * @param y         ~ Indicates the y-axis where the pixel have to be set
     * @param data      ~ Is the data that will be set on the location it is default 1
     */
    void drawPixel(int x, int y, bool data);
    
    /**
     * @brief Pulse the clkpin once
     * @param clk       Pin clock
     * @param wait      How many ms you want to slow the pulse down, default is 0
     */
    void pulseClk(hwlib::target::pin_out clk, int wait);
    
    /**
     * @brief Shift data to the din pin, its repeating it so many time as it's own value repeat, it use the function shift data and it set the load "low" before it and "high" after
     * @param data      Pin Data
     * @param repeat    How many times the shift repeats
     */
    void sendDataRepeat(const uint16_t data, const uint8_t repeat);
    
    /**
     * @brief setup the matrix so its possible to use
     * @param matrix    Matrix who will be setup
     */
    void Setup();
    
    /**
     * @brief Sets a 8x8 matrix in the output matrix, it is possible to set the matrix at the first second thirth and last matrix,
     * @param inputmatrix       8x8 matrix, character what have to write to the output matrix
     * @param outputmatrix      The full matrix where the inputmatrix will be set
     * @param ledX              Use for where to set the inputmatrix, first, second, thirth or last matrix
     */
    void set8x8matrix(const int inputmatrix[constmax7219::LEDMATRIX_SIZE+1][constmax7219::LEDMATRIX_SIZE +1], int ledX);
    
    /**
     * @brief set four 8x8 matrixes to the four ledmatrix
     * @param ch1 first 8x8 matrix
     * @param ch2 second 8x8 matrix
     * @param ch3 thirth 8x8 matrix
     * @param ch4 fourth 8x8 matrix
     */
    void setfull_4_8x8_ch_matrix(const int ch1[constmax7219::LEDMATRIX_SIZE+1][constmax7219::LEDMATRIX_SIZE +1], 
    const int ch2[constmax7219::LEDMATRIX_SIZE+1][constmax7219::LEDMATRIX_SIZE +1], 
    const int ch3[constmax7219::LEDMATRIX_SIZE+1][constmax7219::LEDMATRIX_SIZE +1], 
    const int ch4[constmax7219::LEDMATRIX_SIZE+1][constmax7219::LEDMATRIX_SIZE +1]);
    
    /**
     * @brief seperate a hunderd number in 3 seperate numbers.
     * @details Example: 158 -> 1,5,8; 94 -> 0,9,4
     * @param hunderd int to convert
     * @return array with 3 numbers
     */
    int* hunderdnumbersepnum(int hunderd);
    
    /**
     * @brief convert the midikeynumber to keynumber
     * @details 14 -> 2, 18 -> 6
     * @param keymidinumber
     * @return int of keynumber
     */
    int keymiditokeyletter(int keymidinumber);
    
    /**
     * @brief sets the outputmatrix to 0 and draws it to the ledmatrix
     */
    void clearDisplay();
    
    /**
     * @brief draws the outputmatrix to the ledmatrix
     */
    void draw();
    
    /**
     * @brief writes the outputmatrix out with hwlib::cout
     */
    void checkOutputmatrix();

};

}

#endif // MAX7219_HPP
