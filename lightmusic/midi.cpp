//          Copyright Dylan van Eck 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


//Include the headerfile
#include "midi.hpp"
#include "constantsmidi.hpp"

namespace lightmusic{

//constructor initialize the same as the class setup
midi::midi(hwlib::port_in_from_pins & row, const int & num_cols, const int & note):
    keymatrix(row, num_cols, note)
{
}

/*****************
    FUNCTIONS       
*****************/  

void midi::midiSetChannelBank(hwlib::target::pin_out & tx_pin, uint8_t chan, uint8_t bank){
    if (chan > 15)  return;
    if (bank > 127) return;
    
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(MIDI_CHAN_MSG | chan, tx_pin, 31250);    //midi_chan_msg
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(MIDI_CHAN_BANK, tx_pin, 31250);           //midi_chan_bank
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(bank, tx_pin, 31250);
}

void midi::midiSetInstrument(hwlib::target::pin_out & tx_pin, uint8_t chan, uint8_t inst){
    if (chan > 15) return;
    inst --; // page 32 of the datasheet vs1053 has instruments starting with 1 not 0
    if (inst > 127) return;
  
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(MIDI_CHAN_PROGRAM | chan, tx_pin, 31250);    //midi_chan_program
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(inst, tx_pin, 31250);
}

void midi::midiSetChannelVolume(hwlib::target::pin_out & tx_pin, uint8_t chan, uint8_t vol){
    if (chan > 15) return;
    if (vol > 127) return;

    hwlib::uart_putc_bit_banged_pin_custom_baudrate(MIDI_CHAN_MSG | chan, tx_pin, 31250);    //midi_chan_msg  
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(MIDI_CHAN_VOLUME, tx_pin, 31250);           //midi_chan_volume
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(vol, tx_pin, 31250);
}

//Send midi note on message to tx_pin
void midi::noteOn(hwlib::target::pin_out & tx_pin, uint8_t chan, int rowCtr, int colCtr, uint8_t vel, uint8_t keyToMidiMap[9][17]){
    if (chan > 15) return;
    if (vel > 127) return;

  
    //hwlib::uart_putc_bit_banged_pin_custom_baudrate(0x90 | chan, tx_pin, 31250);
    //hwlib::uart_putc_bit_banged_pin_custom_baudrate(keyToMidiMap[rowCtr][colCtr], tx_pin, 31250);
    //hwlib::uart_putc_bit_banged_pin_custom_baudrate(vel, tx_pin, 31250);
    
    //TEST//
    int midi = keyToMidiMap[colCtr][rowCtr];
    hwlib::cout << "bericht: noot aan "<< 0x90 << "\n";
    hwlib::cout << "bericht: midi " << midi << "\n";
    hwlib::cout << "noot aan: rij ";
    hwlib::cout << rowCtr;
    hwlib::cout << " colom ";
    hwlib::cout << colCtr << "\n";
    hwlib::cout << "bericht noot velocity " << vel<< "\n\n";


}

//Send midi note off message to tx_pin
void midi::noteOff(hwlib::target::pin_out & tx_pin, uint8_t chan, int rowCtr, int colCtr, uint8_t vel, uint8_t keyToMidiMap[9][17]) {
    if (chan > 15) return;
    if (vel > 127) return;
    
    
    //hwlib::uart_putc_bit_banged_pin_custom_baudrate(0x80 | chan, tx_pin, 31250);
    //hwlib::uart_putc_bit_banged_pin_custom_baudrate(keyToMidiMap[rowCtr][colCtr], tx_pin, 31250);
    //hwlib::uart_putc_bit_banged_pin_custom_baudrate(vel, tx_pin, 31250);
    
    //TEST//
    uint16_t midi = keyToMidiMap[colCtr][rowCtr];
    hwlib::cout << "bericht: noot uit "<< 0x80 << "\n";
    hwlib::cout << "bericht: midi " << midi <<"\n";
    hwlib::cout << "noot uit: rij ";
    hwlib::cout << rowCtr;
    hwlib::cout << " colom ";
    hwlib::cout << colCtr << "\n";
    hwlib::cout << "bericht noot velocity " << vel << "\n\n";

}


// function checks if rowvalue is 1 and keypressed is false by: 
//             \/
//         1   2   3   4
//      1  -   |   -   -
//    ->2  =   +   =   =
//      3  -   |   -   -
//      4  -   |   -   -
//      --------------->
void midi::midinoteOn(hwlib::target::pin_out & tx_pin, int rowValue[], int colCtr, uint8_t chan, uint8_t vel, bool keyPressed[9][17], uint8_t keyToMidiMap[9][17]) {
    for(int rowCtr=0; rowCtr< num_rows; ++rowCtr){
        //TEST//
        //int k = rowValue[rowCtr];
        //hwlib::cout << k;
        if(rowValue[rowCtr] != 0 && !keyPressed[rowCtr][colCtr]){
            keyPressed[rowCtr][colCtr] = true;
            noteOn(tx_pin, chan, rowCtr, colCtr, vel, keyToMidiMap);
            
        }
    }    
}

// function checks if rowvalue is 0 and keypressed is true
void midi::midinoteOff(hwlib::target::pin_out & tx_pin ,int  rowValue[], int colCtr, uint8_t chan, uint8_t vel, bool keyPressed[9][17], uint8_t keyToMidiMap[9][17]) {
    for(int rowCtr=0; rowCtr< num_rows; ++rowCtr){
        if(rowValue[rowCtr] == 0 && keyPressed[rowCtr][colCtr]){
            keyPressed[rowCtr][colCtr] = false;
            noteOff(tx_pin, chan, rowCtr, colCtr, vel, keyToMidiMap);
        }
    }
}

}