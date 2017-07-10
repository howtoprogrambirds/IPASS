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
//           File      : midi.hpp
//           Part of   : C++ Lightmusic, syntherziser library include buzzer, keymatrix, max7219
//           Author    : Dylan van Eck
//           Github    : https://github.com/howtoprogrambirds/IPASS
//           Copyright : dylan.vaneck@student.hu.nl 2017
//
//                 Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
===================================================================================================*/

#ifndef MIDI_HPP
#define MIDI_HPP

#include "keymatrix.hpp"
#include "hwlib.hpp"

namespace lightmusic{

 /**
 * @class     midi
 * @brief     Class to send midi messages to tx pin.
 *  
 * @details   
 * Midi is a sub class It has six functions who makes it possible
 * to send midi messages on the basis of the keymatrix's input.
 */

class midi: public keymatrix{
private:
    uint8_t keyToMidiMap[8][8];                                 ///< Uint8_t used for setting every button to a key
    int velocity = 127;                                         ///< Indicate the velocity, default 127
    int note;
public:

    /**
     * @brief Constructor
     * @param row           ~ Port of al the row inputs
     * @param num_cols      ~ Number of all the colums
     * @param note          ~ Number of the first button's key
     * 
     * @details
     * initialize the same parameters as the class keymatrix
     */
    midi(hwlib::target::pin_in & row1, hwlib::target::pin_in & row2, hwlib::target::pin_in & row3, hwlib::target::pin_in & row4, const int & num_cols, int & note);
    
    
    
    /*****************
        FUNCTIONS     
    *****************/
    
    /**
     * @brief Set te channelbank of the vs1053
     * @param tx_pin    ~ The pin on which sends midi messages
     * @param chan      ~ Channel
     * @param bank      ~ Bank
     */
    void midiSetChannelBank(hwlib::target::pin_out & tx_pin, uint8_t chan, uint8_t bank);
    
    /**
     * @brief Set te instrument of the vs1053
     * @param tx_pin    ~ The pin on which sends midi messages
     * @param chan      ~ Channel
     * @param inst      ~ Instrument
     */
    void midiSetInstrument(hwlib::target::pin_out & tx_pin, uint8_t chan, uint8_t inst);
    
    /**
     * @brief Set te Volume channel of the vs1053
     * @param tx_pin    ~ The pin on which sends midi messages
     * @param chan      ~ Channel
     * @param vol      ~ volume
     */
    void midiSetChannelVolume(hwlib::target::pin_out & tx_pin, uint8_t chan, uint8_t vol);
    
    /**
     * @brief Send midi note on message to tx_pin
     * @param tx_pin    ~ The pin on which sends midi messages
     * @param chan      ~ Uint8_t to send midi on a specific channel
     * @param rowCtr    ~ Container who holds the pressed row number
     * @param colCtr    ~ Container who holds the pressed col number    
     * @param vel       ~ velocity
     */
    void noteOn(hwlib::target::pin_out & tx_pin, uint8_t chan, int rowCtr, int colCtr, uint8_t vel);
    
    /**
     * @brief Send midi note off message to tx_pin
     * @param tx_pin    ~ The pin on which sends midi messages
     * @param chan      ~ Uint8_t to send midi on a specific channel
     * @param rowCtr    ~ Container who holds the released row number
     * @param colCtr    ~ Container who holds the released col number    
     * @param vel       ~ velocity
     */
    void noteOff(hwlib::target::pin_out & tx_pin, uint8_t chan, int rowCtr, int colCtr, uint8_t vel);
    
    /**
     * @brief Check which button is played on keymatrix. uses noteOn() based on the check.
     * @param tx_pin    ~ The pin on which sends midi messages
     * @param rowValue  ~ Array with the values of the row
     * @param colCtr    ~ Container who holds the released col number 
     * @param chan      ~ Uint8_t to send midi on a specific channel
     * @param vel       ~ veloctity
     */
    void midinoteOn(hwlib::target::pin_out & tx_pin, int rowValue[], int colCtr, uint8_t chan, uint8_t vel, bool keyPressed[9][17]);
    
    /**
     * @brief Check which button is released on keymatrix. uses noteOff() based on the check.
     * @param tx_pin    ~ The pin on which sends midi messages
     * @param rowValue  ~ Array with the values of the row
     * @param colCtr    ~ Container who holds the released col number 
     * @param chan      ~ Uint8_t to send midi on a specific channel
     * @param vel       ~ veloctity
     */
    void midinoteOff(hwlib::target::pin_out & tx_pin, int rowValu[], int colCtr, uint8_t chan, uint8_t vel, bool keyPressed[9][17]);
    
    /**
     * @brief get the value of a keytomidimap on a given location
     * @param rowctr which row
     * @param colctr which column
     * @return int of the key on the given location
     */
    int getkeytomidimap(int rowctr, int colctr);
    
    /**
     * @brief get the value of a keytomidimap on a given location
     * @param rowctr which row
     * @param colctr which column
     * @return uint8_t of the key on the given location
     */
    uint8_t getkeytomidimap8t(int rowctr, int colctr);
    
    /**
     * @brief set the velocity by "min/max number + velocity"
     * @param number how many numbers it wil change
     * @param minMax minus(false) or plus(true)
     */
    void minMaxVelocity(int number, bool minMax);
    
    /**
     * @brief get the velocity
     * @return int velocity
     */
    int getVelocity();
};

}

#endif // MIDI_HPP
