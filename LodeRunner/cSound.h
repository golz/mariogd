// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once

#pragma comment(lib, "fmodex_vc.lib" ) // fmod library

#include <fmod.hpp> //fmod c++ header

//Sound array size
#define NUM_SOUNDS 15

//Sound identifiers
#define BACKGROUND_MUSIC	0
#define MARIO_STOMP 1
#define MARIO_DIE 2
#define MARIO_JUMP 3


class cSound
{
public:
	static cSound& getInstance()
	{
		static cSound instance;
		return instance;
	}

	bool Load();
	void Play(int sound_id);
	void StopAll();
	void Update();

	FMOD::System*     system; //handle to FMOD engine
	FMOD::Sound*      sounds[NUM_SOUNDS]; //sound that will be loaded and played
	FMOD::Channel*    backgroundMusic;
	FMOD::Channel*    marioStomp;
	FMOD::Channel*    marioDie;
	FMOD::Channel*	  marioJump;
	FMOD::DSP*        dspSmoothStop;
private:
	~cSound(void);
	cSound(void);
	cSound(cSound const&) = delete;
	void operator=(cSound const&) = delete;
};