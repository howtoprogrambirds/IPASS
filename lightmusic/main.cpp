//          Copyright Dylan van Eck 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "hwlib.hpp"
#include "stdint.h"
#include "midi.hpp"
#include "max7219.hpp"
#include "constantsmax7219.hpp"
#include "constantsmidi.hpp"
#include "constants8x8chars.hpp"
#include "buzzer.hpp"
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
    
    auto clk    = target::pin_out(target::pins::d6);                         //Due pin 2
    auto load   = target::pin_out(target::pins::d7);                         //Due pin 3
    auto din    = target::pin_out(target::pins::d11);
    auto sig    = target::pin_out(target::pins::d12);
    
    
    max7219 kees(din,clk,load,8,8);
    //int matrix[LEDMATRIX_SIZE+1][(LEDMATRIX_SIZE * LEDMATRIX_QUANTITY)+1] = {0};
    kees.Setup();
    //kees.checkOutputmatrix();
    buzzer buzz(sig);
    
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
    int note = 29;
    int manynotes = 0;
    int velocity = 127;
    bool keyPressed[9][17];         ///< Bool used for detection of a pushed button or releaved button
    uint8_t keyToMidiMap[9][17];    ///< Uint8_t used for setting every button to a key
    
    //makes a object mijnmidi
    midi mijnmidi(rows, NUM_COLS, note);
    
    //set the keymatrix of mijnmidi every keypressed on false and keytomidimap to his note 
    mijnmidi.set(note, keyPressed, keyToMidiMap);
    
    for(;;){
        for (int colCtr = 0; colCtr < NUM_COLS; ++colCtr){
            //scan the column for input
            mijnmidi.scanColumn(colCtr,latchPin,dataPin,clockPin);
            
            
            int rowValue[NUM_ROWS];
            rowValue[0] = row1Pin.get();
            rowValue[1] = row2Pin.get();
            rowValue[2] = row3Pin.get();
            rowValue[3] = row4Pin.get();
            
            
            //midinoteOn checks if there is a input if so he sends a midi message with note on
            //mijnmidi.midinoteOn(txPin, rowValue, colCtr, 0, 127, keyPressed, keyToMidiMap);
            for(int rowCtr=0; rowCtr< NUM_ROWS; ++rowCtr){
                //hwlib::cout << rowValue[rowCtr];
                if(rowValue[rowCtr] != 0){
                    int notenumber = keyToMidiMap[colCtr][rowCtr];
                    
                    int letter = notenumber - ((notenumber/12) * 12);
                    
                    //int octave = notenumber/12;
                    buzz.tone(2093);
                    if(!keyPressed[rowCtr][colCtr]){
                        keyPressed[rowCtr][colCtr] = true;
                        //hwlib::cout << "ROW: " << rowCtr << "COL: " << colCtr << "\n\n";
                        manynotes++;
                
                        
                        if(keyPressed[NUM_ROWS-1][NUM_COLS-1] == true && velocity > 0){
                            velocity--;
                            kees.set8x8matrix(MXIN[0], 0);
                            kees.set8x8matrix(MXIN[1], 1);
                            kees.set8x8matrix(MXIN[3], 2);
                            kees.set8x8matrix(MXIN[4], 3);
                        }
                        else if(keyPressed[NUM_ROWS-1][NUM_COLS-2] == true && velocity < 127){
                            velocity++;
                            kees.set8x8matrix(MXIN[0], 0);
                            kees.set8x8matrix(MXIN[1], 1);
                            kees.set8x8matrix(LETTERS[9], 2);
                            kees.set8x8matrix(MXIN[2], 3);
                        }
                        else{
                            mijnmidi.noteOn(txPin, 0x00, rowCtr, colCtr,127, keyToMidiMap);
                            kees.set8x8matrix(LETTERS[letter], 0);
                            
                            int volume = velocity;
                            int number1 = volume/100;
                            int number2 = (volume - (number1*100)) / 10;
                            int number3 = volume - (number1 *100 + number2 * 10);
                            kees.set8x8matrix(NUMBERS[number1], 1);
                            kees.set8x8matrix(NUMBERS[number2], 2);
                            kees.set8x8matrix(NUMBERS[number3], 3);
                        }
                        kees.draw();
                    }
                }
            }
            //midinoteOff checks if the input is false again and sends his own midi messages with note off
            //mijnmidi.midinoteOff(txPin, rowValue, colCtr, 0, 127, keyPressed, keyToMidiMap);
            for(int rowCtr=0; rowCtr< NUM_ROWS; ++rowCtr){
                if(rowValue[rowCtr] == 0 && keyPressed[rowCtr][colCtr]){
                    keyPressed[rowCtr][colCtr] = false;
                    mijnmidi.noteOff(txPin, 0x00, rowCtr, colCtr, 127, keyToMidiMap);
                    manynotes--;
                    if(manynotes == 0){
                    kees.clearDisplay();
                    }
                }
            }
        }
    }
    
    
}
