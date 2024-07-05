#pragma once
#include "MyTransformer2D.h"
#include "MyMesh2D.h"

namespace MyProject
{
	// ���߿� ���� �浹 ������ ���� �޽� ����� ����
	enum CollisionType
	{
		CLICK=0,
		RECT
	};
	
	class MyActor;
	using COLLISION_FUNC = std::function<void(RECT_F&, RECT_F&, MyActor&)>;

	class CollisionComponent
	{
	private:
		bool mIsCollisionable = true;

		MyActor& mObj;

		std::vector<RECT_F>	 mCollisionAreas;
		COLLISION_FUNC		 mCollisionFunc;

	public:
		CollisionComponent(MyActor & _obj);

		void AddCollisionArea(const RECT_F _collsionArea);
		// ���߿� ���� ��� �浹 ����������?
		void SetCollisionable(bool _isCollisionable);
		void ClearCollisionArea();

		bool IsCollision(const RECT_F& _target);
		void IsCollisionWithEvent(MyActor & _targetObj);

		bool IsCollisionable() const;
		
		void RegisterCollisionEvent(COLLISION_FUNC _func);
		void ResizeCollisionArea();

		static bool IsPointInRect(const RECT_F rt1, const vec2 pt);
		static bool IsAABBCollision(const RECT_F& rt1, const RECT_F& rt2);
		static bool IsAABBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM);
		static bool IsOBBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM);
	};
}

