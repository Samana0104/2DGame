#pragma once
#include "Singleton.h"
#include "MyActor.h"
#include "MyTileManager.h"

namespace MyProject
{
	class MyObjectManager : public Singleton<MyObjectManager>
	{
	private:
		std::map<OBJECT_ID, std::shared_ptr<MyObject>> mUILists; // ���Ŀ� ��� ����?
		std::map<OBJECT_ID, std::shared_ptr<MyActor>>  mObjLists;
		
		std::queue<OBJECT_ID> mDeleteQueue;

		MyTileManager* mTileManager = nullptr; // Ÿ�� �Ŵ��� ���� �ȵθ� �ʹ� ���� ���� �˻� ��
		OBJECT_ID registerObjID = 0;
	private:
		friend class Singleton<MyObjectManager>;
		MyObjectManager() = default;

	public:
		void AddObject(std::shared_ptr<MyActor> _obj);
		void SetTileManager(MyTileManager* _tileManager);

		void DeleteObject(OBJECT_ID _objID);
		void ClearObject();

		void Update(const float _deltaTime);
		void Render();
	};
}

