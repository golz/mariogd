// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once

#include "cSound.h"
#include "cAssetManager.h"
#include "cRect.h"
#include "cScene.h"

#define GAME_WIDTH	800
#define GAME_HEIGHT 600

class cGame
{
public:
	static cGame& getInstance()
	{
		static cGame instance;
		return instance;
	}
	
	/**
	Main loop to be called from GLUTMain, and use to call init update render method
	*/
	bool Loop();

	/**
	Read normal keyboard input such as [a...z]
	*/
	void ReadKeyboard(unsigned char key, int x, int y, bool press);

	/**
	Read special keyboard input such as ctrl
	*/
	void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);

	/**
	Read mouse input
	*/
	void ReadMouse(int button, int state, int x, int y);

	/**
	called once each new scene applied
	*/
	bool Init();

	/**
	Game main loop, in this engine the default frame rate is 30 fps
	so we really need to modifiy the time per frame(tpf)
	*/
	bool Update(float tpf=0.0333);

	/**
	Reshape use to justify the viewport width and height to match the frame width height
	so we can scretch the game view
	*/
	void Reshape(int w, int h);

	/**
	Game render output, use to render any sprite or text to screen
	*/
	void Render();

	/**
	Plan to change to the new scene after end of current update
	At the end of the scene, RealUpdateScene function will be called to change active_scene to next_scene
	*/
	void UpdateScene(cScene *scene);
private:
	~cGame(void);
	cGame(void);
	cGame(cGame const&) = delete;
	void operator=(cGame const&) = delete;

	unsigned char keys[256];
	bool bSceneValid = true;
	bool bIsFirst = true;
	
	/**
	Current active scene that being use
	*/
	cScene *active_scene;

	/**
	Next scene that will be active after end of current Update
	*/
	cScene *next_scene;

	/**
	Default camera viewport to use on the ortographic camera
	*/
	cRect visible_area;

	/**
	Apply next scene to be the active scene
	*/
	void RealUpdateScene();
};
