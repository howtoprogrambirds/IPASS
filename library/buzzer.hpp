#ifndef BUZZER_HPP
#define BUZZER_HPP
#include "hwlib.hpp"

namespace lightmusic{

class buzzer{
private:
    int period = 1000000000;
    hwlib::target::pin_out sig;
public:
    buzzer(hwlib::target::pin_out sig);
    void tone(int hertz);
};

}
#endif // BUZZER_HPP
