//Include the headerfile
#include "Setup.hpp"

//Constructor initialize row with param row, num_row with the number of the pins of row, num_cols with param num_cols
setup::setup(hwlib::port_in_from_pins & row, const int & num_cols, const int & note):
    row(row),
    num_rows(row.number_of_pins()),
    num_cols(num_cols)
{
}

/*****************
    FUNCTIONS       
*****************/  
 
// Function Sets every button of the matrix on false and gives his own key
void setup::set(int note, bool keyPressed[9][17], uint8_t keyToMidiMap[9][17]){
    hwlib::cout << num_rows << num_cols;
    // For loop through the columns
    for(int rowCtr = 0; rowCtr < num_rows; ++rowCtr){
            // For loop through the rows
            for(int colCtr = 0; colCtr < num_cols; ++colCtr){
                //sets the keypressed of the button false
                keyPressed[rowCtr][colCtr] = false;
                
                //TEST//
                //hwlib::cout << keyPressed[rowCtr][colCtr] << "  ";
                //hwlib::cout << note << "  ";
                
                //sets the KeytoMidiMap of the button with his own note
                keyToMidiMap[colCtr][rowCtr] = note;
                int midi = keyToMidiMap[colCtr][rowCtr];
                hwlib::cout << midi << "  ";
                note++;
            }
            //TEST//
            hwlib::cout << "\n\n";
        }
    
}

