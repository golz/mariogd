// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include "Globals.h"
#include "cScene.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cRect.h"
#include "cTile.h"
#define TOTAL_TILE_Y 18
#define TOTAL_TILE_X 1000
#define TILE_SIZE 64
#define TEXTURE_TILE_SIZE 128


class cLevel1Scene:public cScene
{
public:
	cLevel1Scene(int val);
	~cLevel1Scene();
	bool Load();
	void renderStatus();
	int highscore;
	cRect visible_area;
	std::vector<cTile*> Stage;
	std::vector<cEnemy*> Enemies;
	
	cPlayer *player;
	
	void UpdateStatus();
	void spawnEnemy(int count_enemy);
	void ResetAllStatus();

	virtual void Render();

	virtual void Init();

	virtual void Update(float tpf = 0.0333);

	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press);

	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);

	virtual void ReadMouse(int button, int state, int x, int y);

	void CheckPlayerGroundCollision();

	void CheckPlayerSideCollision();

	void CheckPlayerStompEnemy();

	void CheckPlayerKilledByEnemy();

	void UpdateCamera();
private:
	bool keys[255];
};

