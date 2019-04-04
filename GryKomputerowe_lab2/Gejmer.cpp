#include "stdafx.h"
#include "Gejmer.h"
#include "math.h"

Gejmer::Gejmer(void)
{
	lifeisbrutal = 3;
	id = 3;
	isalive == true;
	nomove = 1;
	stillmoving = -1;
	modelScale = vec3(1, 1, 1);
	kolizjon = false;
	kolizjondirekszyn = 0;
	iter = 0;
	upadek = false;
	p1 = true;
	p2 = true;
	p3 = true;
	p4 = true;
	plicz = 0;
	plicz1 = 0;
	plicz2 = 0;
	plicz3 = 0;
	imunemod = false;
}


Gejmer::~Gejmer(void)
{
}

bool Gejmer::load(std::string filename)
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
bool Gejmer::load1(std::string filename)
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

	vertices1.clear();

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

			vertices1.push_back(loaded_vertices[idxV]);
			normals1.push_back(loaded_normals[idxN]);
			uvs1.push_back(loaded_uvs[idxUV]);

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
bool Gejmer::load2(std::string filename)
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

	vertices2.clear();

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

			vertices2.push_back(loaded_vertices[idxV]);
			normals2.push_back(loaded_normals[idxN]);
			uvs2.push_back(loaded_uvs[idxUV]);

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
bool Gejmer::load3(std::string filename)
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

	vertices3.clear();

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

			vertices3.push_back(loaded_vertices[idxV]);
			normals3.push_back(loaded_normals[idxN]);
			uvs3.push_back(loaded_uvs[idxUV]);

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
bool Gejmer::load4(std::string filename)
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

	vertices4.clear();

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

			vertices4.push_back(loaded_vertices[idxV]);
			normals4.push_back(loaded_normals[idxN]);
			uvs4.push_back(loaded_uvs[idxUV]);

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
bool Gejmer::load5(std::string filename)
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

	vertices5.clear();

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

			vertices5.push_back(loaded_vertices[idxV]);
			normals5.push_back(loaded_normals[idxN]);
			uvs5.push_back(loaded_uvs[idxUV]);

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


void Gejmer::Render()
{
	if (imunemod == false) {

		if (facing_shot == 0) {
			if (nomove == 0) {
				if (stillmoving != 1) {

					if (!textureName1.empty())
					{
						glEnable(GL_TEXTURE_2D);
						TextureManager::getInstance()->BindTexture(textureName1);

					}
				}
				if (stillmoving == 1) {
					if (!textureName2.empty())
					{
						glEnable(GL_TEXTURE_2D);
						TextureManager::getInstance()->BindTexture(textureName2);

					}
				}
			}
			if (nomove == 1) {
				if (!textureName.empty())
				{
					glEnable(GL_TEXTURE_2D);
					TextureManager::getInstance()->BindTexture(textureName);

				}
			}
		}

		if (facing_shot != 0) {
			if (nomove == 0) {
				if (stillmoving != 1) {
					if (!textureName4.empty())
					{
						glEnable(GL_TEXTURE_2D);
						TextureManager::getInstance()->BindTexture(textureName4);

					}
				}
				if (stillmoving == 1) {
					if (!textureName5.empty())
					{
						glEnable(GL_TEXTURE_2D);
						TextureManager::getInstance()->BindTexture(textureName5);

					}
				}
			}
			if (nomove == 1) {

				if (!textureName3.empty())
				{
					glEnable(GL_TEXTURE_2D);
					TextureManager::getInstance()->BindTexture(textureName3);

				}
			}
		}


	}
	else if (!textureimune.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureimune);

	}




	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = { color.x, color.y, color.z };
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	//glColor3f(0, 1, 1);

	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);
	//glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);
	glScalef(0.3f, 0.3f, 0.3f);
	glScalef(modelScale.x, modelScale.y, modelScale.z);
	if (facing_shot == 0) {

		if (facing_move == 1) {
			glRotatef(180.0, 0.0f, 1.0f, 0.0f);
		}

		if (facing_move == 3) {
			glRotatef(-90.0, 0.0f, 1.0f, 0.0f);
		}
		if (facing_move == 4) {
			glRotatef(90.0, 0.0f, 1.0f, 0.0f);
		}

	}
	else {

		if (facing_shot == 1) {
			glRotatef(180.0, 0.0f, 1.0f, 0.0f);
		}

		if (facing_shot == 3) {
			glRotatef(-90.0, 0.0f, 1.0f, 0.0f);
		}
		if (facing_shot == 4) {
			glRotatef(90.0, 0.0f, 1.0f, 0.0f);
		}

	}
	glBegin(GL_TRIANGLES);
	if (facing_shot == 0) {
		if (nomove == 0) {
			if (stillmoving != 1) {


				for (int i = 0; i < vertices1.size(); i++)
				{
					glNormal3f(normals1[i].x, normals1[i].y, normals1[i].z);
					glTexCoord2f(uvs1[i].x, uvs1[i].y);
					glVertex3f(vertices1[i].x, vertices1[i].y, vertices1[i].z);
				}
			}
			if (stillmoving == 1) {

				for (int i = 0; i < vertices2.size(); i++)
				{
					glNormal3f(normals2[i].x, normals2[i].y, normals2[i].z);
					glTexCoord2f(uvs2[i].x, uvs2[i].y);
					glVertex3f(vertices2[i].x, vertices2[i].y, vertices2[i].z);
				}
			}
		}
		if (nomove == 1) {

			for (int i = 0; i < vertices.size(); i++)
			{
				glNormal3f(normals[i].x, normals[i].y, normals[i].z);
				glTexCoord2f(uvs[i].x, uvs[i].y);
				glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
			}
		}
	}

	if (facing_shot != 0) {
		if (nomove == 0) {
			if (stillmoving != 1) {

				for (int i = 0; i < vertices1.size(); i++)
				{
					glNormal3f(normals4[i].x, normals4[i].y, normals4[i].z);
					glTexCoord2f(uvs4[i].x, uvs4[i].y);
					glVertex3f(vertices4[i].x, vertices4[i].y, vertices4[i].z);
				}
			}
			if (stillmoving == 1) {
				for (int i = 0; i < vertices2.size(); i++)
				{
					glNormal3f(normals5[i].x, normals5[i].y, normals5[i].z);
					glTexCoord2f(uvs5[i].x, uvs5[i].y);
					glVertex3f(vertices5[i].x, vertices5[i].y, vertices5[i].z);
				}
			}
		}
		if (nomove == 1) {

			for (int i = 0; i < vertices.size(); i++)
			{
				glNormal3f(normals3[i].x, normals3[i].y, normals3[i].z);
				glTexCoord2f(uvs3[i].x, uvs3[i].y);
				glVertex3f(vertices3[i].x, vertices3[i].y, vertices3[i].z);
			}
		}
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Gejmer::Update()
{

	//¿ycia
	if (lifeisbrutal == 0 || lifeisbrutal < 0) {
		//isalive = false;
	}
	if (upadek == true) {
		if (pos.x > 10) 	pos.x = 10.5;
		if (pos.x < -10) 	pos.x = -10.5;
		if (pos.z > 10) 	pos.z = 10.5;
		if (pos.z < -10) 	pos.z = -10.5;


	}

	//upadek
	if (pos.x > 10 || pos.x < -10 || pos.z>10 || pos.z < -10) {
		upadek = true;
		pos.y = pos.y - 0.1f;

	}

	//kolizja
	if (kolizjon == true) {
		if (iter < 5) {
			if (kolizjondirekszyn == 1) {
				pos.x = pos.x - 0.2f;
			}
			if (kolizjondirekszyn == 2) {
				pos.x = pos.x + 0.2f;
			}
			if (kolizjondirekszyn == 3) {
				pos.z = pos.z - 0.2f;
			}
			if (kolizjondirekszyn == 4) {
				pos.z = pos.z + 0.2f;
			}

			iter++;
		}
		else {
			kolizjon = false;
			iter = 0;
		}



	}

	//teleportacja

	if (sqrt((pos.x)*(pos.x) + (pos.z + 10)*(pos.z + 10)) < 0.5 && p1 == true)
	{

		pos.x = 0;
		pos.z = 9.5;
		p1 = false;
	}
	if (sqrt((pos.x)*(pos.x) + (pos.z - 10)*(pos.z - 10)) < 0.5 && p2 == true)
	{

		pos.x = 0;
		pos.z = -9.5;
		p2 = false;
	}

	if (sqrt((pos.x - 10)*(pos.x - 10) + (pos.z)*(pos.z)) < 0.5 &&  p3 == true)
	{

		pos.x = -9.5;
		pos.z = 0;
		p3 = false;
	}

	if (sqrt((pos.x + 10)*(pos.x + 10) + (pos.z)*(pos.z)) < 0.5 && p4 == true)
	{

		pos.x = 9.5;
		pos.z = 0;
		p4 = false;
	}

	if (plicz == 500) {
		plicz = 0;
		p1 = true;

	}
	else plicz++;


	if (plicz1 == 500) {
		plicz1 = 0;
		p2 = true;

	}
	else plicz1++;


	if (plicz2 == 500) {
		plicz2 = 0;
		p3 = true;

	}
	else plicz2++;

	if (plicz3 == 500) {
		plicz3 = 0;
		p4 = true;

	}
	else plicz3++;

}
