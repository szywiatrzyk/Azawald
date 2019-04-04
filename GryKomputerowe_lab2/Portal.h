#pragma once
#include "SceneObject.h"
class Portal: public SceneObject
{
public:
	Portal(int x,int y,int z,float rotate);
	~Portal();

	void Render();
	void Update();
	float rotate;
	bool load(std::string filepath);
	std::string textureName;
	std::string textureNameclose;
	std::vector<vec3> normals;
	std::vector<vec3> vertices;
	std::vector<vec3> uvs;
	int spin;
	bool portalclose;
	int portalopentime;
	int chosetex;
};

