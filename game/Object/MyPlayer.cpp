#include "pch.h"
#include "MyPlayer.h"
using namespace MyProject;

MyPlayer::MyPlayer()
{
	mSprite[PlayerAction::STAND].SetSpriteKey(L"player-stand-right.sprite");

	mSprite[PlayerAction::STAND].SetLoop(false);
	mSprite[PlayerAction::STAND_HEAVY].SetLoop(false);
	mSprite[PlayerAction::WALK].SetLoop(true);
	mSprite[PlayerAction::WALK].SetChangeTime(0.08f);
		//STAND,
		//STAND_HEAVY,
		//WALK,
		//WALK_HEAVY,
		//JUMP,
		//JUMP_HEAVY,
		//FALL,
		//FALL_HEAVY

	mSprite[PlayerAction::STAND].SetSpriteKey(L"player-stand-right.sprite");
	mSprite[PlayerAction::STAND].SetSpriteKey(L"player-stand-right.sprite");
	mSprite[PlayerAction::STAND].SetSpriteKey(L"player-stand-right.sprite");
	mSprite[PlayerAction::STAND].SetSpriteKey(L"player-stand-right.sprite");
	mTransform.SetScale({ 10.f, 10.f });
	mMove.SetAcceleration({ 0.f, 0.f });
	mMove.SetSpeed({ 0.f, 0.f });
	mCollision.ResizeCollisionArea();
}

void MyPlayer::OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj)
{
	mManager.mFont.DrawTextForDebugging(L"Ãæµ¹");
}

void MyPlayer::Right()
{
	mMove.SetSpeed({ 35.f, 0.f });
	mCurrentAction = PlayerAction::WALK;
	mSprite[PlayerAction::WALK].SetSpriteKey(L"player-walk-right.sprite");
	mSprite[PlayerAction::STAND].SetSpriteKey(L"player-stand-right.sprite");
}

void MyPlayer::Left()
{
	mMove.SetSpeed({ -35.0f, 0.f });
	mCurrentAction = PlayerAction::WALK;
	mSprite[PlayerAction::WALK].SetSpriteKey(L"player-walk-left.sprite");
	mSprite[PlayerAction::STAND].SetSpriteKey(L"player-stand-left.sprite");
}

void MyPlayer::Stand()
{
	mMove.SetSpeed({ 0.f, 0.f });
	mCurrentAction = PlayerAction::STAND;
	mSprite[PlayerAction::STAND].ResetAnimation();
}

void MyPlayer::UpdatePlayerState()
{
	if (mInput.GetCurrentKeyState(VK_RIGHT) == KeyState::KEY_HOLD)
	{
		Right();
	}

	if (mInput.GetCurrentKeyState(VK_LEFT) == KeyState::KEY_HOLD)
	{
		Left();
	}

	if (mInput.GetCurrentKeyState(VK_RIGHT) == KeyState::KEY_UP ||
		mInput.GetCurrentKeyState(VK_LEFT) == KeyState::KEY_UP)
		Stand();
}

void MyPlayer::Update(const float _deltaTime)
{
	UpdatePlayerState();
	mMove.Update(_deltaTime);
	mSprite[mCurrentAction].Update(_deltaTime);
}

void MyPlayer::Render()
{
	mSprite[mCurrentAction].Render(*this);
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
