/**
 *  \file       rows.hpp
 *  \author     Dylan van Eck
 *  \date       2017
 *  \version    1.0
 *  
 *  \brief      headerfile of the class rows
 * 
 */
    

#ifndef ROWS_HPP
#define ROWS_HPP

#include "hwlib.hpp"

/**
 *  \class     rows
 *  \brief     Class who makes a port_in_from_pins.
 *  \details   This class is used to be used in the setup class.
 */

class rows
{
private:
    hwlib::port_in_from_pins row;   ///< Port_in_from_pins of al the row inputs
public:
    /**
    *@param     row ~ port of al the row inputs
    */
    rows(hwlib::port_in_from_pins & row);

};

#endif // ROWS_HPP
