#include "pch.h"
#include "MySceneStage2.h"
using namespace MyProject;

void MySceneStage2::Init()
{
	mTileMap.LoadScript(L"../data/Image/Tile/stage2.tile");
}

void MySceneStage2::Update(float _deltaTime)
{
}

void MySceneStage2::Render()
{
	mTileMap.Render();
}

void MySceneStage2::Release()
{
}

void MySceneStage2::Reset()
{
}

void MySceneStage2::Execute()
{
}
