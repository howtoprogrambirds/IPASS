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
//           File      : buzzer.cpp
//           Part of   : C++ Lightmusic, syntherziser library include buzzer, keymatrix, max7219
//           Author    : Dylan van Eck
//           Github    : https://github.com/howtoprogrambirds/IPASS
//           Copyright : dylan.vaneck@student.hu.nl 2017
//
//                 Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
===================================================================================================*/

#include "buzzer.hpp"

namespace lightmusic{
 
//constructor, sets the output pin to the given output pin
buzzer::buzzer(hwlib::target::pin_out sig):
    sig(sig)
{}

/*****************
    FUNCTIONS     
*****************/ 

//play the tone by given hertz
void buzzer::tone(int hertz){
    
    //calculate the half of the period by the given hertz in nanoseconds
    int halfPeriodns = ((period/hertz)/2);
    
    
    //sets halfperiod the signal on 1 and halftime the signal on 0
    //     halfp          halfp
    // ------------------------------>
    //_______1______                ______
    //|             |               |
    //|             |               |
    //|             |               |
    //|             |_______0_______|
    sig.set(1);
    hwlib::wait_ns(halfPeriodns);
    sig.set(0);
    hwlib::wait_ns(halfPeriodns);
}

}