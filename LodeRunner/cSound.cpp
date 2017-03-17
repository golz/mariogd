// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cSound.h"

cSound::cSound(void)
{
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels
}

cSound::~cSound(void)
{
	for (int i = 0; i < NUM_SOUNDS; i++) sounds[i]->release();
	system->release();
}

bool cSound::Load()
{
	system->createStream("Sounds/mariobgm.mp3", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[BACKGROUND_MUSIC]);
	system->createStream("Sounds/mariostomp.wav", FMOD_SOFTWARE | FMOD_LOOP_OFF, 0, &sounds[MARIO_STOMP]);
	system->createStream("Sounds/mariodie.wav", FMOD_SOFTWARE | FMOD_LOOP_OFF, 0, &sounds[MARIO_DIE]);
	system->createStream("Sounds/mariojump.wav", FMOD_SOFTWARE | FMOD_LOOP_OFF, 0, &sounds[MARIO_JUMP]);
	//system->createStream("Sounds/ambient1.mp3", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT1]);
	return true;
}

void cSound::Play(int sound_id)
{
	if (sound_id == BACKGROUND_MUSIC) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[BACKGROUND_MUSIC], false, &backgroundMusic);
		backgroundMusic->setVolume(0.5f); //between 0 and 1
	}
	else if (sound_id == MARIO_STOMP) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[MARIO_STOMP], false, &marioStomp);
		marioStomp->setVolume(0.75f); //between 0 and 1
	}
	else if (sound_id == MARIO_DIE) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[MARIO_DIE], false, &marioDie);
		marioDie->setVolume(0.75f); //between 0 and 1
	}
	else if (sound_id == MARIO_JUMP) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[MARIO_JUMP], false, &marioJump);
		marioJump->setVolume(0.75f); //between 0 and 1
	}
	else system->playSound(FMOD_CHANNEL_FREE, sounds[sound_id], false, 0);
}

void cSound::StopAll()
{
	backgroundMusic->stop();
	marioStomp->stop();
	marioDie->stop();
}

void cSound::Update()
{
	system->update();
}