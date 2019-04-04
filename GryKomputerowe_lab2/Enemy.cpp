#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(int enemytype) //1-big 2-carton
{
	rozm = 0.4f;
	id = 1;
	isalive = true;
	speed = 0.02f;;
	spin = 0;
	this->enemytype = enemytype;
	if (enemytype == 1) enemylife = 2;
	else enemylife = 0;
	spinspeed = 1;
	activate = false;
	radius2 =0.6;
}
bool Enemy::load(std::string filename)
{
	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};

	FILE * fp = fopen(filename.c_str(), "r");

	if (fp == NULL) {
		printf("Nie wczytano pliku %s\n", filename.c_str());
		return false;
	}

	vertices.clear();

	std::vector<vec3> loaded_vertices;
	std::vector<vec3> loaded_normals;
	std::vector<vec3> loaded_uvs;
	std::vector<SFace> loaded_faces;

	char buf[256];

	while (fgets(buf, 256, fp)) {
		if (buf[0] == 'v' && buf[1] == ' ') {
			vec3 vertex;
			sscanf(buf, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_vertices.push_back(vertex);
		}
		if (buf[0] == 'v' && buf[1] == 'n') {
			vec3 normal;
			sscanf(buf, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
			loaded_normals.push_back(normal);
		}
		if (buf[0] == 'v' && buf[1] == 't') {
			vec3 vertex;
			sscanf(buf, "vt %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_uvs.push_back(vertex);
		}
		if (buf[0] == 'f' && buf[1] == ' ') {
			SFace face;
			sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&face.v[0], &face.uv[0], &face.n[0],
				&face.v[1], &face.uv[1], &face.n[1],
				&face.v[2], &face.uv[2], &face.n[2]);
			loaded_faces.push_back(face);
		}
	}

	fclose(fp);

	vec3 minVertex = loaded_vertices[0];
	vec3 maxVertex = loaded_vertices[1];

	for (int i = 0; i < loaded_faces.size(); ++i) {
		for (int j = 0; j < 3; ++j) {

			int idxV = loaded_faces[i].v[j] - 1;
			int idxN = loaded_faces[i].n[j] - 1;
			int idxUV = loaded_faces[i].uv[j] - 1;

			vertices.push_back(loaded_vertices[idxV]);
			normals.push_back(loaded_normals[idxN]);
			uvs.push_back(loaded_uvs[idxUV]);

			if (loaded_vertices[idxV].x < minVertex.x)
				minVertex.x = loaded_vertices[idxV].x;

			if (loaded_vertices[idxV].x > maxVertex.x)
				maxVertex.x = loaded_vertices[idxV].x;


			if (loaded_vertices[idxV].y < minVertex.y)
				minVertex.y = loaded_vertices[idxV].y;

			if (loaded_vertices[idxV].y > maxVertex.y)
				maxVertex.y = loaded_vertices[idxV].y;


			if (loaded_vertices[idxV].z < minVertex.z)
				minVertex.z = loaded_vertices[idxV].z;

			if (loaded_vertices[idxV].z > maxVertex.z)
				maxVertex.z = loaded_vertices[idxV].z;

		}
	}

	float diffX = maxVertex.x - minVertex.x;
	float diffY = maxVertex.y - minVertex.y;
	float diffZ = maxVertex.z - minVertex.z;

	if (diffX < diffY)
	{
		if (diffY < diffZ)
		{
			radius = diffZ;
		}
		else
		{
			radius = diffY;
		}
	}
	else
	{
		if (diffX < diffZ)
		{
			radius = diffZ;
		}
		else
		{
			radius = diffX;
		}
	}

	radius /= 2;


	return true;
}

Enemy::Enemy(Enemy &ene) {

	enemytype = ene.enemytype;
	pos.x = ene.pos.x;
	pos.y = ene.pos.y;
	pos.z = ene.pos.z;
	isalive = true;
	speed = ene.speed;
	id = 1;
	textureName = ene.textureName;
	textureName3 = ene.textureName3;
	textureName2 = ene.textureName2;
	normals = ene.normals;
	vertices = ene.vertices;
	uvs = ene.uvs;
	spin = ene.spin;
	enemylife = ene.enemylife;
	spinspeed = ene.spinspeed;
	activate = ene.activate;
	radius2 = ene.radius2;

}


Enemy::~Enemy()
{
}

void Enemy::Render()
{
	

		float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
		float mat_diffuse[] = { 1, 1, 1 };
		float mat_specular[] = { 0.1f, 0.1f, 0.1f };

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	
	

		if (enemytype == 1) {
			if (enemylife == 2) {
				if (!textureName.empty())
				{
					glEnable(GL_TEXTURE_2D);
					TextureManager::getInstance()->BindTexture(textureName);

				}
			}
			if (enemylife == 1) {
				if (!textureName2.empty())
				{
					glEnable(GL_TEXTURE_2D);
					TextureManager::getInstance()->BindTexture(textureName2);

				}
			}
			if (enemylife == 0) {
				if (!textureName3.empty())
				{
					glEnable(GL_TEXTURE_2D);
					TextureManager::getInstance()->BindTexture(textureName3);

				}
			}
		

		if (spin == 360) { spin = 0; }
		else spin=spin+1*spinspeed;
		glPushMatrix();

		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(0.5, 0.5, 0.5);
		glRotatef(spin, 0, 1, 0);
		glBegin(GL_TRIANGLES);

		for (int i = 0; i < vertices.size(); i++)
		{
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glTexCoord2f(uvs[i].x, uvs[i].y);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}



		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
	if (enemytype == 2) {
	
		if (!textureName.empty())
		{
			glEnable(GL_TEXTURE_2D);
			TextureManager::getInstance()->BindTexture(textureName);

		}

		if (spin == 360) { spin = 0; }
		else spin=spin+1*spinspeed;
		glPushMatrix();

		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(0.3, 0.3, 0.3);
		glRotatef(spin, 0, 1, 0);
		glBegin(GL_TRIANGLES);

		for (int i = 0; i < vertices.size(); i++)
		{
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glTexCoord2f(uvs[i].x, uvs[i].y);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}



		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
}

void Enemy::Update()
{

	if (pos.y < 0.6) {
		pos.y += 0.03;
	}
	else {
		activate = true;

		pos.x += force.x / 1.5;
		pos.z += force.z / 1.5;

		force.x /= 1.2;
		force.y /= 1.2;
		force.z /= 1.2;
		

			if (Antiplayerposition.x < pos.x) {
				pos.x = pos.x - speed;
			}
			if (Antiplayerposition.x > pos.x) {
				pos.x = pos.x + speed;
			}
			if (Antiplayerposition.z < pos.z) {
				pos.z = pos.z - speed;
			}
			if (Antiplayerposition.z > pos.z) {
				pos.z = pos.z + speed;
			
		}
	

	}

}
