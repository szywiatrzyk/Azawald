#pragma once
class pickup : public SceneObject
{
public:
	pickup(int x, int y, int z, int mode,float scale);
	pickup(pickup &pik);
	~pickup();

	void Render();
	void Update();
	int spin;
	bool load(std::string filepath);
	std::string textureName;
	std::vector<vec3> normals;
	std::vector<vec3> vertices;
	std::vector<vec3> uvs;
	bool load1(std::string filepath);
	std::string textureName1;
	std::vector<vec3> normals1;
	std::vector<vec3> vertices1;
	std::vector<vec3> uvs1;
	bool load2(std::string filepath);
	std::string textureName2;
	std::vector<vec3> normals2;
	std::vector<vec3> vertices2;
	std::vector<vec3> uvs2;
	float scale;

	

};
