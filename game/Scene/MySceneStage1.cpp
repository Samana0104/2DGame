#include "pch.h"
#include "MySceneStage1.h"
using namespace MyProject;

void MySceneStage1::Init()
{
	mTileMap.LoadScript(L"../data/Image/Tile/stage1.tile");
}

void MySceneStage1::Update(float _deltaTime)
{
}

void MySceneStage1::Render()
{
	mTileMap.Render();
}

void MySceneStage1::Release()
{
}

void MySceneStage1::Reset()
{
}

void MySceneStage1::Execute()
{
}
