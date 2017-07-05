/**
 *  \file       setup.hpp
 *  \author     Dylan van Eck
 *  \date       2017
 *  \version    1.0
 *  
 *  \brief      headerfile of the class midi
 * 
 */

#ifndef MIDI_HPP
#define MIDI_HPP

#include "setup.hpp"
#include "hwlib.hpp"

/**
 *  @class     midi
 *  @brief     Class to send midi messages to tx pin.
 *  @details   Midi is a sub class It has six functions who makes it possible to send midi messages on the basis of the keymatrix's input.
 */

class midi: public setup{
private:
     int bits[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};   ///< Array uses for scanning the columns
    
public:

    /**
     * @param row           ~ Port of al the row inputs
     * @param num_cols      ~ Number of all the colums
     * @param note          ~ Number of the first button's key
     */
    midi(hwlib::port_in_from_pins & row, const int & num_cols, const int & note);
    
    /**
     * @brief Shifts out a byte of data one bit at a time
     * @param dataPin   ~ The pin on which to output each bit
     * @param clockPin  ~ The pin to toggle once the dataPin has been set to correct value
     * @param val       ~ The data to shift out
     */
    void shiftOut(hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin, uint8_t val);
    
    
    /**
     * @brief Send to each column line a 1 
     * @param num_cols  ~ Number of all the colums
     * @param latchPin  ~ The pin which transfers the byte to the device(Key matrix)
     * @param dataPin   ~ The pin on which to output each bit
     * @param clockPin  ~ The pin to toggle once the dataPin has been set to correct value
     */
    void scanColumn(const int num_cols, hwlib::target::pin_out & latchPin, hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin);
    
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

#endif // MIDI_HPP
