#include "pch.h"
#include "MySceneStage3.h"
using namespace MyProject;

void MySceneStage3::Init()
{
	mTileMap.LoadScript(L"../data/Image/Tile/stage3.tile");
}

void MySceneStage3::Update(float _deltaTime)
{
}

void MySceneStage3::Render()
{
	mTileMap.Render();
}

void MySceneStage3::Release()
{
}

void MySceneStage3::Reset()
{
}

void MySceneStage3::Execute()
{
}
