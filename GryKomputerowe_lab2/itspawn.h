#pragma once
#include "SceneObject.h"
class itspawn : public SceneObject
{
public:
	itspawn(int x, int y, int z);
	~itspawn();

	void Render();
	void Update();

	bool load(std::string filepath);
	std::string textureName;
	std::vector<vec3> normals;
	std::vector<vec3> vertices;
	std::vector<vec3> uvs;
	
};

