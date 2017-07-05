/**
 *  \file       display.hpp
 *  \author     Dylan van Eck
 *  \date       2017
 *  \version    1.0
 *  
 *  \brief      headerfile of the class display
 * 
 */

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

/**
 *  @class     display
 *  @brief     Abstract class could be used by any kind of display.
 *  @details   It is a very basic abstract class for displays like OLED and LED matrices.
 */

#include "constants.hpp"
class display
{
protected:
    const int size_x;                       ///<number of the size of the x-as of the display
    const int size_y;                       ///<number of the size of the y-as of the display
    
public:
    /**
     * @param size_x    ~ Number of the size of the x-axis of the display
     * @param size_y    ~ Number of the size of the y-axis of the display
     */
    display(const int & size_x, const int & size_y);
    /**
     * @brief virtual funtion Set a pixel on the full matrix(now: (8,32))
     * @param x         ~ Indicates the x-axis where the pixel have to be set
     * @param y         ~ Indicates the y-axis where the pixel have to be set
     * @param matrix    ~ The matrix where the pixel will be set
     * @param data      ~ Is the data that will be set on the location it is default 1
     */
    virtual void setPixel(int x, int y, int matrix[LEDMATRIX_SIZE_X+1][LEDMATRIX_SIZE_Y+1], int data = 1) = 0;
    
    /**
     * @brief virtual to clear the full matrix(now: (8,32))
     * @param matrix    ~ The matrix that will be cleared
     */
    virtual void clear(int matrix[LEDMATRIX_SIZE_X+1][LEDMATRIX_SIZE_Y+1]) = 0;

};

#endif // DISPLAY_HPP
