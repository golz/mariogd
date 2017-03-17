// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include"Globals.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cAnimControl.h"
#include "cGameObject.h"

class cPlayer:public cGameObject
{
private:
	cAnimControl *animControl;
	std::vector<cSprite*> *playerSheet;
	float x, y;
	int width, height;
	bool keys[255];
	bool isGroundCollide;
	bool isLeftCollide;
	bool isRightCollide;
	bool isCeilCollide;

	bool isStompCollide;
	bool isKilledCollide;

	float jumpPower = 300;
	float currJumpPower = 0;
public:
	cPlayer(std::vector<cSprite*> *playerSheet, float x, float y, int width, int height)
		:playerSheet(playerSheet), x(x), y(y), width(width), height(height) {}
	cPlayer();
	~cPlayer();
	void MarioJump();
	int Height() const { return height; }
	void Height(int val) { height = val; }
	int Width() const { return width; }
	void Width(int val) { width = val; }
	float X() const { return x; }
	void X(float val) { x = val; }
	float Y() const { return y; }
	void Y(float val) { y = val; }

	void setCurrJumpPower(float val) { currJumpPower = val; }

	bool Intersect(float x0, float y0, float x1, float y1);
	bool IsGroundCollide() const { return isGroundCollide; }
	void IsGroundCollide(bool val) { isGroundCollide = val; }
	bool IsLeftCollide() const { return isLeftCollide; }
	void IsLeftCollide(bool val) { isLeftCollide = val; }
	bool IsRightCollide() const { return isRightCollide; }
	void IsRightCollide(bool val) { isRightCollide = val; }
	bool IsCeilCollide() const { return isCeilCollide; }
	void IsCeilCollide(bool val) { isCeilCollide = val; }
	bool IsStompCollide() const { return isStompCollide; }
	void IsStompCollide(bool val) { isStompCollide = val; }
	bool IsKilledCollide() const { return isKilledCollide; }
	void IsKilledCollide(bool val) { isKilledCollide = val; }

	// Inherited via cGameObject
	virtual void Render() override;
	virtual void Init() override;
	virtual void Update(float tpf = 0.0333) override;
	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadMouse(int button, int state, int x, int y) override;
};

