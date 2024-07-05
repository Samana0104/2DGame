#pragma once
#include "MySceneManager.h"
#include "MyTileManager.h"
#include "MyTextButton.h"
namespace MyProject
{
	class MySceneStage2 : public MyScene
	{
	private:
		MyTileManager mTileMap;
		MyTextButton mButtons[3];
		MyObject mPauseBackground;

		int mCurrentButton;
		bool isPause = false;

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
