#pragma once
#include "MyResourceManger.h"
#include "MyInput.h"
#include "ObjectCode.h"

namespace MyProject
{
	class MyObject
	{
	protected:
		TEXTURE_KEY			mTextureKey = L"Default.jpg";
		MESH_KEY			mMeshKey	= L"DEFAULT_MESH";
		SHADER_KEY			mShaderKey	= L"PixelShader.hlsl";
		vec4				mColor		= { 1.f, 1.f, 1.f, 1.f };
		ObjectCode			mObjectCode = ObjectCode::NOT;
		MyTransformer2D		mTransform;

		MyResourceManager&	mManager = MyResourceManager::GetInstance();
		MyInput&			mInput	 = MyInput::GetInstance();
		
	public:
		MyObject() = default;

		void SetColor(const vec4 _color);
		void SetTextureKey(const TEXTURE_KEY _key);
		void SetMeshKey(const MESH_KEY _key);
		void SetShaderKey(const SHADER_KEY _key);
		void SetObjectCode(const ObjectCode _objCode);

		void SetImageScale();

		const vec4&			GetColor() const;
		const MESH_KEY&		GetMeshKey() const;
		const TEXTURE_KEY&  GetTextureKey() const;
		const SHADER_KEY&	GetShaderKey() const;
		const ObjectCode&	GetObjectCode() const;

		MyTransformer2D& GetTransform();
		MyTransformer2D* operator->(); // 위치 변환 편하게 하려고 오버로딩 함
		
		virtual void Update(const float _deltaTime);
		virtual void Render();
	};
}
