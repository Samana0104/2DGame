#pragma once
#include "MyActor.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

namespace MyProject
{
	enum PlayerAction : uint
	{
		STAND,
		STAND_HEAVY,
		WALK,
		WALK_HEAVY,
		JUMP,
		JUMP_HEAVY,
		FALL,
		FALL_HEAVY
	};

	class MyPlayer : public MyActor
	{
	private:
		MyActor*		mObjectOnHand = nullptr;
		SpriteComponent mSprite[8];
		
		PlayerAction mCurrentAction = PlayerAction::STAND;

	private:
		void Right();
		void Left();
		void Stand();

		void UpdatePlayerState();

		virtual void OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj) override;
	public:
		MyPlayer();

		virtual void Update(const float _deltaTime) override;
		virtual void Render() override;
	};
};
