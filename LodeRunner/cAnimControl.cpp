// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cAnimControl.h"

cAnimControl::cAnimControl()
{
	counter = 0;
}


cAnimControl::~cAnimControl()
{
}

void cAnimControl::AddAnim(std::string animType, std::string name, int start, int end, float duration)
{
	animStatus[name] = cAnimation(animType, name, start, end, duration);// add an animation on a key base on name on hashmap
	SetActiveAnim(name);//set the latest added anim to be the active anim
}

void cAnimControl::RemoveAnim(std::string name)
{
	animStatus[name] = cAnimation();
}

void cAnimControl::SetAnim(std::string animType, std::string name, int start, int end, float duration)
{
	animStatus[name] = cAnimation(animType, name, start, end, duration);
}

void cAnimControl::SetActiveAnim(std::string name)
{
	activeAnimation = animStatus[name];
	activeName = name;
	index = animStatus[name].Start();
}

void cAnimControl::UpdateAnim(float tpf)
{
	counter += tpf;//increment the counter tpf
	if (counter >= activeAnimation.AnimDuration()) {//if counter time already pass the animation duration
		counter -= activeAnimation.AnimDuration();//decrease counter duration with the animation duration
		if (activeAnimation.AnimType() == "StraightLoop") {
			index++;
			if (index > activeAnimation.End()) index = activeAnimation.Start();//back to start if index already end
		}
		else if (activeAnimation.AnimType() == "RoundLoop") {
			//not implemented yet
		}
		else if (activeAnimation.AnimType() == "NoLoop") {
			if (index < activeAnimation.End()) index++;//increment only if index not already the last frame
		}
	}
}

