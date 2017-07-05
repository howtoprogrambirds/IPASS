#include "buzzer.hpp"

buzzer::buzzer(hwlib::target::pin_out sig):
    sig(sig)
{}

void buzzer::tone(int hertz){
    int halfPeriodns = (period/hertz)/2;
    sig.set(1);
    hwlib::wait_ns(halfPeriodns);
    sig.set(0);
    hwlib::wait_ns(halfPeriodns);
}

