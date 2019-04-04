#include "stdafx.h"
#include "Skybox.h"

Skybox1::Skybox1(float rozmiar)
{
	this->rozm = rozmiar;
	this->textureName = textureName;
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
}


Skybox1::~Skybox1(void)
{
}

void Skybox1::Update(void)
{
	
}

void Skybox1::Render(void)
{
	glDisable(GL_LIGHTING);
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
//		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	
	glBegin(GL_QUADS);
	
	//Normal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0, 1);
		glVertex3f(-rozm ,-rozm ,rozm );
	glTexCoord2f(0, 0);
		glVertex3f(-rozm , -rozm, -rozm);
	glTexCoord2f(1, 0);
		glVertex3f(rozm, -rozm, -rozm);
	glTexCoord2f(1, 1);
		glVertex3f(rozm, -rozm, rozm);


		// Lewa œciana
		//glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(-rozm, rozm, rozm);
		glTexCoord2f(1, 1);
		glVertex3f(-rozm, rozm, -rozm);
		glTexCoord2f(0, 1);
		glVertex3f(-rozm, -rozm, -rozm);
		glTexCoord2f(0, 0);
		glVertex3f(-rozm, -rozm, rozm);
		//przednia
		//glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1, 0);
		glVertex3f(-rozm, rozm, -rozm);
		glTexCoord2f(1, 1);
		glVertex3f(rozm, rozm, -rozm);
		glTexCoord2f(0, 1);
		glVertex3f(rozm, -rozm, -rozm);
		glTexCoord2f(0, 0);
		glVertex3f(-rozm, -rozm, -rozm);
		//rpawa
		//glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(rozm, rozm, -rozm);
		glTexCoord2f(1, 1);
		glVertex3f(rozm, rozm, rozm);
		glTexCoord2f(0, 1);
		glVertex3f(rozm, -rozm, rozm);
		glTexCoord2f(0, 0);
		glVertex3f(rozm, -rozm, -rozm);
		glEnd();

		
		

	glPopMatrix();
	
    glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);


	



}

