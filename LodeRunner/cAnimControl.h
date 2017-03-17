// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include "Globals.h"
#include "cAnimation.h"
class cAnimControl
{
public:
	cAnimControl();
	~cAnimControl();

	/**
	add active anim to the map
	*/
	void AddAnim(std::string animType, std::string name, int start, int end, float duration);
	
	/**
	remove anim from the map
	*/
	void RemoveAnim(std::string name);
	
	/**
	replace old anim to new anim
	*/
	void SetAnim(std::string animType, std::string name, int start, int end, float duration);
	
	/**
	set active animation to some animation that already on the map
	*/
	void SetActiveAnim(std::string name);

	/**
	update coundown and update animation index
	*/
	void UpdateAnim(float tpf=0.0333);

	int Index() const { return index; }
	std::string ActiveName() const { return activeName; }
private:
	std::map<std::string, cAnimation> animStatus;
	std::string activeName;
	cAnimation activeAnimation;
	int index = 0;
	float counter = 0;
};

