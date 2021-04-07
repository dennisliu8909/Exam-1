#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);

InterruptIn button_up(D6);
InterruptIn button_down(D9);
InterruptIn button_select(D3);
AnalogOut aout(D7);
AnalogIn ain(D11);
Thread t, t_ADC;
EventQueue queue(32 * EVENTS_EVENT_SIZE);
EventQueue queue_ADC(32 * EVENTS_EVENT_SIZE);

float slew_rate = 1.0;
float freq = 4.166, T = 0.24;
int slope_width = 80;
float ADC[500];
float output = 0.0;
bool restart = 0;
bool print_end = 1;

void screen_print() {
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.locate(1, 2);
    uLCD.printf("%4f", slew_rate);
}

void screen_select() {
    uLCD.locate(1, 3);
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.printf("rate selected");
    uLCD.locate(1, 8);
    uLCD.printf("slope_width :%d", slope_width);
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

void sample() {
    int j = 0;

    while(1) {
        if (j >= 500) {
            j = 0;
        }
        if (print_end)
            ADC[j] = ain;
        j++;
        ThisThread::sleep_for(2ms);
    }
}

void print_ADC() {
    for (int i = 0; i < 500; i++) {
        printf("%.3f\r\n", ADC[i]);
    }
}


void select_slew() {
    restart = 1;
    print_end = 0;
    slope_width = 80 * slew_rate;
    queue.call(screen_print);
    queue.call(screen_select);
    queue.call(print_ADC);
    print_end = 1;
}

int main() {
    uLCD.text_width(2);
    uLCD.text_height(2);

    t.start(callback(&queue, &EventQueue::dispatch_forever));
    t_ADC.start(sample);
    button_up.rise(&increasing);
    button_down.rise(&decreasing);
    button_select.rise(&select_slew);
    int i = 0;

    while (1) {
        if (i >= 240 || restart) {
            i = 0;
            output = 0;
            restart = 0;
        }
        if (i < slope_width) {
            output += 1/1.1/slope_width;
        }
        else if (i >= 240 - slope_width) {
            output -= 1/1.1/slope_width;
        }
        aout = output;
        i++;
        ThisThread::sleep_for(1ms);
    }

}
