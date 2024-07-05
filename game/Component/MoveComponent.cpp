#include "pch.h"
#include "MoveComponent.h"
using namespace MyProject;

MoveComponent::MoveComponent(MyTransformer2D & _transform) :
    mTransform(_transform)
{
}

void MoveComponent::SetSpeed(const vec2 _speed)
{
    mSpeed = _speed;
}

void MoveComponent::SetAcceleration(const vec2 _acceleration)
{
    mAcceleration = _acceleration;
}

void MoveComponent::AddSpeed(const vec2 _speed)
{
    mSpeed += _speed;
}

void MoveComponent::AddAcceleration(const vec2 _acceleration)
{
    mAcceleration += _acceleration;
}

void MoveComponent::Break(const vec2 _accleration)
{
    if (mSpeed.x <= TOLERANCE && mSpeed.y <= TOLERANCE)
        return;

    if (mSpeed.x > 0.f)
    {
		mIsXposBreaking = true;
    }
    else if(mSpeed.x < 0.f)
    {
		mIsXposBreaking = false;
    }

}

vec2 MoveComponent::GetSpeed() const
{
    return mSpeed;
}

vec2 MoveComponent::GetAcceleration() const
{
    return mAcceleration;
}

void MoveComponent::Update(float _deltaTime)
{
    mSpeed += mAcceleration * _deltaTime;
    mTransform->AddLocation(mSpeed * _deltaTime);
}
