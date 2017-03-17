// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#define _CRT_SECURE_NO_WARNINGS
#include "cMenuScene.h"
#include "cLevel1Scene.h"
#include "cGame.h"
#include "cSound.h"
#include <iostream>

cMenuScene::cMenuScene()
{

}

cMenuScene::~cMenuScene()

{

}
int HighScore = 0;
void cMenuScene::Init()
{
	/*Load*/
	FILE *f = fopen("Levels/highscore.txt", "r");
	if (f) {
		while (!feof(f)) {
			fscanf(f, "%d\n", &HighScore);
		}
	}
	fclose(f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.top = GAME_HEIGHT;
	visible_area.bottom = 0;
	visible_area.left = 0;
	visible_area.right = GAME_WIDTH;
	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cSound::getInstance().Load();
	cSound::getInstance().Play(BACKGROUND_MUSIC);
}

void cMenuScene::Update(float tpf /*= 0.0333*/)
{
}
void renderBackground() 
{
	GLuint tex_id = cAssetManager::getInstance().GetID(MENU_IMAGE);
	int tex_w, tex_h;
	cAssetManager::getInstance().GetSize(tex_id, &tex_w, &tex_h);

	//background render
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	for (int j = -15; j < 15; j++) {
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);	glVertex3i(j * 600, 0, 100);
		glTexCoord2f(1, 1);	glVertex3i((j + 1) * 800, 0, 100);
		glTexCoord2f(1, 0);	glVertex3i((j + 1) * 800, 600, 100);
		glTexCoord2f(0, 0);	glVertex3i(j * 800, 600, 100);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

int buttonPosX1 = 200;
int buttonPosX2 = 422;
int buttonPosY1 = 435;
int buttonPosY2 = 449;
void cMenuScene::Render()
{
	renderBackground();
	renderBitmapString(280, 200, 9, GLUT_BITMAP_HELVETICA_18, "Click Anywhere to Start the Game", 1, 1, 1);
	renderBitmapString(300, 180, 9, GLUT_BITMAP_8_BY_13, "Press Arrow Up    : Jump", 1, 1, 1);
	renderBitmapString(300, 165, 9, GLUT_BITMAP_8_BY_13, "Press Arrow Left  : Move Left", 1, 1, 1);
	renderBitmapString(300, 150, 9, GLUT_BITMAP_8_BY_13, "Press Arrow Right : Move Right", 1, 1, 1);

	//High score
	char lblHighScore[50];
	strcpy(lblHighScore, "High Score : ");
	char highscore[50] = { '\0' };
	sprintf(highscore, "%d", HighScore);
	strcat(lblHighScore, highscore);
	strcat(lblHighScore, " pts");
	renderBitmapString(0, 5, 9, GLUT_BITMAP_9_BY_15,lblHighScore, 1, 1, 1);
}

void cMenuScene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{

}

void cMenuScene::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{

}

void cMenuScene::ReadMouse(int button, int state, int x, int y)
{
	std::cout << "Button " << button << " State : " << state << " ( "<< x <<", "<< y <<")" <<std::endl;
	if (state == 1)
	{
		cGame::getInstance().UpdateScene(new cLevel1Scene(HighScore));
		cSound::getInstance().StopAll();
	}
}
