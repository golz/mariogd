// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cScene.h"


cScene::cScene()
{
}

cScene::~cScene()
{
}

void cScene::addGameObject(cGameObject * o)
{
	sceneObject[o] = o;
	o->Init();
}

void cScene::removeGameObject(cGameObject * o)
{
	if (sceneObject.find(o)!=sceneObject.end()) {
		sceneObject.erase(o);
		delete o;
		int a = 4 + 4;
	}
}

void cScene::Init()
{
}

void cScene::Update(float tpf)
{
	for (auto i = sceneObject.begin(); i != sceneObject.end(); i++) {
		i->second->Update(tpf);
	}
}

void cScene::Render()
{
	for (auto i = sceneObject.begin(); i != sceneObject.end(); i++) {
		i->second->Render();
	}
}

void cScene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	for (auto i = sceneObject.begin(); i != sceneObject.end(); i++) {
		i->second->ReadKeyboard(key, x, y, press);
	}
}

void cScene::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	for (auto i = sceneObject.begin(); i != sceneObject.end(); i++) {
		i->second->ReadSpecialKeyboard(key, x, y, press);
	}
}

void cScene::ReadMouse(int button, int state, int x, int y)
{
	for (auto i = sceneObject.begin(); i != sceneObject.end(); i++) {
		i->second->ReadMouse(button, state, x, y);
	}
}
