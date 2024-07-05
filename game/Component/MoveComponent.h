#pragma once
#include "MyCoreAPI.h"
#include "MyTransformer2D.h"

namespace MyProject
{
	class MoveComponent
	{
	private:
		static inline const float TOLERANCE = 4e-4f;

		vec2	mSpeed		  = { 1.f, 1.f };
		vec2 	mAcceleration = { 1.f, 1.f };

		bool	mIsXposBreaking = false;
		bool	mIsYposBreaking = false;

		MyTransformer2D & mTransform;

	public:
		MoveComponent(MyTransformer2D & _transform);

		void SetSpeed(const vec2 _speed);
		void SetAcceleration(const vec2 _acceleration);
		
		void AddSpeed(const vec2 _speed);
		void AddAcceleration(const vec2 _acceleration);

		void Break(const vec2 _scalar);

		vec2  GetSpeed() const;
		vec2  GetAcceleration() const;

		void  Update(float _deltaTime);
	};
}

