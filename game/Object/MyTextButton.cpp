#include "pch.h"
#include "MyTextButton.h"
using namespace MyProject;

MyTextButton::MyTextButton()
{
	mBtnLeftObj->SetScale({ 18.f, 13.f });
	mBtnLeftObj->AddScaleAsRatio(0.4f);
	mBtnRightObj->SetScale({ 18.f, 13.f });
	mBtnRightObj->AddScaleAsRatio(0.4f);

	mBtnLeftSprite.SetSpriteKey(L"menu_left.sprite");
	mBtnLeftSprite.SetChangeTime(0.05f);
	mBtnRightSprite.SetSpriteKey(L"menu_right.sprite");
	mBtnRightSprite.SetChangeTime(0.05f);

	mTextRect = { 0.f, 0.f, 0.f, 0.f };
}

void MyTextButton::SetText(wstringV _text)
{
	mText = _text;
	SetScale();
}

void MyTextButton::SetScale()
{
	float fontSize	= mManager.mFont[L"BUTTON_FONT"]->GetFontSize();
	float length	= static_cast<float>(mText.size()) * fontSize;
	float length2 = length;
	vec2 mainLocation = mTransform.GetLocation();

	length *= MyTransformer2D::GetCartesianSize().x / D3Device::GetInstance().GetViewportSize().x;

	mBtnLeftObj->SetLocation({mainLocation.x-length/2.f -8.f, mainLocation.y-0.5f});
	mBtnRightObj->SetLocation({mainLocation.x+length/2.f + 8.f, mainLocation.y-0.5f});
	
	mainLocation = MyTransformer2D::CartesianToPixel(mainLocation);

	mTextRect =
	{
		mainLocation.x - length2 / 2.f,
		mainLocation.y - fontSize / 2.f,
		mainLocation.x + length2 / 2.f,
		mainLocation.y + fontSize / 2.f
	};
}

void MyTextButton::Update(const float _deltaTime)
{
	SetScale();
	mBtnLeftSprite.Update(_deltaTime);
	mBtnRightSprite.Update(_deltaTime);
}

void MyTextButton::Render()
{
	if (GetCurrentState() == SelectState::ACTIVE)
	{
		mManager.mShader[L"PixelShaderAlpha.hlsl"]->SetUpConfiguration();
		mBtnLeftSprite.Render(mBtnLeftObj);
		mManager.mMesh[mBtnLeftObj.GetMeshKey()]->Draw(mBtnLeftObj->GetModelMat());
		mBtnRightSprite.Render(mBtnRightObj);
		mManager.mMesh[mBtnRightObj.GetMeshKey()]->Draw(mBtnRightObj->GetModelMat());
	}
	mManager.mFont[L"BUTTON_FONT"]->DrawTexts(mText, mTextRect, { 1.f, 1.f, 1.f, 1.f });
}
