#pragma once
#include "MyObject.h"
#include "MyCamera.h"
#include "CollisionComponent.h"

namespace MyProject
{
	class MyActor : public MyObject
	{
	protected:
		MyCamera* mCamera = nullptr;

	protected:
		MyActor() = default;

	public:
		void SetViewedCamera(MyCamera* _camera);

		virtual void Front(vec2 _move) = 0;
		virtual void Back(vec2 _move) = 0;
		virtual void Right(vec2 _move) = 0;
		virtual void Left(vec2 _move) = 0;
		virtual void Update(const float _deltaTime) override = 0;
		virtual void Render() override = 0;
	};
}

