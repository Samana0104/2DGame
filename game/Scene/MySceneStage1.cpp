#include "pch.h"
#include "MySceneStage1.h"
using namespace MyProject;

void MySceneStage1::Init()
{
	mCurrentButton = 0;
	mTileMap.LoadScript(L"../data/Image/Tile/stage1.tile");
	mPauseBackground.SetColor({ 0.f, 0.f, 0.f, 1.f });
	mPauseBackground->SetScale({ 160.f, 90.f });
	mPauseBackground.SetShaderKey(L"BackgroundPause.hlsl");

	mButtons[0]->SetLocation({ 0.f, 11.f });
	mButtons[1]->SetLocation({ 0.f, 0.f });
	mButtons[2]->SetLocation({ 0.f, -11.f });
	mButtons[0].SetText(L"계속 하기");
	mButtons[1].SetText(L"다시 시작");
	mButtons[2].SetText(L"메뉴로 나가기");
	mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
}

void MySceneStage1::Update(float _deltaTime)
{
	if (mInput.GetCurrentKeyState(VK_ESCAPE) == KeyState::KEY_DOWN)
	{
		if (isPause)
		{
			isPause = false;
		}
		else
		{
			mManager.mSound[L"pause.wav"]->Play();
			isPause = true;
		}
	}

	if (mInput.GetCurrentKeyState(VK_UP) == KeyState::KEY_DOWN)
	{
		if (isPause)
		{
			mManager.mSound[L"menu-change.wav"]->Play();
			mButtons[mCurrentButton].SetCurrentState(SelectState::DEFAULT);
			mCurrentButton--;
			mCurrentButton = (mCurrentButton + 3) % 3;
			mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
		}
	}
	if (mInput.GetCurrentKeyState(VK_DOWN) == KeyState::KEY_DOWN)
	{
		if (isPause)
		{
			mManager.mSound[L"menu-change.wav"]->Play();
			mButtons[mCurrentButton].SetCurrentState(SelectState::DEFAULT);
			mCurrentButton++;
			mCurrentButton %= 3;
			mButtons[mCurrentButton].SetCurrentState(SelectState::ACTIVE);
		}
	}

	if (mInput.GetCurrentKeyState(VK_RETURN) == KeyState::KEY_DOWN ||
		mInput.GetCurrentKeyState(0x5A) == KeyState::KEY_DOWN ||
		mInput.GetCurrentKeyState(0x58) == KeyState::KEY_DOWN)
	{
		if (isPause)
		{
			if (mCurrentButton == 0)
			{
				mManager.mSound[L"menu-select.wav"]->Play();
				isPause = false;
				//mManager.mSound[L"title-start.wav"]->Play();
				//mSceneManager.SetCurrentScene(L"STAGE");
			}
			else if (mCurrentButton == 1)
			{
			}
			else if (mCurrentButton == 2)
			{
				mManager.mSound[L"menu-select.wav"]->Play();
				mSceneManager.SetCurrentScene(L"STAGE");
			}
		}
	}

	for (int i = 0; i < 3; i++)
		mButtons[i].Update(_deltaTime);

	mPlayer.Update(_deltaTime);
}

void MySceneStage1::Render()
{
	mTileMap.Render();

	if (isPause)
	{
		mPauseBackground.Render();
		for (int i = 0; i < 3; i++)
			mButtons[i].Render();
	}
	mPlayer.Render();
	mManager.mFont.DrawTextForDebugging(L"%f %f",
		mPlayer->GetLocation().x,
		mPlayer->GetLocation().y);
	mTileMap.Update(mPlayer);
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
