/**
 *  \file       setup.hpp
 *  \author     Dylan van Eck
 *  \date       2017
 *  \version    1.0
 *  
 *  \brief      headerfile of the class midi
 * 
 */
 
//          Copyright Dylan van Eck 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef MIDI_HPP
#define MIDI_HPP

#include "keymatrix.hpp"
#include "hwlib.hpp"

namespace lightmusic{

/**
 *  @class     midi
 *  @brief     Class to send midi messages to tx pin.
 *  @details   Midi is a sub class It has six functions who makes it possible to send midi messages on the basis of the keymatrix's input.
 */

class midi: public keymatrix{
public:

    /**
     * @param row           ~ Port of al the row inputs
     * @param num_cols      ~ Number of all the colums
     * @param note          ~ Number of the first button's key
     */
    midi(hwlib::port_in_from_pins & row, const int & num_cols, const int & note);
    
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
    void noteOn(hwlib::target::pin_out & tx_pin, uint8_t chan, int rowCtr, int colCtr, uint8_t vel, uint8_t keyToMidiMap[9][17]);
    
    /**
     * @brief Send midi note off message to tx_pin
     * @param tx_pin    ~ The pin on which sends midi messages
     * @param chan      ~ Uint8_t to send midi on a specific channel
     * @param rowCtr    ~ Container who holds the released row number
     * @param colCtr    ~ Container who holds the released col number    
     * @param vel       ~ velocity
     */
    void noteOff(hwlib::target::pin_out & tx_pin, uint8_t chan, int rowCtr, int colCtr, uint8_t vel, uint8_t keyToMidiMap[9][17]);
    
    /**
     * @brief Check which button is played on keymatrix. uses noteOn() based on the check.
     * @param tx_pin    ~ The pin on which sends midi messages
     * @param rowValue  ~ Array with the values of the row
     * @param colCtr    ~ Container who holds the released col number 
     * @param chan      ~ Uint8_t to send midi on a specific channel
     * @param vel       ~ veloctity
     */
    void midinoteOn(hwlib::target::pin_out & tx_pin, int rowValue[], int colCtr, uint8_t chan, uint8_t vel, bool keyPressed[9][17], uint8_t keyToMidiMap[9][17]);
    
    /**
     * @brief Check which button is released on keymatrix. uses noteOff() based on the check.
     * @param tx_pin    ~ The pin on which sends midi messages
     * @param rowValue  ~ Array with the values of the row
     * @param colCtr    ~ Container who holds the released col number 
     * @param chan      ~ Uint8_t to send midi on a specific channel
     * @param vel       ~ veloctity
     */
    void midinoteOff(hwlib::target::pin_out & tx_pin, int rowValu[], int colCtr, uint8_t chan, uint8_t vel, bool keyPressed[9][17], uint8_t keyToMidiMap[9][17]);
};

}

#endif // MIDI_HPP
