//Include the headerfile
#include "midi.hpp"

//constructor initialize the same as the class setup
midi::midi(hwlib::port_in_from_pins & row, const int & num_cols, const int & note):
    setup(row, num_cols, note)
{
}

/*****************
    FUNCTIONS       
*****************/  

// Function shifts out a byte of data one bit at a time
void midi::shiftOut(hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin, uint8_t val){
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        //TEST//
        //int test = !!(val & (1 << (7 - i)));
        //hwlib::cout << test;
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
void midi::scanColumn( const int num_cols, hwlib::target::pin_out & latchPin, hwlib::target::pin_out & dataPin, hwlib::target::pin_out & clockPin){
    latchPin.set(0);
    
        shiftOut(dataPin, clockPin, bits[num_cols]);
    
    latchPin.set(1);
}

void midi::midiSetChannelBank(hwlib::target::pin_out & tx_pin, uint8_t chan, uint8_t bank){
    if (chan > 15)  return;
    if (bank > 127) return;
    
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(0xB0 | chan, tx_pin, 31250);    //midi_chan_msg
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(0x00, tx_pin, 31250);           //midi_chan_bank
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(bank, tx_pin, 31250);
}

void midi::midiSetInstrument(hwlib::target::pin_out & tx_pin, uint8_t chan, uint8_t inst){
    if (chan > 15) return;
    inst --; // page 32 of the datasheet vs1053 has instruments starting with 1 not 0
    if (inst > 127) return;
  
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(0xC0 | chan, tx_pin, 31250);    //midi_chan_program
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(inst, tx_pin, 31250);
}

void midi::midiSetChannelVolume(hwlib::target::pin_out & tx_pin, uint8_t chan, uint8_t vol){
    if (chan > 15) return;
    if (vol > 127) return;

    hwlib::uart_putc_bit_banged_pin_custom_baudrate(0xB0 | chan, tx_pin, 31250);    //midi_chan_msg  
    hwlib::uart_putc_bit_banged_pin_custom_baudrate(0x07, tx_pin, 31250);           //midi_chan_volume
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