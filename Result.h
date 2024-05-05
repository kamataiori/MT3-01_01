#pragma once
#include "MathFunctions.h"

class Result
{
public:

	Vector3 rotate{};
	Vector3 translate{};
	Vector3 kLocalVertices[3] = { { 0.0f,0.5f,0.0f },{0.5f,-0.5f,0.0f},{-0.5f,-0.5f,0.0f} };
	//Matrix4x4 worldviewProjectionMatrix = {100};
	Vector3 cameraPosition = { 0.0f,0.0f,-5.0f };
	Vector3 screenVertices[3] = {};
	static const int kWindowWidth = 1280;
	static const int kWindowHeight = 720;



	Result();

	void Updata(char* keys);

	void Draw();

};

