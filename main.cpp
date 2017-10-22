#include "mbed.h"
PwmOut speaker(p26);
Ticker sampletick;
DigitalOut myled(LED1);
//Plays Audio Clip using Array in Flash
//8-bit audio samples used on PWM pin
//setup const array in flash with audio values 
//from free wav file conversion tool at
//http://ccgi.cjseymour.plus.com/wavtocode/wavtocode.htm
//see https://os.mbed.com/users/4180_1/notebook/using-flash-to-play-audio-clips/
#include "cylon8bit.h"

#define sample_freq 11025.0
//get and set the frequency from wav conversion tool GUI
int i=0;

//interrupt routine to play next audio sample from array in flash
void audio_sample ()
{

    speaker = sound_data[i]/255.0;//scale to 0.0 to 1.0 for PWM
    i++;
    if (i>= NUM_ELEMENTS) {
        i = 0;
        sampletick.detach();
        myled = 0;
    }
}
int main()
{
    speaker.period(1.0/250000.0); //PWM freq >10X audio sample rate
    while(1) {
        myled = 1;
//use a ticker to play send next audio sample value to D/A
        sampletick.attach(&audio_sample, 1.0 / sample_freq);
//can do other things while audio plays with timer interrupts
        wait(10.0);
    }
}
