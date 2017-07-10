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
//           File      : keymatrix.cpp
//           Part of   : C++ Lightmusic, syntherziser library include buzzer, keymatrix, max7219
//           Author    : Dylan van Eck
//           Github    : https://github.com/howtoprogrambirds/IPASS
//           Copyright : dylan.vaneck@student.hu.nl 2017
//
//                 Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
===================================================================================================*/

#include "keymatrix.hpp"

namespace lightMusic{

//Constructor initialize row with param row, num_row with the number of the pins of row, num_cols with param num_cols
keyMatrix::keyMatrix(hwlib::target::pin_in & row1, hwlib::target::pin_in & row2, hwlib::target::pin_in & row3, hwlib::target::pin_in & row4, const int & numCols ):
    row1(row1),
    row2(row2),
    row3(row3),
    row4(row4),
    numCols(numCols)
{
      for(int rowCtr = 0; rowCtr < numRows; ++rowCtr){
        
        for(int colCtr = 0; colCtr < numCols; ++colCtr){
            
            //sets the keypressed of the button false
            keyPressed[rowCtr][colCtr] = false;
            
            //TEST//
            //hwlib::cout << keyPressed[rowCtr][colCtr] << "  ";
            
        }
        //TEST//
        //hwlib::cout << "\n\n";
    } 
}

/*****************
    FUNCTIONS     
*****************/  

// function send to each column line a 1 
//     1   2   3   4
//  1  -   |   -   -
//  2  -   |   -   -
//  3  -   |   -   -
//  4  -   |   -   -
//  --------------->
void keyMatrix::scanColumn( const int numCols, hwlib::target::pin_out & latchPin, hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin){
    latchPin.set(0);
    
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        
        //TEST//
        //int test = !!(val & (1 << (7 - i)));
        //hwlib::cout << test;
        
        //00000001
        //00000010
        //00000100
        //00001000
        //etc.
        dataPin.set( !!(bits[numCols] & (1 << (7 - i))));

        clockPin.set(1);
        clockPin.set(0);
    }
    
    //TEST//
    //hwlib::cout << "\n";
    
    latchPin.set(1);
}

    /*****************
      GETTERS/SETTERS     
    *****************/

    
bool* keyMatrix::getRowValue(){
    rowValue[0] = row1.get();
    rowValue[1] = row2.get();
    rowValue[2] = row3.get();
    rowValue[3] = row4.get();
    return rowValue;
}

//return number of rows in the keyMatrix
int keyMatrix::getNum_rows(){
    return numRows;
}

//return number of cols in the keyMatrix
int keyMatrix::getNum_cols(){
    return numCols;
}

//return bool of a the given location of the keyPressed
bool keyMatrix::getKeyPressed(int rowCtr, int colCtr){
    return keyPressed[rowCtr][colCtr];
}

//set the given data to keyPressed on a given location
void keyMatrix::setKeyPressed(int rowCtr, int colCtr, bool data){
    keyPressed[rowCtr][colCtr] = data;
}

//set 1 minus/plus the int quantOfPressKeys
void keyMatrix::minMaxQuantOfPresKeys(bool minMax){
    if(minMax == 1){
        quantOfPresButtons++;
    }
    else{
        quantOfPresButtons--;
    }

}

//get int quantofpreskeys
int keyMatrix::getQuantOfPresKeys(){
    return quantOfPresButtons;
}

}