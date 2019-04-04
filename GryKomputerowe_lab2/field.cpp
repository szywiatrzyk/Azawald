#include "stdafx.h"
#include "field.h"


field::field(float rozmiar)
{
this->rozm = rozmiar;
this->textureName = textureName;
pos.x = 0;
pos.y = 0;
pos.z = 0;
}


field::~field()
{
}

void field::Update(void)
{
}

void field::Render(void)
{

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = { 1, 1, 1 };
	float mat_specular[] = { 0, 0, 0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glColor3f(1, 1, 1);

	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
		//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-rozm, 0, rozm);
	glTexCoord2f(0, 0);
	glVertex3f(-rozm, 0, -rozm);
	glTexCoord2f(1, 0);
	glVertex3f(rozm, 0, -rozm);
	glTexCoord2f(1, 1);
	glVertex3f(rozm, 0, rozm);
	glEnd();



	if (!textureName1.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName1);
		//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(-rozm, 0, rozm);
	glTexCoord2f(1, 1);
	glVertex3f(-rozm, 0, -rozm);
	glTexCoord2f(0, 1);
	glVertex3f(-rozm, -2 * rozm, -rozm);
	glTexCoord2f(0, 0);
	glVertex3f(-rozm, -2 * rozm, rozm);
	glEnd();
	//przednia
//glNormal3f(0.0f, 0.0f, -1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(-rozm, 0, rozm);
	glTexCoord2f(1, 1);
	glVertex3f(rozm, 0, rozm);
	glTexCoord2f(0, 1);
	glVertex3f(rozm, -2 * rozm, rozm);
	glTexCoord2f(0, 0);
	glVertex3f(-rozm, -2 * rozm, rozm);
	glEnd();
			//rpawa
	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(rozm, 0, -rozm);
	glTexCoord2f(1, 1);
	glVertex3f(rozm, 0, rozm);
	glTexCoord2f(0, 1);
	glVertex3f(rozm, -2*rozm, rozm);
	glTexCoord2f(0, 0);
	glVertex3f(rozm, -2 * rozm, -rozm);
	glEnd();

	
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}
