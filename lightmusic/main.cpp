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
//           File      : main.cpp
//           Part of   : C++ Lightmusic, syntherziser library include buzzer, keymatrix, max7219
//           Author    : Dylan van Eck
//           Github    : https://github.com/howtoprogrambirds/IPASS
//           Copyright : dylan.vaneck@student.hu.nl 2017
//
//                 Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
===================================================================================================*/


#include "hwlib.hpp"
#include "stdint.h"
#include "lightmusiclib.hpp"
#include <cmath>
#include <vector>

#define NUM_ROWS 4
#define NUM_COLS 8
#define VELOCITY 40

int main( void ){	
   // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    //know when to start
    hwlib::cout << "start\n";
    
    namespace target = hwlib::target;
    
    auto clk    = target::pin_out(target::pins::d6);                         
    auto load   = target::pin_out(target::pins::d7);                         
    auto din    = target::pin_out(target::pins::d11);
    auto sig    = target::pin_out(target::pins::d12);
    
    
    lightmusic::max7219 ledmatrix(din,clk,load,8,8);
    ledmatrix.Setup();
    
    //TEST//
    //kees.checkOutputmatrix();
    
    lightmusic::buzzer buzz(sig);
    
    //initialize all rows
    auto row1Pin = target::pin_in(target::pins::d2);
    auto row2Pin = target::pin_in(target::pins::d3);
    auto row3Pin = target::pin_in(target::pins::d4);
    auto row4Pin = target::pin_in(target::pins::d5);
    
    //port_in_from_pins
    auto rows = hwlib::port_in_from_pins(row1Pin, row2Pin, row3Pin, row4Pin);
    
    //datapin, latchpin, clockpin, txpin
    auto dataPin  = target::pin_out(target::pins::d8);
    auto latchPin = target::pin_out(target::pins::d9);
    auto clockPin = target::pin_out(target::pins::d10);
    auto txPin    = target::pin_out(target::pins::d1);
    
    //initialize note
    int note = 81;
    int manynotes = 0;
    int velocity = 127;
    //bool keyPressed[9][17];         ///< Bool used for detection of a pushed button or releaved button
    uint8_t keyToMidiMap[9][17];    ///< Uint8_t used for setting every button to a key
    
    //makes a object mijnmidi
    lightmusic::midi mijnmidi(rows, NUM_COLS, note);
    
    //set the keymatrix of mijnmidi every keypressed on false and keytomidimap to his note 
    mijnmidi.set();
    
    for(;;){
        for (int colCtr = 0; colCtr < NUM_COLS; ++colCtr){
            //scan the column for input
            mijnmidi.scanColumn(colCtr,latchPin,dataPin,clockPin);
            
            
            int rowValue[NUM_ROWS];
            rowValue[0] = row1Pin.get();
            rowValue[1] = row2Pin.get();
            rowValue[2] = row3Pin.get();
            rowValue[3] = row4Pin.get();
            
            
            //midinoteOn checks if there is an input if so he sends a midi message with note on
            //mijnmidi.midinoteOn(txPin, rowValue, colCtr, 0, 127, keyPressed, keyToMidiMap);
            for(int rowCtr=0; rowCtr< NUM_ROWS; ++rowCtr){
                //hwlib::cout << rowValue[rowCtr];
                if(rowValue[rowCtr] != 0){
                    
                    int notenumber = mijnmidi.getkeytomidimap(colCtr,rowCtr);
                    buzz.tone(buzz.keymidimaptohertz(notenumber));
                    
                    if(!mijnmidi.getkeypressed(rowCtr, colCtr)){
                        mijnmidi.setkeypressed(rowCtr, colCtr, true);
                        
                        //TEST//
                        //hwlib::cout << "ROW: " << rowCtr << "COL: " << colCtr << "\n\n";
                        
                        manynotes++;
                        
                        
                        if(mijnmidi.getkeypressed(NUM_ROWS-1, NUM_COLS-1) == true && velocity > 0){
                            velocity--;
                            ledmatrix.setfull_4_8x8_ch_matrix(const8x8ch::SPACEMXIN[0], const8x8ch::SPACEMXIN[1], const8x8ch::SPACEMXIN[3], const8x8ch::SPACEMXIN[4]);
                        }
                        else if(mijnmidi.getkeypressed(NUM_ROWS-1, NUM_COLS-2) == true && velocity < 127){
                            velocity++;
                            ledmatrix.setfull_4_8x8_ch_matrix(const8x8ch::SPACEMXIN[0], const8x8ch::SPACEMXIN[1], const8x8ch::LETTERS[9], const8x8ch::SPACEMXIN[2]);
                        }
                        else{
                            mijnmidi.noteOn(txPin, 0x00, rowCtr, colCtr,127, keyToMidiMap);

                            int *sepnumber = ledmatrix.hunderdnumbersepnum(velocity);
                            ledmatrix.setfull_4_8x8_ch_matrix(const8x8ch::LETTERS[ledmatrix.keymiditokeyletter(notenumber)] ,const8x8ch::NUMBERS[sepnumber[0]], const8x8ch::NUMBERS[sepnumber[1]], const8x8ch::NUMBERS[sepnumber[2]]);

                        }
                        ledmatrix.draw();
                    }
                }
            }
            //midinoteOff checks if the input is false again and sends his own midi messages with note off
            //mijnmidi.midinoteOff(txPin, rowValue, colCtr, 0, 127, keyPressed, keyToMidiMap);
            for(int rowCtr=0; rowCtr< NUM_ROWS; ++rowCtr){
                if(rowValue[rowCtr] == 0 && mijnmidi.getkeypressed(rowCtr, colCtr)){
                    mijnmidi.setkeypressed(rowCtr, colCtr, false);
                    mijnmidi.noteOff(txPin, 0x00, rowCtr, colCtr, 127, keyToMidiMap);
                    manynotes--;
                    if(manynotes == 0){
                    ledmatrix.clearDisplay();
                    }
                }
            }
        }
    }
    
    
}
