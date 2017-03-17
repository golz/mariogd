// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cSprite.h"



cSprite::cSprite()
{
}


cSprite::cSprite(GLuint texture, float x0, float y0, float x1, float y1)
{
	this->texture = texture;
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;
}

cSprite::~cSprite()
{
}
