// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cAnimation.h"



cAnimation::cAnimation()
{
}


cAnimation::cAnimation(std::string animType, std::string name, int start, int end, float animDuration)
{
	this->animType = animType;
	this->name = name;
	this->start = start;
	this->end = end;
	this->animDuration = animDuration;
}

cAnimation::~cAnimation()
{
}
