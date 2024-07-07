#include "pch.h"
#include "MyWoodBox.h"
using namespace MyProject;

MyWoodBox::MyWoodBox()
{
	SetObjectCode(ObjectCode::WOOD_BOX);
	mMove.SetAccelY(-160.f);
	SetTextureKey(L"wood_box.png");
	mTransform->SetScale({ 8.5f, 6.f });
	mCollision.ResizeCollisionArea();
}

void MyWoodBox::OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj)
{
	vec2 correction = CollisionComponent::GetCorrectionForCollision(mMove.GetOffset(), _self, _target);
	ObjectCode targetObjCode = _targetObj.GetObjectCode();

	switch (targetObjCode)
	{
	case ObjectCode::TILE:
		mTransform.AddLocation(correction);

		if (abs(correction.x) > TOLERANCE)
		{
			mManager.mSound[L"box-hit.wav"]->Play();
			mMove.SetSpeedX(0.f);
			mMove.SetAccelY(-160.f);

			if(correction.x > TOLERANCE)
				mMove.SetAccelX(30.f);
			else if(correction.x < -TOLERANCE)
				mMove.SetAccelX(-30.f);
		}

		if (correction.y > 0.f)
		{
			mMove.SetAccelX(0.f);
			mMove.SetSpeedX(0.f);
			mMove.SetSpeedY(0.f);
		}
		else if (correction.y < 0.f)
		{
			mMove.SetSpeedY(0.f);
		}
		//else
		//{
		//	RECT_F intersectRect = CollisionComponent::GetIntersectionRect(_self, _target);
		//	vec2 myVec = mTransform.GetLocation();
		//	vec2 targetVec = _targetObj->GetLocation();

		//	// 타겟이 오른쪽에 있다면
		//	if ((targetVec - myVec).x > 0)
		//		mTransform.AddLocation({ -(intersectRect.right - intersectRect.left) - TOLERANCE, 0.f });
		//	else
		//		mTransform.AddLocation({ intersectRect.right - intersectRect.left + TOLERANCE, 0.f });
		//}
		break;

	case ObjectCode::WOOD_BOX:
		if (correction.y > TOLERANCE)
		{
			mTransform.AddLocation(correction);
			mMove.SetSpeedY(0.f);
			mMove.SetSpeedX(0.f);
		}
	}
}

void MyWoodBox::Update(const float _deltaTime)
{
	mMove.Update(_deltaTime);
}
