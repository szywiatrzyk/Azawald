#pragma once
#include "SceneObject.h"
class field : public SceneObject
{
public:
	field(float rozm);
	~field();

	void Render();
	void Update();
	float rozm;

	std::string textureName;
	std::string textureName1;
};

