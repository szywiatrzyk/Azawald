#pragma once
#include "SceneObject.h"



class bullet:public SceneObject
{
public:
	bullet();
	
	~bullet();


	void Render();
	void Update();


	bool load(std::string filepath);
	vec3 color;
	float radius;
	int direct;
	int time;
	float speed;
	std::string textureName;
	std::vector<vec3> normals;
	std::vector<vec3> vertices;
	std::vector<vec3> uvs;
};

