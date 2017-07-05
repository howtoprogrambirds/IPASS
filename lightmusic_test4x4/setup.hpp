/**
 *  \file       setup.hpp
 *  \author     Dylan van Eck
 *  \date       2017
 *  \version    1.0
 *  
 *  \brief      headerfile of the class setup
 * 
 */

#ifndef SETUP_HPP
#define SETUP_HPP

/**
 *  \class     setup
 *  \brief     Class who setup the key matrix.
 *  \details   It has one function who sets the keymatrix. So, every button has the value false and has its own note
 */

#include "rows.hpp"
class setup
{
private:
    rows row;                       ///< Port_in_from_pins of al the row inputs
    int note;                       ///< Number of the first button's key
protected:
    int num_rows;                   ///< Number of all the rows  
    int num_cols;                   ///< Number of all the colums
public:
    
    /**
     * @param row           ~ port of al the row inputs
     * @param num_cols      ~ Number of all the colums
     * @param note          ~ Number of the first button's key
     */
    //Default Constructor
    setup(hwlib::port_in_from_pins & row, const int & num_cols, const int & note);
    
    /**
     * @brief Sets every button of the matrix on false and gives his own key
     * @param note ~ Number of the first button's key
     */
    void set( int note, bool keyPressed[9][17], uint8_t keyToMidiMap[9][17]);

};

#endif // SETUP_HPP
