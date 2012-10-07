//
// Speaker.cpp
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#include "Speaker.h"
using namespace ecrobot;


//=============================================================================
// Constructor
Speaker::Speaker(void){}

//=============================================================================
// play a tone sound
void Speaker::playTone(U32 freq, U32 duration, U32 volume)
{
	freq = (freq > MAX_TONE_FREQ)? MAX_TONE_FREQ:((freq < MIN_TONE_FREQ)? MIN_TONE_FREQ:freq);
	volume  = (volume > 100)? 100:volume;
	ecrobot_sound_tone(freq, duration, volume);
}

//=============================================================================
// play 8bit monochnome PCM WAV file 
S16 Speaker::playWav(const CHAR* file, U32 length, U32 volume)
{
	volume = (volume > 100)? 100:volume;
	return static_cast<S16>(ecrobot_sound_wav(file, length, -1, volume));
}

