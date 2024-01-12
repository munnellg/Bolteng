#ifndef SOKOBAN_AUDIO_H
#define SOKOBAN_AUDIO_H

#include "settings.h"

#define AUDIO_SAWTOOTH 0
#define AUDIO_SQUARE   1
#define AUDIO_TRIANGLE 2
#define AUDIO_SINE     3

int audio_init(struct Settings const &settings);
void set_freq(int freq);
void set_amplitude(int amplitude);
int get_amplitude();
void set_waveform(int select);
void play_sine();
void audio_quit();

#endif
