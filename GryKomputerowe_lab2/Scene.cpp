#include "stdafx.h"
#include "Scene.h"



Scene::Scene(void)
{
	EnemyCount = 0;
	pickup_machinegun = false;
	pickup_heal = false;
	pickup_speedboost = false;
	startgame = true;
	gameover = false;
	gameovertimer = 0;
	howtoplay = true;
	
}


Scene::~Scene(void)
{
	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		delete sceneObjects[i];

	sceneObjects.clear();

	for (unsigned int i = 0; i < enemys.size(); i++)
		delete enemys[i];

	enemys.clear();
}

// Dodawanie obiektu do sceny
void Scene::AddObject(SceneObject* object)
{
	sceneObjects.push_back(object);
	if (object->id == 1) {
		enemys.push_back(object);
		EnemyCount++;
		
	}
}


void renderBitmapString(float x, float y, char* text) {

	char *c;
	glRasterPos3f(x, y, 0);
	for (c = text; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void Scene::HeadUpDisplay()
{
	if (startgame == true) {
		if (howtoplay == true) {
			if (!textureNames.empty())
			{
				glEnable(GL_TEXTURE_2D);
				TextureManager::getInstance()->BindTexture(textureNames);
				//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			}
			float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
			float mat_diffuse[] = { 1, 1, 1 };
			float mat_specular[] = { 0.1f, 0.1f, 0.1f };

			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glDisable(GL_LIGHTING);

			glBegin(GL_QUADS);

			//

			glTexCoord2f(0, 1);
			glVertex2f(0, 100);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(1, 0);
			glVertex2f(100, 0);
			glTexCoord2f(1, 1);
			glVertex2f(100, 100);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_LIGHTING);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
		if (howtoplay == false) {

			if (!textureNamesh.empty())
			{
				glEnable(GL_TEXTURE_2D);
				TextureManager::getInstance()->BindTexture(textureNamesh);
				//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			}
			float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
			float mat_diffuse[] = { 1, 1, 1 };
			float mat_specular[] = { 0.1f, 0.1f, 0.1f };

			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glDisable(GL_LIGHTING);

			glBegin(GL_QUADS);

			//

			glTexCoord2f(0, 1);
			glVertex2f(0, 100);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(1, 0);
			glVertex2f(100, 0);
			glTexCoord2f(1, 1);
			glVertex2f(100, 100);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_LIGHTING);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);


		}
	}
	else {
		if (gameover == true) {
			if (!textureNameendb.empty())
			{
				glEnable(GL_TEXTURE_2D);
				TextureManager::getInstance()->BindTexture(textureNameendb);
				//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			}
			
			gameovertimer++;
			
			float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
			float mat_diffuse[] = { 1, 1, 1 };
			float mat_specular[] = { 0.1f, 0.1f, 0.1f };

			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glDisable(GL_LIGHTING);

			if (gameovertimer > 100) {
				if (!textureNameend.empty())
				{
					glEnable(GL_TEXTURE_2D);
					TextureManager::getInstance()->BindTexture(textureNameend);
					//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				}
			}
			
			glBegin(GL_QUADS);

			//glColor3f(0, 1, 0);
			glTexCoord2f(0, 1);
			glVertex2f(0, 100);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(1, 0);
			glVertex2f(100, 0);
			glTexCoord2f(1, 1);
			glVertex2f(100, 100);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			//glEnable(GL_LIGHTING);
			glPopMatrix();
		//	glMatrixMode(GL_MODELVIEW);
		
		
		
		
		}
		else {
			float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
			float mat_diffuse[] = { 1, 1, 1 };
			float mat_specular[] = { 0.1f, 0.1f, 0.1f };

			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);


			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glDisable(GL_LIGHTING);
			//glDisable(GL_CULL_FACE);
			if (!textureName.empty())
			{
				glEnable(GL_TEXTURE_2D);
				TextureManager::getInstance()->BindTexture(textureName);
				//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			}
			//glBegin(GL_QUADS);
			if (hud.life > 0 && hud.life <= 6) {
				for (int i = 0; i < hud.life; i++) {



					glEnd();
					glBegin(GL_QUADS);
					glTexCoord2f(0, 1);
					glVertex2f(2 + i * 5, 98);
					glTexCoord2f(0, 0);
					glVertex2f(2 + i * 5, 92);
					glTexCoord2f(1, 0);
					glVertex2f(6 + i * 5, 92);
					glTexCoord2f(1, 1);
					glVertex2f(6 + i * 5, 98);
					glEnd();
				}

			}
			glDisable(GL_TEXTURE_2D);


			glBegin(GL_QUADS);
			glColor3f(1, 1, 0);
			glVertex2f(2.5, 89);
			glVertex2f(2.5, 87);
			if ((hud.minEnergy / hud.maxEnegry) < 0.00001) {
				glVertex2f(2.5, 87);

				glVertex2f(2.5, 89);
			}
			else {
				glVertex2f(31 - 28.5*(hud.minEnergy / hud.maxEnegry), 87);

				glVertex2f(31 - 28.5*(hud.minEnergy / hud.maxEnegry), 89);
			}
			glEnd();

			glBegin(GL_QUADS);
			glColor3f(0, 0, 0);
			glVertex2f(2, 90);
			glVertex2f(2, 86);
			glVertex2f(32, 86);
			glVertex2f(32, 90);
			glEnd();

			
			char text1[50];
			sprintf(text1, "LEVEL: %d ", (int)hud.level);

			glColor3f(1, 1, 0);
			renderBitmapString(80, 3, text1);


			char text[50];
			sprintf(text, "SCORE: %d ", (int)hud.score);

			glColor3f(1, 1, 0);
			renderBitmapString(80, 90, text);

			glEnable(GL_LIGHTING);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
	}
}




// Renderowanie wszystkich obiektów na scenie
void Scene::Render()
{
	for(unsigned int i = 0 ; i < sceneObjects.size() ; i++)
		sceneObjects[i]->Render();
}

// Aktualizowanie wszystkich obiektów na scenie
void Scene::Update()
{
	if (imunemode == true) {
		if (imunecount == 100) {
			imunemode = false;
			imunecount = 0;

		}
		else {
			imunecount++;
		}
	}

	for (unsigned int i = 0; i < sceneObjects.size(); i) {
		
		sceneObjects[i]->Update();

		if (sceneObjects[i]->id == 4 && sceneObjects[i]->activate == true) {
			hud.score += 50;
			if (sceneObjects[i]->whoactive == 1) {
				pickup_heal = true;
				delete sceneObjects[i];
				sceneObjects.erase(sceneObjects.begin() + i);
				continue;
			}
			if (sceneObjects[i]->whoactive == 2) {
				pickup_machinegun = true;
				delete sceneObjects[i];
				sceneObjects.erase(sceneObjects.begin() + i);
				continue;
			}
			if (sceneObjects[i]->whoactive == 3) {
				pickup_speedboost =  true;
				delete sceneObjects[i];
				sceneObjects.erase(sceneObjects.begin() + i);
				continue;
			}
		}



		if (sceneObjects[i]->id == 1) {

			for (unsigned int j = 0; j < enemys.size(); j++) {


					SceneObject* obj1 = sceneObjects[i];
					SceneObject* obj2 = enemys[j];

					float r = vec3::distance(obj1->pos, obj2->pos);
					
					if (obj1->pos.x == obj2->pos.x && obj1->pos.z == obj2->pos.z) continue;
					float d = (obj1->radius2 + obj2->radius2) - r;
					
					if (d > 0)
					{
						vec3 v1 = obj1->pos - obj2->pos;
						vec3 v2 = obj2->pos - obj1->pos;

						v1 = v1.normalized();
						v2 = v2.normalized();

						obj1->pos = obj1->pos + v1 * (d / 2) * 1.2f;
						obj2->pos = obj2->pos + v2 * (d / 2) * 1.2f;

						float total_force = obj1->force.length() + obj2->force.length();

						obj1->force = v1 * total_force * 0.5f;
						obj2->force = v2 * total_force * 0.5;

						if (obj1->pos.y>0.6) obj1->pos.y = 0.6f;
						if (obj2->pos.y>0.6) obj2->pos.y = 0.6f;
				}
			}

		}
		if (sceneObjects[i]->id == 2)
		{
			for (unsigned int j = 0; j < enemys.size(); j++) {


				if (sqrt((sceneObjects[i]->pos.x - enemys[j]->pos.x)*(sceneObjects[i]->pos.x - enemys[j]->pos.x) + (sceneObjects[i]->pos.z - enemys[j]->pos.z)*(sceneObjects[i]->pos.z - enemys[j]->pos.z)) < 0.3f)
				{
					sceneObjects[i]->isalive = false;
					if (enemys[j]->enemylife == 0) {


						enemys[j]->isalive = false;
						hud.score += 100;
						enemys.erase(enemys.begin() + j);
						EnemyCount--;
						
					}
					else enemys[j]->enemylife -= 1;

					
				}


			}

		}
		if (sceneObjects[i]->id == 3)
		{	
			if (imunemode == true) { sceneObjects[i]->imunemod = true; }
			else { sceneObjects[i]->imunemod = false; }

			if (sceneObjects[i]->pos.y < -5 && sceneObjects[i]->isalive != false) {
				gameover = true;
			

			}
				for (unsigned int j = 0; j < enemys.size(); j++) {

					if (sqrt((sceneObjects[i]->pos.x - enemys[j]->pos.x)*(sceneObjects[i]->pos.x - enemys[j]->pos.x) + (sceneObjects[i]->pos.z - enemys[j]->pos.z)*(sceneObjects[i]->pos.z - enemys[j]->pos.z)) < 0.5f && enemys[j]->activate == true &&imunemode==false)
					{
						
						if (sceneObjects[i]->lifeisbrutal <= 1) {
							gameover = true;
						
						}
						else {

							sceneObjects[i]->lifeisbrutal = sceneObjects[i]->lifeisbrutal - 1;
							imunemode = true;
							
							
							sceneObjects[i]->kolizjon = true;
							if (sceneObjects[i]->pos.x < enemys[j]->pos.x) {
								sceneObjects[i]->kolizjondirekszyn = 1;
								sceneObjects[i]->pos.x = sceneObjects[i]->pos.x - 0.5f;
							}
							if (sceneObjects[i]->pos.x > enemys[j]->pos.x) {
								sceneObjects[i]->kolizjondirekszyn = 2;
								sceneObjects[i]->pos.x = sceneObjects[i]->pos.x + 0.5f;
							}
							if (sceneObjects[i]->pos.z < enemys[j]->pos.z) {
								sceneObjects[i]->kolizjondirekszyn = 3;
								sceneObjects[i]->pos.z = sceneObjects[i]->pos.z - 0.5f;
							}
							if (sceneObjects[i]->pos.z > enemys[j]->pos.z) {
								sceneObjects[i]->kolizjondirekszyn = 4;
								sceneObjects[i]->pos.z = sceneObjects[i]->pos.z + 0.5f;
							}
						}

					}
				}

			
		}
		
		if (sceneObjects[i]->isalive == true) {
			sceneObjects[i]->Antiplayerposition.x = wspGracza.x;
			sceneObjects[i]->Antiplayerposition.y = wspGracza.y;
			sceneObjects[i]->Antiplayerposition.z = wspGracza.z;
			i++;
		}
		else {
			delete sceneObjects[i];
			sceneObjects.erase(sceneObjects.begin() + i);
			
		}

	}
		
		
}