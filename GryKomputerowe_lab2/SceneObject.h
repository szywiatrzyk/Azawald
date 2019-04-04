#pragma once

// Klasa abstrakcyjna opisuj�ca obiekt sceny. Wszystkie klasy obiekt�w sceny (np. sfery, �ciany, gracz itd.) powinny po tej klasie dziedziczy�.

class SceneObject
{
public:
	SceneObject(void);
	~SceneObject(void);
	int lifeisbrutal;
	vec3 pos;
	bool isalive;
	int id;
	vec3 Antiplayerposition;
	virtual void Render() = 0;
	virtual void Update() = 0;
	float radius;
	float radius1;
	bool kolizjon;
	int kolizjondirekszyn;
	bool activate;
	int whoactive;
	int enemylife;
	vec3 force;
	float radius2;
	bool imunemod;
};

// ID : 1: ENEMY 2: BULLET 3: GR�ACZ 4:PICKUP