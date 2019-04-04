#pragma once

class vec3
{
public:
	vec3(void);
	vec3(float x, float y, float z);
	~vec3(void);

	static float distance(vec3 v1, vec3 v2);
	static vec3 cross(vec3 v1, vec3 v2);

	vec3 normalized();
	float length();

	vec3 operator+(vec3 v);
	vec3 operator-(vec3 v);
	vec3 operator*(float v);



	float x, y, z;
};