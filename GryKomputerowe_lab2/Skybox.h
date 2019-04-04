#pragma once
#include "SceneObject.h"
class Skybox1 : public SceneObject
{
public:
	Skybox1(float rozm);
	~Skybox1();

	void Render();
	void Update();
	float rozm;
	
	std::string textureName;

};
