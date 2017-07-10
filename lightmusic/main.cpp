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


#define NUM_ROWS 4
#define NUM_COLS 8

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
    
    
    lightMusic::max7219 ledmatrix(din,clk,load);
    ledmatrix.setup( constMax7219::MAX7219_DATA_TEST_NORMAL_OPERATION, constMax7219::MAX7219_DATA_SCAN_LIMIT8, constMax7219::MAX7219_DATA_DECODE_NO_DECODE, 
    constMax7219::MAX7219_DATA_INTENSITY_LVL2,constMax7219::MAX7219_DATA_SHUTDOWN_NORMAL_OPERATION);
    
    //TEST//
    //ledmatrix.checkOutputmatrix();
    
    lightMusic::buzzer buzz(sig);
    
    //initialize all rows
    auto row1Pin = target::pin_in(target::pins::d2);
    auto row2Pin = target::pin_in(target::pins::d3);
    auto row3Pin = target::pin_in(target::pins::d4);
    auto row4Pin = target::pin_in(target::pins::d5);
    
    //datapin, latchpin, clockpin, txpin
    auto dataPin  = target::pin_out(target::pins::d8);
    auto latchPin = target::pin_out(target::pins::d9);
    auto clockPin = target::pin_out(target::pins::d10);
    auto txPin    = target::pin_out(target::pins::d1);
    
    
    //makes a object myMidi
    int note = 81;
    lightMusic::midi myMidi(row1Pin, row2Pin, row3Pin, row4Pin, NUM_COLS, note);
    
    while(true){
        for (int colCtr = 0; colCtr < NUM_COLS; ++colCtr){
            //scan the column for input
            myMidi.scanColumn(colCtr,latchPin,dataPin,clockPin);
            
            bool* rowValue = myMidi.getRowValue();
            
            for(int rowCtr=0; rowCtr< NUM_ROWS; ++rowCtr){
                //hwlib::cout << rowValue[rowCtr];
                if(rowValue[rowCtr] != 0){
                    
                    int notenumber = myMidi.getKeyToMidiMap(colCtr,rowCtr);
                    buzz.tone(buzz.keyMidiMapToHertz(notenumber));
                    
                    if(!myMidi.getKeyPressed(rowCtr, colCtr)){
                        myMidi.setKeyPressed(rowCtr, colCtr, true);
                        
                        //TEST//
                        //hwlib::cout << "ROW: " << rowCtr << " COL: " << colCtr << "\n\n";
                        
                        myMidi.minMaxQuantOfPresKeys(1);
                        
                        
                        if(myMidi.getKeyPressed(NUM_ROWS-1, NUM_COLS-4) == true && myMidi.getVelocity() > 0){
                            myMidi.minMaxVelocity(10,false);
                            ledmatrix.setFull4_8x8ChMatrix(const8x8Ch::SPACEMXIN[0], const8x8Ch::SPACEMXIN[1], const8x8Ch::SPACEMXIN[3], const8x8Ch::SPACEMXIN[4]);
                        }
                        else if(myMidi.getKeyPressed(NUM_ROWS-1, NUM_COLS-3) == true && myMidi.getVelocity() < 127){
                            myMidi.minMaxVelocity(10,true);
                            
                            ledmatrix.setFull4_8x8ChMatrix(const8x8Ch::SPACEMXIN[0], const8x8Ch::SPACEMXIN[1], const8x8Ch::LETTERS[9], const8x8Ch::SPACEMXIN[2]);
                        }
                        else{
                            myMidi.noteOn(txPin, 0x00, rowCtr, colCtr, myMidi.getVelocity());

                            int *sepnumber = ledmatrix.hunderdNumberSepNum(myMidi.getVelocity());
                            ledmatrix.setFull4_8x8ChMatrix(const8x8Ch::LETTERS[ledmatrix.semitoneCode(notenumber)] ,const8x8Ch::NUMBERS[sepnumber[0]], const8x8Ch::NUMBERS[sepnumber[1]], const8x8Ch::NUMBERS[sepnumber[2]]);

                        }
                        ledmatrix.draw();
                    }
                }
                
                else if(rowValue[rowCtr] == 0 && myMidi.getKeyPressed(rowCtr, colCtr)){
                    myMidi.setKeyPressed(rowCtr, colCtr, false);
                    myMidi.noteOff(txPin, 0x00, rowCtr, colCtr, myMidi.getVelocity());
                    myMidi.minMaxQuantOfPresKeys(0);
                    if(myMidi.getQuantOfPresKeys() == 0){
                    ledmatrix.clearDisplay();
                    }
                }
            }
        }
    }
    
    
}
