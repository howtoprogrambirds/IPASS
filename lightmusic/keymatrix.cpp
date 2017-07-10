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

namespace lightmusic{

//Constructor initialize row with param row, num_row with the number of the pins of row, num_cols with param num_cols
keymatrix::keymatrix(hwlib::port_in_from_pins & row, const int & num_cols):
    row(row),
    num_rows(row.number_of_pins()),
    num_cols(num_cols)
{
      for(int rowCtr = 0; rowCtr < num_rows; ++rowCtr){
        
        for(int colCtr = 0; colCtr < num_cols; ++colCtr){
            
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
void keymatrix::scanColumn( const int num_cols, hwlib::target::pin_out & latchPin, hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin){
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
        dataPin.set( !!(bits[num_cols] & (1 << (7 - i))));

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

//return number of rows in the keymatrix
int keymatrix::getNum_rows(){
    return num_rows;
}

//return number of cols in the keymatrix
int keymatrix::getNum_cols(){
    return num_cols;
}

//return bool of a the given location of the keypressed
bool keymatrix::getkeypressed(int rowctr, int colctr){
    return keyPressed[rowctr][colctr];
}

//set the given data to keypressed on a given location
void keymatrix::setkeypressed(int rowctr, int colctr, bool data){
    keyPressed[rowctr][colctr] = data;
}

//set 1 minus/plus the int quantOfPressKeys
void keymatrix::minMaxQuantOfPresKeys(bool minMax){
    if(minMax == 1){
        quantOfPresButtons++;
    }
    else{
        quantOfPresButtons--;
    }

}

//get int quantofpreskeys
int keymatrix::getQuantOfPresKeys(){
    return quantOfPresButtons;
}

}