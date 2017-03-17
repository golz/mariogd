#pragma once
#include"Globals.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cAnimControl.h"
#include "cGameObject.h"

class cEnemy :public cGameObject
{
private :
	cAnimControl *animControl;
	std::vector<cSprite*> *enemySheet;
	float x, y;
	int velocityx;
	int width, height;
	bool keys[255];
	bool isGroundCollide;
	bool isLeftCollide;
	bool isRightCollide;
	bool isCeilCollide;
public:
	cEnemy(std::vector<cSprite*> *enemySheet, float x, float y, int width, int height)
		:enemySheet(enemySheet), x(x), y(y), width(width), height(height) {}
	cEnemy();
	~cEnemy();
	int Height() const { return height; }
	void Height(int val) { height = val; }
	int Width() const { return width; }
	void Width(int val) { width = val; }
	float X() const { return x; }
	void X(float val) { x = val; }
	float Y() const { return y; }
	void Y(float val) { y = val; }
	bool Intersect(float x0, float y0, float x1, float y1);
	bool IsGroundCollide() const { return isGroundCollide; }
	void IsGroundCollide(bool val) { isGroundCollide = val; }
	bool IsLeftCollide() const { return isLeftCollide; }
	void IsLeftCollide(bool val) { isLeftCollide = val; }
	bool IsRightCollide() const { return isRightCollide; }
	void IsRightCollide(bool val) { isRightCollide = val; }
	bool IsCeilCollide() const { return isCeilCollide; }
	void IsCeilCollide(bool val) { isCeilCollide = val; }

	// Inherited via cGameObject
	virtual void Render() override;
	virtual void Init() override;
	virtual void Update(float tpf = 0.0333) override;
	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadMouse(int button, int state, int x, int y) override;

};

