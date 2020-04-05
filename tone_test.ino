#include <Tone.h>
#include "melody.h"
const int first_buzzer_pin = 11;
const int second_buzzer_pin = 9;
Tone notePlayer[2];

unsigned int last_time_1 = 0;
int position_1 = 0;
unsigned int last_time_2 = 0;
int position_2 = 0;

void setup(void)
{
  notePlayer[0].begin(first_buzzer_pin);
  notePlayer[1].begin(second_buzzer_pin);
  notePlayer[0].play(0);
  notePlayer[1].play(0);
  notePlayer[0].stop();
  notePlayer[1].stop();
  last_time_1 = millis();
  last_time_2 = millis();
  
}

void play(Tone& tone_,unsigned int& last_time_,int& position_,const volatile uint16_t* melody,const volatile uint16_t* duration,int length_) {
    if(position_ != -1){
        if(pgm_read_word(&melody[position_]) != 0){
            tone_.play(pgm_read_word(&melody[position_]));
        }else {
            tone_.stop();
        }
        if(millis() - last_time_ > (unsigned long)(TEMP_OF_MUSIC/pgm_read_word(&duration[position_]))){
            position_++;
            tone_.stop();
            last_time_ = millis();
        }
   }
   if(position_ >= length_){
        last_time_ = millis();
        position_ = -1;
        tone_.stop();
   }
}

void loop(void)
{
    play(notePlayer[0],last_time_1,position_1,&melody[0],&duration[0],sizeof(melody)/sizeof(melody[0]));
    play(notePlayer[1],last_time_2,position_2,&melody2[0],&duration2[0],sizeof(melody2)/sizeof(melody2[0]));
}
