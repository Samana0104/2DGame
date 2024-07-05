#include "pch.h"
#include "MyTile.h"
using namespace MyProject;

MyTile::MyTile() :
	mCollision(mTransform),
	mUV({})
{
	mCollision.AddCollisionArea(mTransform.GetCartesianRectF());
	mRow = 0;
	mColumn = 0;
}

CollisionComponent& MyTile::GetCollsionComponent()
{
	return mCollision;
}

void MyTile::SetUVRect(const RECT_F _uv)
{
	mUV = _uv;
}

void MyTile::SetRow(const int _row)
{
	mRow = _row;
}

void MyTile::SetColumn(const int _column)
{
	mColumn = _column;
}

int MyTile::GetRow() const
{
	return mRow;
}

int MyTile::GetColumn() const
{
	return mColumn;
}

const RECT_F& MyTile::GetUVRect() const
{
	return mUV;
}

void MyTile::Render()
{
	vec2 imageSize = mManager.mTexture[mTextureKey]->GetTextureSizeVec2();
	mManager.mShader[mShaderKey]->SetUpConfiguration();
	mManager.mTexture[mTextureKey]->Render();
	mManager.mMesh[mMeshKey]->SetUVVertexAsRect(mUV, imageSize);
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
