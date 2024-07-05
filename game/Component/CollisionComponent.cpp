#include "pch.h"
#include "CollisionComponent.h"
#include "MyActor.h"
using namespace MyProject;

CollisionComponent::CollisionComponent(MyActor& _obj):
    mObj(_obj)
{
    mCollisionAreas.reserve(5);
}

void CollisionComponent::AddCollisionArea(const RECT_F _collisionArea)
{
    mCollisionAreas.push_back(_collisionArea);
}

void CollisionComponent::SetCollisionable(bool _isCollisionable)
{
    mIsCollisionable = _isCollisionable;
}

void CollisionComponent::ClearCollisionArea()
{
    mCollisionAreas.clear();
}

bool CollisionComponent::IsCollision(const RECT_F& _target)
{
    if (!mIsCollisionable)
        return false;

    RECT_F transformRect = mObj->GetCartesianRectF();
    RECT_F collisionRect;
    
    for (auto& collisionArea : mCollisionAreas)
    {
        collisionRect =
        {
            collisionArea.left + transformRect.left,
            collisionArea.top + transformRect.top,
            collisionArea.right + transformRect.right,
            collisionArea.bottom + transformRect.bottom
        };

        if (IsAABBCollision(collisionRect, _target))
            return true;
    }
    
    return false;
}

void CollisionComponent::IsCollisionWithEvent(MyActor & _targetObj)
{
    // 충돌 오브젝트가 아니라면
    CollisionComponent& targetComponent  = _targetObj.GetCollisionComponent();

    if (!mIsCollisionable || !targetComponent.mIsCollisionable)
        return;

    vec2 myLocation = mObj->GetLocation();
    RECT_F myCollisionRect;
    auto a = MyResourceManager::GetInstance().mFont[L"DEBUG_FONT"]->GetBrush();

    // 이차원 위치 벡터를 더해야하는데 잘못 더한듯
    vec2 targetLocation = _targetObj->GetLocation();
    RECT_F targetCollisionRect;

    for (auto& selfRange : mCollisionAreas)
    {
        for(auto& targetRange : targetComponent.mCollisionAreas)
        {
			myCollisionRect =
			{
				selfRange.left + myLocation.x,
				selfRange.top + myLocation.y,
				selfRange.right + myLocation.x,
				selfRange.bottom + myLocation.y
			};
			targetCollisionRect =
			{
				targetRange.left + targetLocation.x,
				targetRange.top + targetLocation.y,
				targetRange.right + targetLocation.x,
				targetRange.bottom + targetLocation.y
			};


            RECT_F n1 = MyTransformer2D::CartesianToPixelRect(myCollisionRect);
            RECT_F n2 = MyTransformer2D::CartesianToPixelRect(targetCollisionRect);

            D3Device::GetInstance().mD2dRT->BeginDraw();
            D3Device::GetInstance().mD2dRT->DrawRectangle(&n1, a.Get());
            D3Device::GetInstance().mD2dRT->DrawRectangle(&n2, a.Get());
            D3Device::GetInstance().mD2dRT->EndDraw();
            if (IsAABBCollision(myCollisionRect, targetCollisionRect))
            {
                if (mCollisionFunc != nullptr)
                    mCollisionFunc(myCollisionRect, targetCollisionRect, _targetObj);
                if(targetComponent.mCollisionFunc != nullptr)
                    targetComponent.mCollisionFunc(myCollisionRect, targetCollisionRect,  _targetObj);
            }
		}
    }
}

bool CollisionComponent::IsCollisionable() const
{
    return mIsCollisionable;
}

void CollisionComponent::RegisterCollisionEvent(COLLISION_FUNC _func)
{
    mCollisionFunc = _func;
}

void CollisionComponent::ResizeCollisionArea()
{
    ClearCollisionArea();
    mCollisionAreas.push_back(mObj->GetCartesianScaleRectF());
}

bool CollisionComponent::IsPointInRect(const RECT_F rt1, const vec2 pt)
{
	if (rt1.left <= pt.x && rt1.right >= pt.x)
	{
		if (rt1.top >= pt.y && rt1.bottom <= pt.y)
		{
			return true;
		}
	}
	return false;
}

bool CollisionComponent::IsAABBCollision(const RECT_F& rt1, const RECT_F& rt2)
{
    // 내 생각에는 여기 AABB 콜리젼이 잘못된듯?
	float minX, maxX, minY, maxY;
	minX = min(rt1.left, rt2.left);
	maxX = max(rt1.right, rt2.right);
	minY = min(rt1.top, rt2.top);
	maxY = max(rt1.bottom, rt2.bottom);
	float sizeX, sizeY;
	sizeX = maxX - minX;
	sizeY = maxY - minY;

	float  rt1W, rt1H, rt2W, rt2H;
	rt1W = rt1.right - rt1.left;// rt1.w + rt2.w;
	rt1H = rt1.bottom - rt1.top;
	rt2W = rt2.right - rt2.left;// rt1.w + rt2.w;
	rt2H = rt2.bottom - rt2.top;

	if ( sizeX <= (rt1W + rt2W) &&
		 sizeY <= (rt1H + rt2H))
	{
		return true;
	}
	return false;
}

bool CollisionComponent::IsAABBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM)
{
    vec2 objScale = _objM.GetScale();
    vec2 objLocation = _objM.GetLocation();
    vec2 targetScale = _targetM.GetScale();
    vec2 targetLocation = _targetM.GetLocation();

    vec2 objToTarget = glm::abs(targetLocation - objLocation);
    vec2 minimumDistance = { objScale.x / 2 + targetScale.x / 2, objScale.y / 2 + targetScale.y / 2 };
    minimumDistance = glm::abs(minimumDistance);

    if (objToTarget.x <= minimumDistance.x && objToTarget.y <= minimumDistance.y)
        return true;
    else
        return false;
}

bool CollisionComponent::IsOBBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM)
{ 
    vec2 objScale     = _objM.GetScale();
    vec2 objLocation  = _objM.GetLocation();
    float objAngle    = _objM.GetAngle();
    vec2 targetScale  = _targetM.GetScale();
    vec2 targetLocation = _targetM.GetLocation();
    float targetAngle = _targetM.GetAngle();

    vec2 objXVec = MyTransformer2D::RotateAsAngle({ objScale.x / 2, 0.f }, objAngle);
    vec2 objYVec = MyTransformer2D::RotateAsAngle({ 0.f, objScale.y / 2 }, objAngle);
    vec2 targetXVec = MyTransformer2D::RotateAsAngle({ targetScale.x / 2, 0.f }, targetAngle);
    vec2 targetYVec = MyTransformer2D::RotateAsAngle({ 0.f, targetScale.y / 2 }, targetAngle);
    
    vec2 distance = targetLocation - objLocation;

    float distance1 = glm::abs(glm::dot(objXVec, distance)) / glm::length(objXVec);
    float distance2 = glm::abs(glm::dot(objYVec, distance)) / glm::length(objYVec);
    float distance3 = glm::abs(glm::dot(targetXVec, distance)) / glm::length(targetXVec);
    float distance4 = glm::abs(glm::dot(targetYVec, distance)) / glm::length(targetYVec);

    float targetProj1X = glm::abs(glm::dot(objXVec, targetXVec)) / glm::length(objXVec);
    float targetProj1Y = glm::abs(glm::dot(objXVec, targetYVec)) / glm::length(objXVec);
    float objProj1 = glm::length(objXVec);

    float targetProj2X = glm::abs(glm::dot(objYVec, targetXVec)) / glm::length(objYVec);
    float targetProj2Y = glm::abs(glm::dot(objYVec, targetYVec)) / glm::length(objYVec);
    float objProj2 = glm::length(objYVec);

    float objProj1X = glm::abs(glm::dot(targetXVec, objXVec)) / glm::length(targetXVec);
    float objProj1Y = glm::abs(glm::dot(targetXVec, objYVec)) / glm::length(targetXVec);
    float targetProj3 = glm::length(targetXVec);

    float objProj2X = glm::abs(glm::dot(targetYVec, objXVec)) / glm::length(targetYVec);
    float objProj2Y = glm::abs(glm::dot(targetYVec, objYVec)) / glm::length(targetYVec);
    float targetProj4 = glm::length(targetYVec);

    if (targetProj1X + targetProj1Y + objProj1 < distance1)
        return false;
            
    if (targetProj2X + targetProj2Y + objProj2 < distance2)
        return false;

    if (objProj1X + objProj1Y + targetProj3 < distance3)
        return false; 

    if (objProj2X + objProj2Y + targetProj4 < distance4)
        return false;

    return true;
}
