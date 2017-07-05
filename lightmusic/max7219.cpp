//          Copyright Dylan van Eck 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "max7219.hpp"

max7219::max7219(hwlib::target::pin_out din, hwlib::target::pin_out clk, hwlib::target::pin_out load, const int & size_x, const int & size_y):
    monochrome8x8dotmatrix(size_x, size_y),
    din(din),
    clk(clk),
    load(load)
{
    hwlib::wait_ms(1000);
}
//set a pixel on the big matrix(8,32)
void max7219::setPixel(int x, int y, bool data){
    if( (x < LEDMATRIX_SIZE+1 ) && (x > 0) && (y < LEDMATRIX_SIZE*LEDMATRIX_QUANTITY+1) && (y > 0) ){
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

//shift data to the din pin, its repeating it so many time as it's own parameter repeat
void max7219::shiftDataRepeat(const uint16_t data, const uint8_t repeat){
    for( uint8_t repeatCnt = 0; repeatCnt < repeat; repeatCnt++ ) {
        for( int16_t bitCnt = 15; bitCnt >= 0; bitCnt-- ) {
            //splits data in bits and write it one bit at a time to the din pin
            din.set( ( data & ( 1 << bitCnt ) ) != 0 );
            pulseClk(clk);
                        hwlib::cout << (( data & ( 1 << bitCnt ) ) != 0) << ' ';
        }
        hwlib::cout<<"\n";
    }
}


void max7219::sendDataRepeat(const uint16_t data, const uint8_t repeat){
    // sets load to zero to make it possible to clock data
    load.set(0);
    shiftDataRepeat(data, repeat);
    // sets load to one to load the data
    load.set(1);
    
}

void max7219::Setup(){
    //it send a DISPLAYTEST it is left shifted by 8 and or on NO_OP_DATA because it write this two bytes:       00001111 00000000(normal operation), 
    //this data repeats 4 times so every max7219 is setup and there is no miss_behavior
    sendDataRepeat( ( MAX7219_REG_DISPLAYTEST << 8) | MAX7219_NO_OP_DATA, LEDMATRIX_QUANTITY );
    //it send the SCANLIMIT it is left shifted by 8 and or on SCAN_LIMIT because it write this two bytes:       00001011 00000111(display digits 0,1,2,3,4,5,6,7),
    //this data repeats 4 times so every max7219 is setup and there is no miss_behavior
    sendDataRepeat( ( MAX7219_REG_SCAN_LIMIT  << 8) | MAX7219_SCAN_LIMIT, LEDMATRIX_QUANTITY );
    //it send the DECODE it is left shifted by 8 and or on NO_OP_DATA because it write this two bytes:          00001001 00000000(no decoder for digits 7-0),
    //this data repeats 4 times so every max7219 is setup and there is no miss_behavior
    sendDataRepeat( ( MAX7219_REG_DECODE      << 8) | MAX7219_NO_OP_DATA, LEDMATRIX_QUANTITY );
    //it send the INTENSITY it is left shifted by 8 and or on INTENSITY_LVL because it write this two bytes:    00001010 00000001(3/32),
    //this data repeats 4 times so every max7219 is setup and there is no miss_behavior
    sendDataRepeat( ( MAX7219_REG_INTENSITY  << 8)  | INTENSITY_LVL, LEDMATRIX_QUANTITY );
    //it send the SHUTDOWN it is left shifted by 8 and or on INTENSITY_LVL because it write this two bytes:     00001100 00000001(normal operation),
    //this data repeats 4 times so every max7219 is setup and there is no miss_behavior
    sendDataRepeat( ( MAX7219_REG_SHUTDOWN    << 8) | MAX7219_NORMAL_OPERATION, LEDMATRIX_QUANTITY );
    clearDisplay();
}

//sets a 8x8 matrix in the output matrix, it is possible to set the matrix at the first second thirth and last matrix,
void max7219::set8x8matrix(const int inputmatrix[LEDMATRIX_SIZE+1][LEDMATRIX_SIZE+1], int ledX){
    for( int columnr = 1; columnr <= LEDMATRIX_SIZE; columnr++ ){
        for( int row = LEDMATRIX_SIZE; row >= 1; row-- ){
            int x = columnr + 8 * ledX;
            setPixel(row, x ,  inputmatrix[columnr][row]);
        }
    }
}

//draw the input matrix to the led matrix
void max7219::draw(){
    for( int columnr = 1; columnr <= LEDMATRIX_SIZE; columnr++ ){
        load.set(0);
        for( int row = LEDMATRIX_SIZE * LEDMATRIX_QUANTITY; row >= 1; row-- ){
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

void max7219::clearDisplay(){
    for(int columnr = 1; columnr < LEDMATRIX_SIZE+1; columnr++ ){
            for( int pixel = 1; pixel < LEDMATRIX_SIZE * LEDMATRIX_QUANTITY+1; pixel++ ){
                setPixel(columnr,pixel,0);
            }
    }
    max7219::draw();
}

void max7219::checkOutputmatrix(){
    for(int i = 0; i < LEDMATRIX_SIZE+1; i++){
        for(int j = 0; j < (LEDMATRIX_SIZE * LEDMATRIX_QUANTITY)+1; j++){
            hwlib::cout << outputmatrix[i][j] << ' ';
        }
        hwlib::cout << '\n';
    }
    
}