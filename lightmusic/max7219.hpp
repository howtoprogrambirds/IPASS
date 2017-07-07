/**
 *  \file       max7219.hpp
 *  \author     Dylan van Eck
 *  \date       2017
 *  \version    1.0
 *  
 *  \brief      headerfile of the class max7219
 * 
 */

//          Copyright Dylan van Eck 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef MAX7219_HPP
#define MAX7219_HPP

#include "monochrome8x8dotmatrix.hpp"
#include "hwlib.hpp"

namespace lightmusic{
    
    /**
     * @class       max7219
     * @brief       Class to set and draw on the max7219 8x8 matrixes
     * @details     max7219 is a class with 8 functions who makes it possible to set, draw and clear 8x8 matrixes
     */

class max7219: public monochrome8x8dotmatrix{
private:
    hwlib::target::pin_out din;         ///<Pin dataIn
    hwlib::target::pin_out clk;         ///<Pin clock
    hwlib::target::pin_out load;        ///<Pin load
    int outputmatrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE * LEDMATRIX_QUANTITY)+1] = {0};
    
public:

    /**
     * @param din       ~ Pin dataIn
     * @param clk       ~ Pin clock
     * @param load      ~ Pin load
     * @param size_x    ~ Width of led matrix
     * @param size_y    ~ Height of led matrix
     */
    max7219(hwlib::target::pin_out din, hwlib::target::pin_out clk, hwlib::target::pin_out load, const int & size_x, const int & size_y);
    
    /**
     * @brief Funtion Set a pixel on the full matrix
     * @param x         ~ Indicates the x-axis where the pixel have to be set
     * @param y         ~ Indicates the y-axis where the pixel have to be set
     * @param matrix    ~ The matrix where the pixel will be set
     * @param data      ~ Is the data that will be set on the location it is default 1
     */
    void setPixel(int x, int y, bool data);
    
    
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
     * @brief Shift data to the din pin, its repeating it so many time as it's own value repeat, but it doesn't load
     * @param data      Pin Data
     * @param repeat    How many times the shift repeats
     */
    void shiftDataRepeat(const uint16_t data, const uint8_t repeat);
    
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
    void set8x8matrix(const int inputmatrix[LEDMATRIX_SIZE+1][LEDMATRIX_SIZE +1], int ledX);
    
    /**
     * @brief Virtual to clear the full matrix(now: (8,32))
     * @param matrix    ~ The matrix that will be cleared
     */
    void clearDisplay();
    
    /**
     * @brief draws the matrix to the ledmatrix
     * @param matrix    ~ Matrix that will be written to led matrix
     */
    void draw();
    
    void checkOutputmatrix();

};

}

#endif // MAX7219_HPP
