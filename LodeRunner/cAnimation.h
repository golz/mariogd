// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include "Globals.h"
class cAnimation
{
public:
	cAnimation(std::string animType, std::string name, int start, int end, float animDuration);
	cAnimation();
	~cAnimation();
	
	std::string Name() const { return name; }
	void Name(std::string val) { name = val; }
	int Start() const { return start; }
	void Start(int val) { start = val; }
	int End() const { return end; }
	void End(int val) { end = val; }
	std::string AnimType() const { return animType; }
	void AnimType(std::string val) { animType = val; }
	float AnimDuration() const { return animDuration; }
	void AnimDuration(float val) { animDuration = val; }
private:
	std::string name;
	int start, end;
	std::string animType;
	float animDuration;
};

