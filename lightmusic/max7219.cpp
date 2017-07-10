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
//           File      : max7219.cpp
//           Part of   : C++ Lightmusic, syntherziser library include buzzer, keymatrix, max7219
//           Author    : Dylan van Eck
//           Github    : https://github.com/howtoprogrambirds/IPASS
//           Copyright : dylan.vaneck@student.hu.nl 2017
//
//                 Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
===================================================================================================*/


#include "max7219.hpp"

namespace lightmusic{

//sets the din-outputpin, clock-outputpin, load/cs-outputpin
max7219::max7219(hwlib::target::pin_out & din, hwlib::target::pin_out & clk, hwlib::target::pin_out & load):
    din(din),
    clk(clk),
    load(load)
{
    hwlib::wait_ms(1000);
}

//set a pixel on the outputmatrix
void max7219::setPixel(int x, int y, bool data){
    if( (x < constmax7219::LEDMATRIX_SIZE+1 ) && (x > 0) && (y < constmax7219::LEDMATRIX_SIZE*constmax7219::MAX7219_QUANTITY+1) && (y > 0) ){
        outputmatrix[x][y] = data;
    }
}

//setpixel and draw it direct after setting it
void max7219::drawPixel(int x, int y, bool data){
    setPixel(x,y,data);
    draw();
}

//pulse the clkpin once
void max7219::pulseClk(hwlib::target::pin_out clk, int wait = 0){
    clk.set(0);
    hwlib::wait_ms(wait);
    clk.set(1);

}


//Shift data to the din pin, its repeating so many times as it's own given value repeat, 
void max7219::sendDataRepeat(const uint16_t data, const uint8_t repeat){
    load.set(0);
    
    for( uint8_t repeatCnt = 0; repeatCnt < repeat; repeatCnt++ ) {
        for( int16_t bitCnt = 15; bitCnt >= 0; bitCnt-- ) {
            
            //splits data in bits and write it one bit at a time to the din pin
            din.set( ( data & ( 1 << bitCnt ) ) != 0 );
            pulseClk(clk);
                        
            //TEST//
            //hwlib::cout << (( data & ( 1 << bitCnt ) ) != 0) << ' ';
            
        }
        
        //TEST//
        //hwlib::cout<<"\n";
        
    }
    
    load.set(1);
}

//setup the matrix so its possible to use
void max7219::Setup(){
    //it sends the DISPLAYTEST, it is left shifted by 8 and afterwards it sends MAX7219_DATA_TEST_NORMAL_OPERATION because so it writes this two bytes:       00001111 00000000(normal operation), 
    //this data repeats 4 times so every max7219 is setup and there is no miss_behavior
    sendDataRepeat( ( constmax7219::MAX7219_REG_DISPLAYTEST << 8) | constmax7219::MAX7219_DATA_TEST_NORMAL_OPERATION, constmax7219::MAX7219_QUANTITY );
    //it sends the MAX7219_REG_SCAN_LIMIT , it is left shifted by 8 and afterwards it sends MAX7219_DATA_SCAN_LIMIT8 because so it writes this two bytes:     00001011 00000111(display digits 0,1,2,3,4,5,6,7),
    //this data repeats 4 times so every max7219 is setup and there is no miss_behavior
    sendDataRepeat( ( constmax7219::MAX7219_REG_SCAN_LIMIT  << 8) | constmax7219::MAX7219_DATA_SCAN_LIMIT8, constmax7219::MAX7219_QUANTITY );
    //it sends the MAX7219_REG_DECODE , it is left shifted by 8 and afterwards it sends MAX7219_DATA_DECODE_NO_DECODE because so it writes this two bytes:    00001001 00000000(no decoder for digits 7-0),
    //this data repeats 4 times so every max7219 is setup and there is no miss_behavior
    sendDataRepeat( ( constmax7219::MAX7219_REG_DECODE      << 8) | constmax7219::MAX7219_DATA_DECODE_NO_DECODE, constmax7219::MAX7219_QUANTITY );
    //it sends the MAX7219_REG_INTENSITY , it is left shifted by 8 and afterwards it sends MAX7219_DATA_INTENSITY_LVL2 because so it writes this two bytes:   00001010 00000001(3/32),
    //this data repeats 4 times so every max7219 is setup and there is no miss_behavior
    sendDataRepeat( ( constmax7219::MAX7219_REG_INTENSITY  << 8)  | constmax7219::MAX7219_DATA_INTENSITY_LVL2, constmax7219::MAX7219_QUANTITY );
    //it sends the MAX7219_REG_SHUTDOWN , it is left shifted by 8 and afterwards it sends MAX7219_DATA_SHUTDOWN_NORMAL_OPERATION because so it writes this two bytes:     00001100 00000001(normal operation),
    //this data repeats 4 times so every max7219 is setup and there is no miss_behavior
    sendDataRepeat( ( constmax7219::MAX7219_REG_SHUTDOWN    << 8) | constmax7219::MAX7219_DATA_SHUTDOWN_NORMAL_OPERATION, constmax7219::MAX7219_QUANTITY );
    clearDisplay();
}

//sets a 8x8 matrix in the output matrix, it is possible to set the matrix at the first second thirth and last matrix,
void max7219::set8x8matrix(const int inputmatrix[constmax7219::LEDMATRIX_SIZE+1][constmax7219::LEDMATRIX_SIZE+1], int ledX){
    for( int columnr = 1; columnr <= constmax7219::LEDMATRIX_SIZE; columnr++ ){
        for( int row = constmax7219::LEDMATRIX_SIZE; row >= 1; row-- ){
            int x = columnr + 8 * ledX;
            setPixel(row, x ,  inputmatrix[columnr][row]);
        }
    }
}

void max7219::setfull_4_8x8_ch_matrix(const int ch1[constmax7219::LEDMATRIX_SIZE+1][constmax7219::LEDMATRIX_SIZE +1], 
    const int ch2[constmax7219::LEDMATRIX_SIZE+1][constmax7219::LEDMATRIX_SIZE +1], 
    const int ch3[constmax7219::LEDMATRIX_SIZE+1][constmax7219::LEDMATRIX_SIZE +1], 
    const int ch4[constmax7219::LEDMATRIX_SIZE+1][constmax7219::LEDMATRIX_SIZE +1]){
        set8x8matrix(ch1, 0);
        set8x8matrix(ch2, 1);
        set8x8matrix(ch3, 2);
        set8x8matrix(ch4, 3);
}

int* max7219::hunderdnumbersepnum(int hunderd){
        sepnum[0] = hunderd/100;
        sepnum[1] = (hunderd - (sepnum[0]*100)) / 10;
        sepnum[2] = hunderd - (sepnum[0] *100 + sepnum[1] * 10);
        
        return sepnum;
}

int max7219::keymiditokeyletter(int keymidinumber){
    return keymidinumber - ((keymidinumber/12) * 12);
}

//draw the output matrix to the led matrix
void max7219::draw(){
    for( int columnr = 1; columnr <= constmax7219::LEDMATRIX_SIZE; columnr++ ){
        load.set(0);
        for( int row = constmax7219::LEDMATRIX_SIZE * constmax7219::MAX7219_QUANTITY; row >= 1; row-- ){
            if( row%8 == 0 ){
                for ( int columnbit = 7; columnbit >= 0; columnbit-- ){
                    din.set( columnr & ( 1 << columnbit ));
                    pulseClk(clk);
                }
            }
            din.set(outputmatrix[columnr][row]);
            pulseClk(clk);
        }
        load.set(1);
    }
}


//sets the outputmatrix to 0 and draws it to the ledmatrix
void max7219::clearDisplay(){
    for(int columnr = 1; columnr < constmax7219::LEDMATRIX_SIZE+1; columnr++ ){
            for( int pixel = 1; pixel < constmax7219::LEDMATRIX_SIZE * constmax7219::MAX7219_QUANTITY+1; pixel++ ){
                setPixel(columnr,pixel,0);
            }
    }
    max7219::draw();
}

//writes the outputmatrix out with hwlib::cout
void max7219::checkOutputmatrix(){
    for(int i = 0; i < constmax7219::LEDMATRIX_SIZE+1; i++){
        for(int j = 0; j < (constmax7219::LEDMATRIX_SIZE * constmax7219::MAX7219_QUANTITY)+1; j++){
            hwlib::cout << outputmatrix[i][j] << ' ';
        }
        hwlib::cout << '\n';
    }
    
}
}