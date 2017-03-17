#pragma once
class cGameObject
{
public:
	cGameObject();
	~cGameObject();

	virtual void Render()=0;
	virtual void Init()=0;
	virtual void Update(float tpf = 0.0333)=0;
	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press)=0;
	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)=0;
	virtual void ReadMouse(int button, int state, int x, int y)=0;
};

