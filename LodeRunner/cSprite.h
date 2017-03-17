// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include "Globals.h"
class cSprite
{
public:
	cSprite(GLuint texture, float x0, float y0, float x1, float x2);
	cSprite();
	~cSprite();
	GLuint Texture() const { return texture; }
	void Texture(GLuint val) { texture = val; }
	float Y1() const { return y1; }
	void Y1(float val) { y1 = val; }
	float X0() const { return x0; }
	void X0(float val) { x0 = val; }
	float Y0() const { return y0; }
	void Y0(float val) { y0 = val; }
	float X1() const { return x1; }
	void X1(float val) { x1 = val; }
private:
	GLuint texture;
	float x0, y0, x1, y1;
};

