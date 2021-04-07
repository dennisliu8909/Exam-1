#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);

InterruptIn button_up(D6);
InterruptIn button_down(D9);
InterruptIn button_select(D3);
AnalogOut aout(D7);
AnalogIn ain(D11);
Thread t;
EventQueue queue(32 * EVENTS_EVENT_SIZE);

float slew_rate = 1.0;
float freq = 4.166, T = 0.24;
float output = 1.0;
int slope_width = 80;

void screen_print() {
    uLCD.locate(1, 2);
    uLCD.printf("%4f", slew_rate);
}

void screen_select() {
    uLCD.locate(1, 3);
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.printf("rate selected");
}

void increasing() {
    queue.call(screen_print);
    if (slew_rate >= 0.125 && slew_rate < 1.0)
        slew_rate *= 2;
    else    
        slew_rate = slew_rate;   
}

void decreasing() {
    queue.call(screen_print);
    if (slew_rate > 0.125 && slew_rate <= 1.0)
        slew_rate /= 2;
    else    
        slew_rate = slew_rate; 
}

void select_slew() {
    queue.call(screen_print);
    queue.call(screen_select);
    slope_width = 80 * slew_rate;
}

int main() {
    uLCD.text_width(2);
    uLCD.text_height(2);

    t.start(callback(&queue, &EventQueue::dispatch_forever));
    button_up.rise(&increasing);
    button_down.rise(&decreasing);
    button_select.rise(&select_slew);
    int i = 0;

    while (1) {
        if (i >= 240)
            i = 0;
        if (i < slope_width) {
            aout = output;
            output += 1/1.1/slope_width;
        }
        else if (i >= 240 - slope_width) {
            aout = output;
            output -= 1/1.1/slope_width;
        }
        i++;
        ThisThread::sleep_for(1ms);
    }

}