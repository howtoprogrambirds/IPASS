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
keymatrix::keymatrix(hwlib::port_in_from_pins & row, const int & num_cols, const int & note):
    row(row),
    note(note),
    num_rows(row.number_of_pins()),
    num_cols(num_cols)
{
}

/*****************
    FUNCTIONS     
*****************/  

// Function Sets every button of the matrix on false and gives his own key
void keymatrix::set(){
    
    //TEST//
    //hwlib::cout << num_rows << num_cols;
    
    // For loop through the columns
    for(int rowCtr = 0; rowCtr < num_rows; ++rowCtr){
        
        // For loop through the rows
        for(int colCtr = 0; colCtr < num_cols; ++colCtr){
            
            //sets the keypressed of the button false
            keyPressed[rowCtr][colCtr] = false;
            
            //TEST//
            //hwlib::cout << keyPressed[rowCtr][colCtr] << "  ";
            //hwlib::cout << note << "  ";
            
            //sets the KeytoMidiMap of the button with his own note
            keyToMidiMap[colCtr][rowCtr] = note;
            
            //TEST//
            int midi = keyToMidiMap[colCtr][rowCtr];
            hwlib::cout << midi << "  ";
            
            note++;
        }
        //TEST//
        hwlib::cout << "\n\n";
    }    
}

// Function shifts out a byte of data one bit at a time
void keymatrix::shiftOut(hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin, uint8_t val){
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
        dataPin.set( !!(val & (1 << (7 - i))));

        clockPin.set(1);
        clockPin.set(0);
    }
    
    //TEST//
    //hwlib::cout << "\n";
}

// function send to each column line a 1 
//     1   2   3   4
//  1  -   |   -   -
//  2  -   |   -   -
//  3  -   |   -   -
//  4  -   |   -   -
//  --------------->
void keymatrix::scanColumn( const int num_cols, hwlib::target::pin_out & latchPin, hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin){
    latchPin.set(0);
    
        shiftOut(dataPin, clockPin, bits[num_cols]);
    
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

//get the value of a keytomidimap on a given location in int
int keymatrix::getkeytomidimap(int rowctr, int colctr){
    return keyToMidiMap[rowctr][colctr];
}

//get the value of a keytomidimap on a given location in int8_t
uint8_t keymatrix::getkeytomidimap8t(int rowctr, int colctr){
    return keyToMidiMap[rowctr][colctr];
}

//set the velocity by "min/max number + velocity"
void keymatrix::minMaxVelocity(int number, bool minMax){
    if(minMax == 1 && ((velocity+number) <= 127)){
        hwlib::cout << velocity;
        velocity += number;
    }
    else if(minMax == 0 && ((velocity-number) >= 0)){
        velocity -= number;
    }

}

//get the velocity
int keymatrix::getVelocity(){
    return velocity;
}

//set 1 minus/plus the int quantOfPressKeys
void keymatrix::minMaxQuantOfPresKeys(bool minMax){
    if(minMax == 1){
        quantOfPresKeys++;
    }
    else{
        quantOfPresKeys--;
    }

}

//get int quantofpreskeys
int keymatrix::getQuantOfPresKeys(){
    return quantOfPresKeys;
}
}