// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cPlayer.h"
#include "cSound.h"
#define LOOK_AT_LEFT 1
#define LOOK_AT_RIGHT 2

cPlayer::cPlayer()
{
}


cPlayer::~cPlayer()
{
}

void cPlayer::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, playerSheet->at(animControl->Index())->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x, y, 49);
	glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x + Width(), y, 49);
	glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x + Width(), y + Height(), 49);
	glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x, y + Height(), 49);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void cPlayer::Init()
{
	animControl = new cAnimControl();
	animControl->AddAnim("StraightLoop", "walk_forward", 6, 7, 0.1f);
	animControl->AddAnim("StraightLoop", "walk_backward", 8, 9, 0.1f);
	animControl->AddAnim("NoLoop", "mario_die", 11, 11, 0.2f);
	animControl->AddAnim("NoLoop", "jump_right", 4, 4, 0.2f);
	animControl->AddAnim("NoLoop", "jump_left", 10, 10, 0.2f);
	animControl->AddAnim("NoLoop", "idle_right", 5, 5, 0.2f);
	animControl->AddAnim("NoLoop", "idle_left", 13, 13, 0.2f);

	IsKilledCollide(false);
}
int movementspeed = 300;
bool jumpMode = false;
int lookAt = LOOK_AT_RIGHT;
void cPlayer::Update(float tpf /*= 0.0333*/)
{
	animControl->UpdateAnim(tpf);

	/* Animation Controller */
	if (IsKilledCollide() == false)
	{

		if (keys[GLUT_KEY_RIGHT] && jumpMode == false)
		{
			if (animControl->ActiveName() != "walk_forward" && (animControl->ActiveName() != "jump_left" || animControl->ActiveName() != "jump_right")) {
				animControl->SetActiveAnim("walk_forward");
				lookAt = LOOK_AT_RIGHT;
			}
		}
		else if (keys[GLUT_KEY_LEFT] && jumpMode == false)
		{
			if (animControl->ActiveName() != "walk_backward" && (animControl->ActiveName() != "jump_left" || animControl->ActiveName() != "jump_right")) {
				animControl->SetActiveAnim("walk_backward");
				lookAt = LOOK_AT_LEFT;
			}
		}
		else if (keys[GLUT_KEY_UP])
		{
			if (lookAt == LOOK_AT_RIGHT)
			{
				if (animControl->ActiveName() != "jump_right")
					animControl->SetActiveAnim("jump_right");
			}
			else if (lookAt == LOOK_AT_LEFT)
			{
				if (animControl->ActiveName() != "jump_left")
					animControl->SetActiveAnim("jump_left");
			}
		}
		else
		{
			if (lookAt == LOOK_AT_RIGHT)
			{
				if (animControl->ActiveName() != "idle_right")
					animControl->SetActiveAnim("idle_right");
			}
			else if (lookAt == LOOK_AT_LEFT)
			{
				if (animControl->ActiveName() != "idle_left")
					animControl->SetActiveAnim("idle_left");
			}
		}
		/* Gravity */
		if (!IsGroundCollide()) {
			y -= 300 * tpf;
			jumpMode = true;
		}
		else {
			jumpMode = false;
		}
	}
	else
	{
		if (animControl->ActiveName() != "mario_die")
			animControl->SetActiveAnim("mario_die");
		y -= 300 * tpf;
		jumpMode = true;
	}
	
	if (currJumpPower > 0) {
		currJumpPower -= 600 * tpf;
		if (!IsCeilCollide())
			y += 600 * tpf;
		else
		{
			jumpMode = false;
			currJumpPower = 0;
		}
			
	}
	if (jumpMode == false)
	{
		if (keys[GLUT_KEY_LEFT] && !IsLeftCollide() && !IsCeilCollide()) {
			x -= movementspeed * tpf;
		}
		if (keys[GLUT_KEY_RIGHT] && !IsRightCollide() && !IsCeilCollide()) {
			x += movementspeed * tpf;
		}
	}
	else if (jumpMode == true && IsKilledCollide() == false)
	{
		/* SET ANIM AGAIN */
		if (lookAt == LOOK_AT_RIGHT)
		{
			if (animControl->ActiveName() != "jump_right")
				animControl->SetActiveAnim("jump_right");
		}
		else if (lookAt == LOOK_AT_LEFT)
		{
			if (animControl->ActiveName() != "jump_left")
				animControl->SetActiveAnim("jump_left");
		}
		/* SET ANIM AGAIN */
		if (keys[GLUT_KEY_LEFT] && !IsLeftCollide()) {
			x -= movementspeed * tpf;
		}
		if (keys[GLUT_KEY_RIGHT] && !IsRightCollide()) {
			x += movementspeed * tpf;
		}
	}
}

void cPlayer::MarioJump()
{
	currJumpPower = jumpPower;
}

void cPlayer::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cPlayer::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	if (keys[GLUT_KEY_UP] && IsGroundCollide())
	{
		MarioJump();
		jumpMode = true;
		cSound::getInstance().Play(MARIO_JUMP);
	}
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cPlayer::ReadMouse(int button, int state, int x, int y)
{

}

bool cPlayer::Intersect(float x0, float y0, float x1, float y1)
{
	return x < x1 && x > x0 &&
		y < y1 && y > y0;
}
