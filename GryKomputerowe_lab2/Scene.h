#pragma once

// Klasa odpowiedzialna za obs³ugê sceny i nale¿¹cych do niej elementów (kamera, obiekty)

class Scene
{
public:
	Scene(void);
	~Scene(void);

	void Render();
	void Update();

	void AddObject(SceneObject* object);
	vec3 wspGracza;
	int EnemyCount;

	//HUD!!1
	struct HUD
	{
		int life;
		float maxEnegry;
		float minEnergy;
		int score;
		int level;
	}hud;


	//pickupy
	bool pickup_machinegun;
	bool pickup_heal;
	bool pickup_speedboost;
	void HeadUpDisplay();
public:
	std::string textureName;
	std::string textureNameend;
	std::string textureNames;
	std::string textureNamesh;
	std::string textureNameendb;
	std::vector<SceneObject*> sceneObjects;
	std::vector<SceneObject*> enemys;
	int gameovertimer;
	bool startgame;
	bool howtoplay;
	bool gameover;
	bool imunemode;
	int imunecount;
};

