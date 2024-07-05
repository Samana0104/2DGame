#pragma once
#include "MyTransformer2D.h"
#include "MyMesh2D.h"

namespace MyProject
{
	// 나중에 다중 충돌 구현을 위해 메쉬 헤더만 포함
	enum CollisionType
	{
		CLICK=0,
		RECT
	};
	
	class CollisionComponent
	{
	private:
		bool mIsCollisionable = true;

		MyTransformer2D&    mTransform;
		std::vector<RECT_F> mCollisionAreas;

	public:
		CollisionComponent(MyTransformer2D& _transform);

		void AddCollisionArea(const RECT_F _collsionArea);
		// 나중에 여러 모양 충돌 구현할지도?
		void SetCollisionable(bool _isCollisionable);
		void ClearCollisionArea();

		bool IsCollision(const RECT_F& _target);
		bool IsCollisionable() const;


		static bool IsPointInRect(const RECT_F rt1, const vec2 pt);
		static bool IsAABBCollision(const RECT_F& rt1, const RECT_F& rt2);
		static bool IsAABBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM);
		static bool IsOBBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM);
	};
}

