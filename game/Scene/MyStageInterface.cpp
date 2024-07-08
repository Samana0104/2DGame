#include "pch.h"
#include "MyStageInterface.h"
using namespace MyProject;

void MyStageInterface::Render()
{
	mObjManager.Render();
	if (isPause)
	{
		mPauseBackground.Render();
		for (int i = 0; i < 3; i++)
			mButtons[i].Render();
	}
}

void MyStageInterface::Release()
{
	mObjManager.ClearObject();
}
