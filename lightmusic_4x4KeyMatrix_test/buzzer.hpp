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
//           File      : buzzer.hpp
//           Part of   : C++ Lightmusic, syntherziser library include buzzer, keymatrix, max7219
//           Author    : Dylan van Eck
//           Github    : https://github.com/howtoprogrambirds/IPASS
//           Copyright : dylan.vaneck@student.hu.nl 2017
//
//                 Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
===================================================================================================*/

#ifndef BUZZER_HPP
#define BUZZER_HPP
#include "hwlib.hpp"

namespace lightMusic{

class buzzer{
private:
    int period = 1000000000;                    ///<period of 1 hertz, use for calculating the half of the period by given hertz
    hwlib::target::pin_out sig;                 ///<output pin signal for the buzzer
public:
    /**
    * @brief Constructor
    * @param sig signal output pin for the buzzer
    * 
    * @details
    * sets the output pin to the given output pin
    */
    buzzer(hwlib::target::pin_out sig);
    
    /*****************
        FUNCTIONS     
    *****************/
    
    /**
     * @brief play the tone by given hertz
     * @param hertz the hertz in ints
     */
    void tone(int hertz);
    
    /**
     * @brief calculate the hertz by given midiKeyNumber and returns the hertz in int
     * @param keyMidiNumber the number of the key
     * @return returns hertz in int
     */
    int keyMidiMapToHertz(int KeyMidiNumber);
};

}
#endif // BUZZER_HPP
