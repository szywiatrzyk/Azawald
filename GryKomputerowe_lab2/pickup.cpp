#include "stdafx.h"
#include "pickup.h"


pickup::pickup(int x, int y, int z,  int mode,float scale)  //1-heal 2-machinegun 3-speedboost
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	spin = 0;
	isalive = true;
	activate = false;
	id = 4;
	this->scale = scale;
	whoactive = mode;
}
pickup::pickup(pickup &pik) {
	pos.x = pik.pos.x;
	pos.y = pik.pos.y;
	pos.z = pik.pos.z;
	isalive = true;
	activate = false;
	id = 4;
	spin = 0;
	textureName = pik.textureName;
	normals = pik.normals;
	vertices=pik.vertices;
	uvs=pik.uvs;
	whoactive = pik.whoactive;
	scale = pik.scale;


}

pickup::~pickup()
{
}

bool pickup::load(std::string filename)
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


void pickup::Render() {
	
		if (!textureName.empty())
		{
			glEnable(GL_TEXTURE_2D);
			TextureManager::getInstance()->BindTexture(textureName);

		}
	
	
	
	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = { 1, 1, 1 };
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	if (spin == 1080) { spin = 0; }
	else spin++;
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(scale, scale , scale);
	glRotatef(spin/3, 0, 1, 0);
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

void pickup::Update() {
	if (pos.y < 0.6) {
		pos.y += 0.03;
	}

	if (sqrt((Antiplayerposition.x - pos.x)*(Antiplayerposition.x - pos.x) + (Antiplayerposition.z - pos.z)*(Antiplayerposition.z - pos.z))<0.5)
	{
	
		activate = true;
	}


}