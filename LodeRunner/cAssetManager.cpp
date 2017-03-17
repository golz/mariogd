// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma warning(disable:4996)
#include "cAssetManager.h"
#include "Globals.h"

cAssetManager::cAssetManager(void) {}
cAssetManager::~cAssetManager(void) {}

int cAssetManager::GetID(int img)
{
	return textures[img].GetID();
}

void cAssetManager::GetSize(int img, int *w, int *h)
{
	textures[img].GetSize(w, h);
}

bool cAssetManager::LoadImage(int img, char *filename, int type)
{
	int res;

	res = textures[img].Load(filename, type);
	if (!res) return false;

	return true;
}
bool cAssetManager::Load()
{
	int res;

	/* Spritesheet Mario , File Name: spritesheet_mario.png */
	res = LoadImage(SPRITESHEET_PLAYERS, "Textures/Spritesheets/spritesheet_mario.png", GL_RGBA);
	if (!res) return false;
	float sprite_width = 1.0f / 6;
	float sprite_height = 1.0f / 2;
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			float x0, y0, x1, y1;
			x0 = sprite_width*i;
			x1 = sprite_width*(i + 1);
			y0 = sprite_height*j;
			y1 = sprite_height*(j + 1);
			player->push_back(new cSprite(GetID(SPRITESHEET_PLAYERS), x0, y0, x1, y1));

		}
	}
	
	
	/* Menu Scene Background */
	res = LoadImage(MENU_IMAGE, "Textures/PNG/Backgrounds/background.png",GL_RGBA);
	if (!res) return false;

	/* Level Scene Background */
	res = LoadImage(LEVEL_IMAGE, "Textures/PNG/Backgrounds/level.png", GL_RGBA);
	if (!res) return false;

	/* Wall */
	res = LoadImage(WALL, "Textures/Spritesheets/spritesheet_tiles.png", GL_RGBA);
	if (!res) return false;
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 16; i++) {
			float x0, y0, x1, y1;
			int tex_w, tex_h;
			GetSize(GetID(WALL), &tex_w, &tex_h);
			float sprite_width = 128.0f / tex_w;
			float sprite_height = 128.0f / tex_h;
			x0 = sprite_width*j;
			x1 = sprite_width*(j + 1);
			y0 = sprite_height*i;
			y1 = sprite_height*(i + 1);
			tiles->push_back(new cSprite(GetID(WALL), x0, y0, x1, y1));
		}
	}

	/* Spritesheet Enemy , File Name: spiresheet_enemy.png */
	res = LoadImage(SPRITESHEET_ENEMIES, "Textures/Spritesheets/spiresheet_enemy.png", GL_RGBA);
	if (!res) return false;
	float sprite_width1 = 1.0f / 2;
	float sprite_height1 = 1.0f / 1;
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			float x0, y0, x1, y1;
			x0 = sprite_width1*i;
			x1 = sprite_width1*(i + 1);
			y0 = sprite_height1*j;
			y1 = sprite_height1*(j + 1);
			enemy->push_back(new cSprite(GetID(SPRITESHEET_ENEMIES), x0, y0, x1, y1));

		}
	}

	return true;
}

