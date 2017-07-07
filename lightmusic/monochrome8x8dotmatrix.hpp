/**
 *  \file       unicolordisplay.hpp
 *  \author     Dylan van Eck
 *  \date       2017
 *  \version    1.0
 *  
 *  \brief      headerfile of the class unicolor display
 * 
 */

//          Copyright Dylan van Eck 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef MONOCHROME8X8DOTMATRIX_HPP
#define MONOCHROME8X8DOTMATRIX_HPP

/**
 *  @class     unicolordisplay
 *  @brief     Abstract class could be used by any kind of unicolor display.
 *  @details   It is a very basic abstract class for unicolor displays like OLED and LED matrices.
 */

#include "constantsmax7219.hpp"

namespace lightmusic{

class monochrome8x8dotmatrix
{
protected:
    const int size_x;                       ///<number of the size of the x-as of the unicolor display
    const int size_y;                       ///<number of the size of the y-as of the unicolor display
public:
    /**
     * @param size_x    ~ Number of the size of the x-axis of the unicolor display
     * @param size_y    ~ Number of the size of the y-axis of the unicolor display
     */
    monochrome8x8dotmatrix(const int & size_x, const int & size_y);
    /**
     * @brief virtual funtion draw a pixel on the full matrix(now: (8,32))
     * @param x         ~ Indicates the x-axis where the pixel have to be set
     * @param y         ~ Indicates the y-axis where the pixel have to be set
     * @param matrix    ~ The matrix where the pixel will be set
     * @param data      ~ Is the data that will be set on the location it is default 1
     */
    virtual void drawPixel(int x, int y, bool data = 1) = 0;
    
    /**
     * @brief virtual to clear the full matrix(now: (8,32))
     * @param matrix    ~ The matrix that will be cleared
     */
    virtual void clearDisplay() = 0;

};

}

#endif // UNICOLORDISPLAY_HPP
