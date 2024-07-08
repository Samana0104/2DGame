#pragma once
#include "MyActor.h"
#include "SpriteComponent.h"
#include "MyObjectManager.h"

namespace MyProject
{
	class MyKey : public MyActor
	{
	private:
		SpriteComponent mSprite;

	private:
		virtual void OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj) override;

	public:
		MyKey();

		virtual void Update(const float _deltaTime) override;
		virtual void Render() override;

	};
};

