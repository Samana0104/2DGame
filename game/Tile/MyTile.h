#pragma once
#include "MyObject.h"
#include "CollisionComponent.h"

namespace MyProject
{
	class MyTile : public MyObject
	{
	private:
		CollisionComponent	mCollision;

		RECT_F mUV;
		int	   mRow;
		int	   mColumn;

	public:
		MyTile();

		CollisionComponent& GetCollsionComponent();
		void SetUVRect(const RECT_F _uv);

		void SetRow(const int _row);
		void SetColumn(const int _column);

		int GetRow() const;
		int GetColumn() const;

		const RECT_F& GetUVRect() const;

		virtual void Render();
	};
}

