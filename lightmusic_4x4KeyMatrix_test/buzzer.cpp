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
#include <cmath>

namespace lightMusic{
 
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
    int halfPeriodNs = ((period/hertz)/2);
    
    
    //sets halfPeriod the signal on 1 and halftime the signal on 0
    //     halfP          halfP
    // ------------------------------>
    //_______1______                ______
    //|             |               |
    //|             |               |
    //|             |               |
    //|             |_______0_______|
    sig.set(1);
    hwlib::wait_ns(halfPeriodNs);
    sig.set(0);
    hwlib::wait_ns(halfPeriodNs);
}

//calculate the hertz by given midiKeyNumber and returns the hertz in int
int buzzer::keyMidiMapToHertz(int keyMidiNumber){
    
    int note = keyMidiNumber - ((keyMidiNumber/12) * 12);
    int octave = (keyMidiNumber/12);
    int hertzOctave = 16 * pow(2,octave);
    int hertzNote = (((16 * pow(2,octave+1))-(16 * pow(2,octave)))/12*note);
    return hertzOctave+hertzNote;
    
}

}