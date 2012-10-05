//
// Speaker.h
//
// Copyright 2009 by Takashi Chikamasa, Jon C. Martin and Robert W. Kramer
//

#ifndef SPEAKER_H_
#define SPEAKER_H_

extern "C"
{
	#include "ecrobot_interface.h"
	#include "rtoscalls.h"
};

namespace ecrobot
{
/**
 * NXT speaker class
 */
class Speaker
{
public:
	/**
	 * Minimum frequency of tone.
	 */
	static const U32 MIN_TONE_FREQ = 33;

	/**
	 * Maximum frequency of tone.
	 */
	static const U32 MAX_TONE_FREQ = 1976;

	/**
	 * Constructor.
	 * @param -
	 * @return -
	 */
	Speaker(void);

	/**
	 * Play a tone sound.
	 * @param freq Tone frequency in Hz. MIN_TONE_FREQ to MAX_TONE_FREQ
	 * @param duration Tone duration in msec (10msec unit)
	 * @param volume Tone volume (0 to 100)
	 * @return -
	 */
	void playTone(U32 freq, U32 duration, U32 volume);
	
	/**
	 * Play an 8bit monochrome PCM WAV file
	 * @param file Head of a WAV file
	 * @param length Length of a WAV file
	 * @param volume Volume of WAV file (0 to 100)
	 * @return 1:succeeded/0:sound resource was busy/-1:unsupported file format
	 */
	S16 playWav(const CHAR* file, U32 length, U32 volume);
};
}
#endif
