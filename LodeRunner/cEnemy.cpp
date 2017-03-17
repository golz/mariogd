#include "cEnemy.h"



cEnemy::cEnemy()
{
}


cEnemy::~cEnemy()
{
}



void cEnemy::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, enemySheet->at(animControl->Index())->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(enemySheet->at(animControl->Index())->X0(), enemySheet->at(animControl->Index())->Y1());	glVertex3i(x, y, 49);
	glTexCoord2f(enemySheet->at(animControl->Index())->X1(), enemySheet->at(animControl->Index())->Y1());	glVertex3i(x + Width(), y, 49);
	glTexCoord2f(enemySheet->at(animControl->Index())->X1(), enemySheet->at(animControl->Index())->Y0());	glVertex3i(x + Width(), y + Height(), 49);
	glTexCoord2f(enemySheet->at(animControl->Index())->X0(), enemySheet->at(animControl->Index())->Y0());	glVertex3i(x, y + Height(), 49);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void cEnemy::Init()
{
	velocityx = rand()%100<50?-100:100;
	animControl = new cAnimControl();
	animControl->AddAnim("StraightLoop", "walking", 0, 1, 0.2f);
}
void cEnemy::Update(float tpf)
{
	animControl->UpdateAnim(tpf);
	/* Movement */
	if (X() < 20 || X() > 1580)
	{
		velocityx *= -1;
	}
	x += velocityx* tpf;
}

void cEnemy::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
}

void cEnemy::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
}

void cEnemy::ReadMouse(int button, int state, int x, int y)
{
}

bool cEnemy::Intersect(float x0, float y0, float x1, float y1)
{
	return x < x1 && x + width > x0 &&
		y < y1 && y + height > y0;
}