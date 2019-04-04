#include "stdafx.h"
#include "time.h"


// Deklaracje funkcji u¿ywanych jako obs³uga zdarzeñ GLUT-a.
void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnTimer(int);
void bullettime(int);

// Struktura pozwalaj¹ca na przechowanie aktualnego stanu kamery.
// Struktura powinna dziedziczyæ po klasie SceneObject, ale dla u³atwienia w ramach dzisiejszych zajêæ zostanie zaimplementowana osobno.
struct SCameraState {
	vec3 pos; // pozycja kamery
	vec3 tmp;
	float speed; // mno¿nik zmian pozycji - "szybkoœæ" ruchów kamery
};
int worldstep = 10;
// Zmienna przsechowuj¹ca aktualny stan kamery. Powinno siê "w³o¿yæ ten obiekt do sceny za pomoc¹ metody AddObject().
SCameraState player;
Gejmer* obiekt = new Gejmer();

pickup *item1,*item2,*item3,*item4,*item15, *item25 ,*item35, *item45,*item16, *item26, *item36, *item46;
Enemy *preenemy,*preenemy2;
Portal *por1, *por2, *por3, *por4;

int level=0; //poziom gry ->utrudnienia rozgrywki
int leveltimer= 150; //czas pomiedzy levelami;

// Deklaracja sceny
Scene scene;
float a;
int machinegun = 15; //pickup mashinegun
int timetoend = 0; // licznik czasu do: czas na zakonczenie pickupa
int timetoendset = 200;//czas na zakonczenie pickupa
int shotspeedy = 0; //szybkosc strzelania + przeladowanie
int opoznienie=0;
int actionflag = 1; //przeladowanie naboju
int timewithoutpickup; //czas w ktorym spawni sie pickup
int timepickupset = 200; //ustawianie czasu po ktorym sie spawni
bool nopickup = true; //true winc nie ma pickupa
bool specialstate[256];
bool machinecolour = false;

void specialKeyUp(int key, int x, int y) {
		specialstate[key] = false;
}

void specialKeyDown(int key, int x, int y) {
//nothing ahppens
}

void specialKeyPress(int key, int x, int y) {
	if (!specialstate[key]) {
		specialKeyDown(key, x, y); // 
	}
	specialstate[key] = true;
}

void buildNewBullet(int key) {
	bullet*	tes = new bullet;
	
	
	tes->pos.x = obiekt->pos.x;
	tes->pos.y = obiekt->pos.y;
	tes->pos.z = obiekt->pos.z;
	tes->direct = key;
	if (machinecolour == true) {


		tes->color.x = 1.0f;
		tes->color.y = 0.0f;
		tes->color.z = 0.0f;
	}
	else {
		tes->color.x = 1.0f;
		tes->color.y = 1.0f;
		tes->color.z = 0.0f;


	}
	tes->radius = 0.1f;

	scene.AddObject(tes);
	actionflag = 0;
}
void createNewEnemy(float x, float z,int type) {
	Enemy* enem;
	if (type == 1) {
		 enem = new Enemy(*preenemy);
	}
	else  enem = new Enemy(*preenemy2);
	enem->pos.x = x;
	enem->pos.y = -1.2f;
	enem->pos.z = z;
	scene.AddObject(enem);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitWindowPosition(1, 1);
	glutInitWindowSize(1280, 720);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("AZAWALD");

	//float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(specialKeyPress);
	glutSpecialUpFunc(specialKeyUp);
	glutTimerFunc(17, OnTimer, 0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	srand(time(NULL));
	scene.startgame == true;

	// Inicjalizacja parametrów kamery:
	player.pos.x = 0.0f;
	player.pos.y = 5.0f;
	player.pos.z = 3.0f;

	player.tmp.x = 0.0f;
	player.tmp.y = -1.2f;
	player.tmp.z = -1.0f;

	player.speed = .2f;
	
	obiekt->color.x = 1.0f;
	obiekt->color.y = 1.0f;
	obiekt->color.z = 1.0f;
	obiekt->pos.x = 0.0f;
	obiekt->pos.y = 0.4f;
	obiekt->pos.z = 0.0f;
	
	
	

	obiekt->load("../Resources/Model/wat11.obj");
	obiekt->load1("../Resources/Model/wat2.obj");
	obiekt->load2("../Resources/Model/wat3.obj");
	obiekt->load3("../Resources/Model/wats.obj");
	obiekt->load4("../Resources/Model/wats2.obj");
	obiekt->load5("../Resources/Model/wats33.obj");
	obiekt->textureName = "wat";
	obiekt->textureName1 = "wat1";
	obiekt->textureName2 = "wat2";
	obiekt->textureName3 = "wats";
	obiekt->textureName4 = "wats1";
	obiekt->textureName5 = "wats2";
	obiekt->textureimune = "imun";

	obiekt->modelTranslation = vec3(0, -1.2, 0);
	scene.AddObject(obiekt);





//pickupy
	//heal
	item15 = new pickup(worldstep / 2, -4, worldstep / 2, 1,0.05);
	item15->load("../Resources/Model/Heart.obj");
	item15->textureName = "item1";

	item25 = new pickup(worldstep / 2, -4, -worldstep / 2, 1,0.05);
	item25->load("../Resources/Model/Heart.obj");
	item25->textureName = "item1";

	item35 = new pickup(-worldstep / 2, -4, worldstep / 2, 1,0.05);
	item35->load("../Resources/Model/Heart.obj");
	item35->textureName = "item1";

	item45 = new pickup(-worldstep / 2, -4, -worldstep / 2, 1,0.05);
	item45->load("../Resources/Model/Heart.obj");
	item45->textureName = "item1";
	//machinegun
	item1 = new pickup(worldstep / 2, -4, worldstep / 2,2,0.3);
	item1->load("../Resources/Model/machinegun.obj");
	item1->textureName = "item2";

	item2 = new pickup(worldstep / 2, -4, -worldstep / 2,2, 0.3);
	item2->load("../Resources/Model/machinegun.obj");
	item2->textureName = "item2";

	item3 = new pickup(-worldstep / 2, -4, worldstep / 2,2, 0.3);
	item3->load("../Resources/Model/machinegun.obj");
	item3->textureName = "item2";

	item4 = new pickup(-worldstep / 2, -4, -worldstep / 2,2, 0.3);
	item4->load("../Resources/Model/machinegun.obj");
	item4->textureName = "item2";
	//speedboost
	item16 = new pickup(worldstep / 2, -4, worldstep / 2, 3,0.3);
	item16->load("../Resources/Model/speedboost.obj");
	item16->textureName = "item3";

	item26 = new pickup(worldstep / 2, -4, -worldstep / 2, 3,0.3);
	item26->load("../Resources/Model/speedboost.obj");
	item26->textureName = "item3";

	item36 = new pickup(-worldstep / 2, -4, worldstep / 2,3,0.3);
	item36->load("../Resources/Model/speedboost.obj");
	item36->textureName = "item3";

	item46 = new pickup(-worldstep / 2, -4, -worldstep / 2, 3,0.3);
	item46->load("../Resources/Model/speedboost.obj");
	item46->textureName = "item3";


	preenemy = new Enemy(1);
	preenemy->textureName = "enemy";
	preenemy->textureName2 = "enemy11";
	preenemy->textureName3 = "enemy22";
	preenemy->load("../Resources/Model/enemy.obj");

	preenemy2 = new Enemy(2);
	preenemy2->textureName = "enemy2";
	preenemy2->load("../Resources/Model/enemy2.obj");

	

	//portale
	por1 = new Portal(0,0,-worldstep,90);
	por1->load("../Resources/Model/portal.obj");
	por1->textureName ="por1";
	por1->textureNameclose = "porclose";
	scene.AddObject(por1);

	por2 = new Portal(worldstep, 0, 0 , 0);
	por2->load("../Resources/Model/portal.obj");
	por2->textureName = "por1";
	por2->textureNameclose = "porclose";
	scene.AddObject(por2);

	por3 = new Portal(-worldstep, 0, 0, 180);
	por3->load("../Resources/Model/portal.obj");
	por3->textureName = "por1";
	por3->textureNameclose = "porclose";
	scene.AddObject(por3);

	por4 = new Portal(0, 0, worldstep, 90);
	por4->load("../Resources/Model/portal.obj");
	por4->textureName = "por1";
	por4->textureNameclose = "porclose";
	scene.AddObject(por4);
	//spawnery itemow:

	itspawn *num1 = new itspawn(worldstep/2, 0, worldstep/2);
	num1->textureName = "itpsawn";
	num1->load("../Resources/Model/itspawn.obj");
	scene.AddObject(num1);

	itspawn *num2 = new itspawn(worldstep / 2, 0, -worldstep / 2);
	num2->textureName = "itpsawn";
	num2->load("../Resources/Model/itspawn.obj");
	scene.AddObject(num2);

	itspawn *num3 = new itspawn(-worldstep / 2, 0, worldstep / 2);
	num3->textureName = "itpsawn";
	num3->load("../Resources/Model/itspawn.obj");
	scene.AddObject(num3);

	itspawn *num4 = new itspawn(-worldstep / 2, 0, -worldstep / 2);
	num4->textureName = "itpsawn";
	num4->load("../Resources/Model/itspawn.obj");
	scene.AddObject(num4);
	
	


	//niebo
	Skybox1 *niebo = new Skybox1(30);
	niebo->textureName = "niebo";
	
	scene.AddObject(niebo);
	
	field *podl = new field(worldstep);
	podl->textureName = "podl";
	podl->textureName1 = "podl1";
	podl->id = 1298;
	scene.AddObject(podl);

	scene.textureName = "hearthud";
	scene.textureNames = "startgame";
	scene.textureNamesh = "htp";
	scene.textureNameend = "gameover";
	scene.textureNameendb = "gameoverb";
	
	TextureManager::getInstance()->LoadTexture("por1", "../Resources/textures/portal.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	//TextureManager::getInstance()->LoadTexture("bolt1", "../Resources/textures/bolt1.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("niebo", "../Resources/textures/skydome.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("wat", "../Resources/textures/wat1.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("wat1", "../Resources/textures/wat2.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("wat2", "../Resources/textures/wat3.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("wats", "../Resources/textures/wats.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("wats1", "../Resources/textures/wats2.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("wats2", "../Resources/textures/wats3.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("podl", "../Resources/textures/checkboard.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("podl1", "../Resources/textures/checkboard.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("itpsawn", "../Resources/textures/itpsawn.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("item1", "../Resources/textures/Heart.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("item2", "../Resources/textures/machinegun.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("item3", "../Resources/textures/speedboost.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("hearthud", "../Resources/textures/DINO.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("enemy2", "../Resources/textures/brick.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("enemy", "../Resources/textures/enemy.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("enemy11", "../Resources/textures/enemy1.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("enemy22", "../Resources/textures/enemy2.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("startgame", "../Resources/textures/startgame.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("gameover", "../Resources/textures/END.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("htp", "../Resources/textures/htp.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("gameoverb", "../Resources/textures/ENDb.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("porclose", "../Resources/textures/portalclose.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("imun", "../Resources/textures/imun.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	

	glutMainLoop();

	
	return 0;
}

// Tablica przechowuj¹ca stan klawiszy w formie flag, indeksowana wg kodów ASCII.
bool keystate[256];

// Obs³uga zdarzenia, gdy zostanie wciœniêty klawisz - zdarzenie nieoodporne na repetycjê klawiszy.
void OnKeyPress(unsigned char key, int x, int y) {
	
	if (!keystate[key]) {
		OnKeyDown(key, x, y); // Emulacja zdarzenia zwi¹zanego z pojedynczym wciœniêciem klawisza
	}
	keystate[key] = true;
}

// Obs³uga naszego w³asnego zdarzenia, gdy zostanie po raz pierwszy wciœniêty klawisz - zdarzenie odporne na repetycjê.
void OnKeyDown(unsigned char key, int x, int y) {
	
	if (key == 27) { // ESC - wyjœcie
		glutLeaveMainLoop();
	}
}

// Obs³uga zdarzenia puszczenia klawisza.
void OnKeyUp(unsigned char key, int x, int y) {
	
	
	keystate[key] = false;
}

// Aktualizacja stanu gry - wywo³ywana za poœrednictwem zdarzenia-timera.
void OnTimer(int id) {

	if (scene.startgame == true) {
		
		if ((keystate['w'] || keystate['s'] || keystate['a'] || keystate['d']) && scene.startgame == true && scene.howtoplay == false)
		{
			scene.startgame = false;
		}

		if (keystate['q'] && scene.startgame == true && scene.howtoplay == true)
		{
			scene.howtoplay = false;
		}
	}
	else {
		//kamera sledzi gracza:
		player.pos.x = obiekt->pos.x;
		player.pos.z = obiekt->pos.z + 4.0f;

		//LEVEL CONSTRUCTION:::

	if (scene.EnemyCount == 0) {
			if (leveltimer == 0) {
				level++;
				preenemy->speed += 0.01f;
				preenemy2->speed += 0.01f;
				preenemy->spinspeed += 1;
				preenemy2->spinspeed += 1;
			
				for (int i = 1; i <= level; i++) {
					int randx1 = (std::rand() % 18) - 9;
					int randy1 = (std::rand() % 18) - 9;
					int randx2 = (std::rand() % 18) - 9;
					int randy2 = (std::rand() % 18) - 9;
					int randx3 = (std::rand() % 18) - 9;
					int randy3 = (std::rand() % 18) - 9;
					createNewEnemy(randx1, randy1, 2);
					createNewEnemy(randx2, randy2, 1);
					createNewEnemy(randx3, randy3, 2);


				}
				leveltimer = 150;
			}
			else leveltimer--;
		}



		//END OF LEVEL CONTRUCTION:::



		if (obiekt->p1 == false) {
			por1->portalclose = true; por1->chosetex = 1;
		}
		else if (obiekt->p1 == true) {
			por1->portalclose = false; por1->chosetex = 2;
		}

		if (obiekt->p2 == false) { por4->portalclose = true; por4->chosetex = 1; }
		else if (obiekt->p2 == true) {
			por4->portalclose = false; por4->chosetex = 2;
		}
		if (obiekt->p3 == false) { por2->portalclose = true; por2->chosetex = 1; }
		else if (obiekt->p2 == true) {
			por2->portalclose = false; por2->chosetex = 2;
		}
	
	if (obiekt->p4 == false) { por3->portalclose = true; por3->chosetex = 1; }
	else if (obiekt->p4 == true){por3->portalclose = false; por3->chosetex = 2;
}

		

		//BLOK CZEKANIA NA AKCJE I TWORZENIA RZECZY:
		//szybkoœc strzelania zalezy od tego:
		opoznienie = opoznienie + 1;
		if (opoznienie > 5)
		{

			opoznienie = 0;
			//actionflag = 1;
			obiekt->facing_shot = 0;
			obiekt->stillmoving = obiekt->stillmoving * (-1);
			if (keystate['d'] == false && keystate['w'] == false && keystate['a'] == false && keystate['s'] == false) obiekt->nomove = 1;
		}
		//PICKUP SHOTSPEED
			//if pickup activate ->mashinegun

		if (nopickup == true) {
			if (timewithoutpickup < timepickupset) {
				timewithoutpickup++;
			}
			else {
				nopickup = false;
				timewithoutpickup = 0;
				//TWORZENIE NOWYCH PICKUPÓW
				int random = (std::rand() % 4) + 1;
				int pictype = (std::rand() % 3) + 1;
				

				if (random == 1) {
					if (pictype == 2) { pickup *item11 = new pickup(*item1);  scene.AddObject(item11); }
					if (pictype == 1) { pickup *item11 = new pickup(*item15);  scene.AddObject(item11); }
					if (pictype == 3) { pickup *item11 = new pickup(*item16);  scene.AddObject(item11); }
				}
				if (random == 2) {
					if (pictype == 2) { pickup *item22 = new pickup(*item2);  scene.AddObject(item22); }
					if (pictype == 1) { pickup *item22 = new pickup(*item25);  scene.AddObject(item22); }
					if (pictype == 3) { pickup *item22 = new pickup(*item26);  scene.AddObject(item22); }
				}
				if (random == 3) {
					if (pictype == 2) { pickup *item33 = new pickup(*item3);  scene.AddObject(item33); }
					if (pictype == 1) { pickup *item33 = new pickup(*item35);  scene.AddObject(item33); }
					if (pictype == 3) { pickup *item33 = new pickup(*item36);  scene.AddObject(item33); }
				}
				if (random == 4) {
					if (pictype == 2) { pickup *item44 = new pickup(*item4);  scene.AddObject(item44); }
					if (pictype == 1) { pickup *item44 = new pickup(*item45);  scene.AddObject(item44); }
					if (pictype == 3) { pickup *item44 = new pickup(*item46);  scene.AddObject(item44); }
				}



			}
		}
		if (scene.pickup_heal == true) {

			scene.pickup_heal = false;
			nopickup = true;
			if (obiekt->lifeisbrutal <= 10) obiekt->lifeisbrutal += 1;
			
		}

		if (scene.pickup_machinegun == true) {

			machinegun = 3;
			machinecolour = true;
			if (timetoend < 200) {
				timetoend++;
			}
			else {
				machinecolour = false;
				scene.pickup_machinegun = false;
				nopickup = true;
				machinegun = 30;
				timetoend = 0;
			}

		}
		if (scene.pickup_speedboost == true) {

			player.speed = 0.3f;
			if (timetoend < 200) {
				timetoend++;
			}
			else {

				scene.pickup_speedboost = false;
				nopickup = true;
				player.speed = 0.2f;
				timetoend = 0;
			}

		}
		shotspeedy += 1;
		if (shotspeedy > machinegun) {
			actionflag = 1;
			shotspeedy = 0;

		}

		scene.hud.maxEnegry = timetoendset;
		scene.hud.minEnergy = timetoend;
		scene.hud.level = level;

		//przekazywanie wspolzednych wrogom (do sceny)



		scene.wspGracza.x = obiekt->pos.x;
		scene.wspGracza.y = obiekt->pos.y;
		scene.wspGracza.z = obiekt->pos.z;

		
	\
		//BLOK KIEROWANIA LUDZIKIEM	
			//kierowanie strzalu strzalkami:
		if (specialstate[100]) { bullettime(3); } //lewo
		if (specialstate[102]) { bullettime(4); } //prawo
		if (specialstate[101]) { bullettime(1); } //gora
		if (specialstate[103]) { bullettime(2); } //dol



		if (keystate['w'])
		{
			player.pos.x += player.tmp.x * player.speed;
			player.pos.z += player.tmp.z * player.speed;
			obiekt->facing_move = 1;
			obiekt->pos.x += player.tmp.x * player.speed;
			obiekt->pos.z += player.tmp.z * player.speed;

			obiekt->nomove = 0;

		}
		if (keystate['s'])
		{
			obiekt->facing_move = 2;
			player.pos.x -= player.tmp.x * player.speed;
			player.pos.z -= player.tmp.z * player.speed;


			obiekt->pos.x -= player.tmp.x * player.speed;
			obiekt->pos.z -= player.tmp.z * player.speed;
			obiekt->nomove = 0;


		}

		if (keystate['a'])
		{
			obiekt->facing_move = 3;
			player.pos.z -= player.tmp.x * player.speed;
			player.pos.x += player.tmp.z * player.speed;

			obiekt->pos.z -= player.tmp.x * player.speed;
			obiekt->pos.x += player.tmp.z * player.speed;
			obiekt->nomove = 0;

		}
		if (keystate['d'])
		{
			obiekt->facing_move = 4;
			player.pos.z += player.tmp.x * player.speed;
			player.pos.x -= player.tmp.z * player.speed;

			obiekt->pos.z += player.tmp.x * player.speed;
			obiekt->pos.x -= player.tmp.z * player.speed;
			obiekt->nomove = 0;
		}



	}
		// Aktualizacja ca³ej sceny
		scene.Update();

		// Chcemy, by ta funkcja wywolala sie ponownie za 17ms.
		glutTimerFunc(17, OnTimer, 0);
	
}
void bullettime(int key) {
	obiekt->facing_shot = key;
	if (actionflag == 1) {
	
		if (key == 1) {
			buildNewBullet(key);
		}
		if (key == 2) {
			buildNewBullet(key);
		}
		if (key == 3) {
			buildNewBullet(key);
		}
		if (key == 4) {
			buildNewBullet(key);
		}
	}
}
void OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//START GAME: 
	
	//HUD
	scene.hud.life = obiekt->lifeisbrutal;
	
	scene.HeadUpDisplay();
	//swiatlo

	GLfloat l0_ambient[] = { 0.2f, 0.2f, 0.2f };
	GLfloat l0_diffuse[] = { 1.0f, 1.0f, 1.0f };
	GLfloat l0_specular[] = { 0.5f, 0.5f, 0.5f };
	GLfloat l0_position[] = { 0, 7,7 , 1.0f };


	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);





	// Ustawienie kamery na podstawie jej stanu przechowywanego w zmiennej player.
	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z, // Pozycja kamery
		player.pos.x + player.tmp.x, player.pos.y + player.tmp.y, player.pos.z + player.tmp.z, // Punkt na ktory patrzy kamera (pozycja + kierunek)
		0.0f, 1.0f, 0.0f // Wektor wyznaczajacy pion
	);

	// Rendering ca³ej sceny
	scene.Render();


	

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float)width / height, .01f, 100.0f);
}
