// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include "cScene.h"
#include "cRect.h"
class cMenuScene:public cScene
{
public:
	cMenuScene();
	~cMenuScene();
	int High_Score;

	virtual void Init() override;

	virtual void Update(float tpf = 0.0333) override;

	virtual void Render() override;

	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press) override;

	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press) override;

	virtual void ReadMouse(int button, int state, int x, int y) override;

private:
	bool keys[255];
	cRect visible_area;
};

