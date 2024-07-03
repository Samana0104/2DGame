#include "pch.h"
#include "MyObject.h"
using namespace MyProject;

MyObject::MyObject() :
	mTextureKey(L"Default.jpg"), 
	mMeshKey(L"DEFAULT_MESH"),
	mShaderKey(L"PixelShader.hlsl"),
	mColor({ 1.f, 1.f, 1.f, 1.f })
{
}

void MyObject::SetImageScale()
{
	vec2 windowSize = MyWindow::GetInstance().GetWindowSizeVec2();
	vec2 imageSize = mManager.mTexture[mTextureKey]->GetTextureSizeVec2();
	vec2 cartesianSize = mTransform.GetCartesianSize();
	
	mTransform.SetScale((imageSize/windowSize) * cartesianSize);
}

void MyObject::SetColor(vec4 _color)
{
	mColor = _color;
}

void MyObject::SetTextureKey(TEXTURE_KEY _key)
{
	mTextureKey = _key;
}

void MyObject::SetMeshKey(MESH_KEY _key)
{
	mMeshKey = _key;
}

void MyObject::SetShaderKey(SHADER_KEY _key)
{
	mShaderKey = _key;
}


const vec4& MyObject::GetColor() const
{
	return mColor;
}

const MESH_KEY& MyProject::MyObject::GetMeshKey() const
{
	return mMeshKey;
}

const TEXTURE_KEY& MyObject::GetTextureKey() const
{
	return mTextureKey;
}

const SHADER_KEY& MyObject::GetShaderKey() const
{
	return mShaderKey;
}

MyTransformer2D& MyObject::GetTransform() 
{
	return mTransform;
}

MyTransformer2D* MyObject::operator->()
{
	return &mTransform;
}

void MyObject::Update(const float _deltaTime)
{
}

void MyObject::Render()
{
	mManager.mShader[mShaderKey]->SetUpConfiguration();
	mManager.mTexture[mTextureKey]->Render();
	mManager.mMesh[mMeshKey]->Draw(mTransform.GetModelMat(), mColor);
}
