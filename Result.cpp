#include "Result.h"

Result::Result()
{
}

void Result::Updata(char* keys)
{
	rotate.y += 0.1f;
	//rotate.y -= 0.1f;

	if (keys[DIK_D])
	{
		translate.x += 0.01f;
	}
	if (keys[DIK_A])
	{
          translate.x -= 0.01f;	
	}

	if (keys[DIK_W])
	{
		translate.z += 0.03f;
	}
	if (keys[DIK_S])
	{
		translate.z -= 0.03f;
	}

	Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	Matrix4x4 worldviewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	for (uint32_t i = 0; i < 3; ++i)
	{
		//NDCまで変換。Transformを使うと同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることになる
		Vector3 ndcVertex = Transform(kLocalVertices[i], worldviewProjectionMatrix);
		//Viewport変換を使ってScreen空間へ
		screenVertices[i] = Transform(ndcVertex, viewportMatrix);
	}
}

void Result::Draw()
{
	Novice::DrawTriangle(
		(int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y,
		(int)screenVertices[2].x, (int)screenVertices[2].y, RED , kFillModeSolid
	);
}