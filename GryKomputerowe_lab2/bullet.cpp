#include "stdafx.h"
#include "bullet.h"


bullet::bullet()
{
	id = 2;
time = 30;
speed = 0.4;
//load("../Resources/Model/bolt.obj");
//textureName = "bolt1";
}



bullet::~bullet()
{
}
bool bullet::load(std::string filename)
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
void bullet::Render()
{
	/*
	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);

	}
	*/
	glDisable(GL_LIGHTING);
	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = { color.x, color.y, color.z };
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);


	

	glPushMatrix();
	glColor3f(color.x, color.y, color.z);
	glTranslatef(pos.x, pos.y, pos.z);
	//glScalef(time / 60.0f, time / 60.0f, time / 60.0f);
	glutSolidSphere(radius, 24, 24);
/*	glScalef(0.1f, 0.1f, 0.1f);
	glRotatef(90, 0, 1, 0);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i++)
	{
		glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		glTexCoord2f(uvs[i].x, uvs[i].y);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	*/

	glPopMatrix();
	glColor3f(1, 1, 1);
	glEnable(GL_LIGHTING);
}

void bullet::Update()
{
	time = time - 1;
	if (direct == 1)pos.z = pos.z - speed;
	if (direct == 2)pos.z = pos.z + speed;
	if (direct == 3)pos.x = pos.x - speed;
	if (direct == 4)pos.x = pos.x + speed;
	if (time <= 0) {
		isalive = false;
	}
	

	//teleportacja

	if (sqrt((pos.x)*(pos.x) + (pos.z + 10)*(pos.z + 10)) < 0.5)
	{

		pos.x = 0;
		pos.z = 9.5;
	}
	if (sqrt((pos.x)*(pos.x) + (pos.z - 10)*(pos.z - 10)) < 0.5)
	{

		pos.x = 0;
		pos.z = -9.5;
	}

	if (sqrt((pos.x - 10)*(pos.x - 10) + (pos.z)*(pos.z)) < 0.5)
	{

		pos.x = -9.5;
		pos.z = 0;
	}

	if (sqrt((pos.x + 10)*(pos.x + 10) + (pos.z)*(pos.z)) < 0.5)
	{

		pos.x = 9.5;
		pos.z = 0;
	}




}