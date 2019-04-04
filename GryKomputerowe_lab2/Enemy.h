#pragma once
#include "SceneObject.h"

class Enemy : public SceneObject
{
public:
	Enemy(int enemytype);
	Enemy(Enemy &ene);
	~Enemy(void);

	void Render();
	void Update();
	int enemytype;
	vec3 color;
	float speed;
	bool load(std::string filepath);
	std::string textureName;
	std::string textureName2;
	std::string textureName3;
	std::vector<vec3> normals;
	std::vector<vec3> vertices;
	std::vector<vec3> uvs;
	int spin;
	int rozm;
	int spinspeed;




};