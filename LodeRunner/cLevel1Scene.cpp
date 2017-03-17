// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cLevel1Scene.h"
#include "cAssetManager.h"
#include "cGame.h"
#include "cMenuScene.h"
#include "cSound.h"
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)

//Status
int current_wave = 1;
int	killEnemy = 0;
int overall_score = 0;
bool isMusicPaused = false;
int hscore = 0;
cLevel1Scene::cLevel1Scene(int val)
{
	hscore = val;
}

cLevel1Scene::~cLevel1Scene()
{
}

bool cLevel1Scene::Load()
{
	FILE *f = fopen("Levels/wall.txt", "r");
	if (f) {
		int i = 0;
		while (!feof(f)) {
			char temp[1000];
			fscanf(f, "%[^\n]\n", &temp);
			for (int j = 0; j < strlen(temp); j++) {
				if (temp[j] != ' ') {
					cTile *t = new cTile(cAssetManager::getInstance().tiles->at(0), j * 32, (TOTAL_TILE_Y - i) * 32, 32, 32, j, i);
					Stage.push_back(t);
				}
			}
			++i;

		}
	}
	else {
		return false;
	}
	fclose(f);
}
void cLevel1Scene::Init()
{
	srand(time(NULL));
	/* First Load */
	Load();
	/* Play Background Music */
	cSound::getInstance().Load();
	cSound::getInstance().Play(BACKGROUND_MUSIC);

	player = new cPlayer(cAssetManager::getInstance().player, 100, 200, TILE_SIZE, TILE_SIZE);
	addGameObject(player);

	//Summon Enemy
	spawnEnemy(current_wave);

}
void renderLevelBackground()
{
	GLuint tex_id = cAssetManager::getInstance().GetID(LEVEL_IMAGE);
	int tex_w, tex_h;
	cAssetManager::getInstance().GetSize(tex_id, &tex_w, &tex_h);

	//background render
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	for (int j = -15; j < 15; j++) {
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);	glVertex3i(j * 600, 0, 100);
		glTexCoord2f(1, 1);	glVertex3i((j + 1) * 600, 0, 100);
		glTexCoord2f(1, 0);	glVertex3i((j + 1) * 600, 600, 100);
		glTexCoord2f(0, 0);	glVertex3i(j * 600, 600, 100);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}
void cLevel1Scene::spawnEnemy(int count_enemy)
{
	//Clear First
	while (!Enemies.empty())
	{
		Enemies.pop_back();
	}
	for (int i = 0; i < count_enemy; i++)
	{
		cEnemy *newEnemy = new cEnemy(cAssetManager::getInstance().enemy, rand() % 1400 + 100,62, TILE_SIZE, TILE_SIZE);
		Enemies.push_back(newEnemy);
		newEnemy->Init();
	}
}

void cLevel1Scene::renderStatus()
{
	char lblScore[50];
	strcpy(lblScore, "Score : ");
	char lblHScore[50];
	strcpy(lblHScore, "High Score : ");
	char lblWave[50];
	strcpy(lblWave, "Wave : ");
	char lblMusic[50];
	strcpy(lblMusic, "Music(M) : ");
	char score[50] = {'\0'};
	sprintf(score, "%d", overall_score);
	char hsc[50] = { '\0' };
	sprintf(hsc, "%d", hscore);
	char wave[50] = {'\0'};
	sprintf(wave, "%d", current_wave);
	
	strcat(lblScore, score);
	strcat(lblScore, " pts");
	strcat(lblHScore, hsc);
	strcat(lblHScore, " pts");
	strcat(lblWave, wave);
	strcat(lblMusic, (isMusicPaused == false ? "Playing" : "Paused"));

	glColor3f(1, 1, 1);
	renderBitmapString(player->X() - 170, 550, 1, GLUT_BITMAP_9_BY_15, lblScore,1,1,1);
	renderBitmapString(player->X() + 5, 550, 1, GLUT_BITMAP_9_BY_15, lblWave, 1,1,1);
	renderBitmapString(player->X() + 150, 550, 1, GLUT_BITMAP_9_BY_15, lblMusic,1,1,1);
	renderBitmapString(player->X() + 350, 550, 1, GLUT_BITMAP_9_BY_15, lblHScore, 1, 1, 1);

}
void cLevel1Scene::Render()
{
	cScene::Render();
	//background render
	renderLevelBackground();
	//status render
	renderStatus();
	//tile render
	for (int j = 0; j < Stage.size(); j++) {
		Stage[j]->Render();
	}
	//enemy render
	for (int j = 0; j < Enemies.size(); j++) {

		Enemies[j]->Render();
		Enemies[j]->Update();
	}
}
void cLevel1Scene::UpdateStatus()
{
	if (killEnemy == Enemies.size())
	{
		current_wave++;
		spawnEnemy(current_wave);
		killEnemy = 0;
	}
	system("cls");
	printf("Current Wave\t: %d\n", current_wave);
	printf("Overall Score\t: %d pts\n", overall_score);
	printf("High Score\t: %d pts, Pursuited : %d\n", hscore,overall_score > hscore);
	printf("Enemy Count\t: %d\n",Enemies.size());
	printf("Kill Enemy\t: %d\n", killEnemy);
	printf("Music On/Of\t: %s\n", isMusicPaused==false?"Playing":"Paused");
}
int count = 0;
void cLevel1Scene::Update(float tpf /*= 0.0333*/)
{
	cScene::Update(tpf);
	if (player->IsKilledCollide() == false)
	{
		CheckPlayerGroundCollision();
		CheckPlayerSideCollision();

		CheckPlayerStompEnemy();
		CheckPlayerKilledByEnemy();

		UpdateCamera();
		UpdateStatus();
	}
	else if (player->IsKilledCollide() == true) {
		count += 1;
		if(count == 2)
			Sleep(800);
		if(count < 8)
			player->Y(60);
		if (count == 8)
		{
			player->setCurrJumpPower(300);
		}

		if (player->Y() < -500) {
			ResetAllStatus();
			cGame::getInstance().UpdateScene(new cMenuScene());
		}
	}
}
void cLevel1Scene::ResetAllStatus()
{
	//Kalau udah clear berarti gamenya overkan
	if (overall_score > hscore)
	{
		FILE *in = fopen("Levels/highscore.txt", "w");
		if (in)
		{
			fprintf(in, "%d\n", overall_score);
		}
		fclose(in);
		printf("Success update score");
		Sleep(500);
	}
	overall_score = 0;
	current_wave = 0;
	killEnemy = 0;
	isMusicPaused = false;
	player->IsKilledCollide(false);
	count = 0;
	//Clear First
	while (!Enemies.empty())
	{
		Enemies.pop_back();
	}
}
void cLevel1Scene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	cScene::ReadKeyboard(key, x, y, press);
	if (press)
	{
		keys[key] = true;
		if (key == 'M' || key == 'm')
		{
			if (isMusicPaused)
			{
				cSound::getInstance().backgroundMusic->setPaused(false);
				isMusicPaused = !isMusicPaused;
			}
			else if (!isMusicPaused)
			{
				cSound::getInstance().backgroundMusic->setPaused(true);
				isMusicPaused = !isMusicPaused;
			}
		}
	}
	else
	{
		keys[key] = false;
	}
	if (key == 27)
	{
		ResetAllStatus();
		cSound::getInstance().StopAll();
		cGame::getInstance().UpdateScene(new cMenuScene());
	}
}

void cLevel1Scene::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	cScene::ReadSpecialKeyboard(key, x, y, press);
	
	
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cLevel1Scene::ReadMouse(int button, int state, int x, int y)
{
	cScene::ReadMouse(button, state, x, y);
}

void cLevel1Scene::CheckPlayerGroundCollision()
{
	bool groundFlag = false;
	bool ceilFlag = false;
	for (int i = 0; i < Stage.size(); i++)
	{
		if (Stage.at(i)->Intersect(
			player->X() + 30,
			player->Y(),
			player->X() + player->Width() - 30,
			player->Y()
		)) {
			groundFlag = true;
		}
		if (Stage.at(i)->Intersect(
			player->X() + 30,
			player->Y() + 30,
			player->X() + player->Width() - 30,
			player->Y() + player->Height() - 30
		)) {
			ceilFlag = true;
		}
	}
	if (groundFlag)
		player->IsGroundCollide(true);
	else
		player->IsGroundCollide(false);
	if (ceilFlag)
		player->IsCeilCollide(true);
	else
		player->IsCeilCollide(false);

}

void cLevel1Scene::CheckPlayerStompEnemy()
{
	for (int i = 0; i < Enemies.size(); i++)
	{
		if (Enemies.at(i)->Intersect(
			player->X() + 30,
			player->Y(),
			player->X() + player->Width() - 30,
			player->Y()
		)) {
			Enemies[i]->Y(-100);
			player->setCurrJumpPower(200);
			cSound::getInstance().Play(MARIO_STOMP);
			killEnemy += 1;
			overall_score += 100;
			return;
		}
	}
}
void cLevel1Scene::CheckPlayerKilledByEnemy()
{
	for (int i = 0; i < Enemies.size(); i++)
	{
		if (player->X() > Enemies.at(i)->X() - 20 && player->X() < Enemies.at(i)->X() + 20 && player->Y() < Enemies.at(i)->Y())
		{
			player->IsKilledCollide(true);
			cSound::getInstance().StopAll();
			cSound::getInstance().Play(MARIO_DIE);
		}
	}
}

void cLevel1Scene::CheckPlayerSideCollision()
{
	bool rightCollision = false;
	bool leftCollision = false;
	for (int i = 0; i < Stage.size(); i++)
	{
		if (Stage.at(i)->Intersect(
			player->X(),
			player->Y() + 30,
			player->X() + 50,
			player->Y() + player->Height() - 30
		)) {
			leftCollision = true;
		}
		if (Stage.at(i)->Intersect(
			player->X() + player->Width(),
			player->Y() + 30,
			player->X() + player->Width(),
			player->Y() + player->Height() - 30
		)) {
			rightCollision = true;
		}
	}
	if (rightCollision)
		player->IsRightCollide(true);
	else
		player->IsRightCollide(false);
	if (leftCollision)
		player->IsLeftCollide(true);
	else
		player->IsLeftCollide(false);
}
void cLevel1Scene::UpdateCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	visible_area.top = GAME_HEIGHT;
	visible_area.bottom = 0;
	visible_area.left = player->X() - GAME_WIDTH / 2 + 200;
	visible_area.right = player->X() + GAME_WIDTH / 2 + 200;
	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
