#pragma once
#include "MySceneManager.h"
#include "MyTileManager.h"
namespace MyProject
{
	class MySceneStage1 : public MyScene
	{
	private:
		MyTileManager mTileMap;

	public:
		using MyScene::MyScene;

		virtual void Init() override;
		virtual void Update(float _deltaTime) override;
		virtual void Render() override;
		virtual void Release() override;
		virtual void Reset() override;
		virtual void Execute() override;
	};
}

