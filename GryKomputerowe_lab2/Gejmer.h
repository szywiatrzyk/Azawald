#pragma once
#include "SceneObject.h"

class Gejmer : public SceneObject
{
public:
	Gejmer(void);
	~Gejmer(void);

	void Render();
	void Update();
	bool load(std::string filepath);
	bool load1(std::string filepath);
	bool load2(std::string filepath);
	bool load3(std::string filepath);
	bool load4(std::string filepath);
	bool load5(std::string filepath);
	int iter;
	//int lifeisbrutal;

	vec3 modelScale;
	vec3 color;
	int facing_shot;
	int facing_move;
	std::vector<vec3> normals;
	std::vector<vec3> vertices;
	std::vector<vec3> normals1; //test animacji
	std::vector<vec3> vertices1;
	std::vector<vec3> normals2; //test animacji
	std::vector<vec3> vertices2;
	std::vector<vec3> normals3; //test animacji
	std::vector<vec3> vertices3;
	std::vector<vec3> normals4; //test animacji
	std::vector<vec3> vertices4;
	std::vector<vec3> normals5; //test animacji
	std::vector<vec3> vertices5;

	std::vector<vec3> uvs;
	std::vector<vec3> uvs1;
	std::vector<vec3> uvs2;
	std::vector<vec3> uvs3;
	std::vector<vec3> uvs4;
	std::vector<vec3> uvs5;

	vec3 modelTranslation;
	int nomove;
	int stillmoving;

	std::string textureName;
	std::string textureName1;
	std::string textureName2;
	std::string textureName3;
	std::string textureName4;
	std::string textureName5;
	std::string textureimune;
	bool upadek;
	//do portalo:
	bool p1,p2,p3,p4;
	int plicz;
	int plicz1;
	int plicz2;
	int plicz3;
	


};

