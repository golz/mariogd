// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include "Globals.h"
#include "cGameObject.h"
#include <map>

class cScene
{
protected:
	std::map<cGameObject*, cGameObject*> sceneObject;
public:
	cScene();
	~cScene();
	
	virtual void addGameObject(cGameObject *o);

	virtual void removeGameObject(cGameObject *o);

	/**
	method that will be called first and only once when 
	*/
	virtual void Init();

	/**
	method that will be called each frame, use this to update the scene/game logic
	*/
	virtual void Update(float tpf = 0.0333);

	/**
	method that will be called each frame after update been 
	*/
	virtual void Render();
	
	/**
	Read normal keyboard input such as [a...z], this method been called from cGame
	*/
	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press);

	/**
	Read special keyboard input such as ctrl, this method been called from cGame
	*/
	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);

	/**
	Read mouse input, this method been called from cGame
	*/
	virtual void ReadMouse(int button, int state, int x, int y);

	/**
	Render String Example
	*/
	void renderBitmapString(
		float x,
		float y,
		float z,
		void *font,
		char *string,
		float r,
		float g,
		float b) {

		glColor3f(r, g, b);
		char *c;
		glRasterPos3f(x, y, z);
		for (c = string; *c != '\0'; c++) {
			glutBitmapCharacter(font, *c);
		}
		glColor3f(1.0f, 1.0f, 1.0f);

	}
};

