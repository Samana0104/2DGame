#pragma once
#include "MyCoreAPI.h"
#include "MyTile.h"

namespace MyProject
{
	class MyTileManager
	{
	private:
		std::map<WCHAR, std::shared_ptr<MyTile>> mTiles;
		std::vector<std::unique_ptr<MyTile>> mTileMap;
		std::vector<std::shared_ptr<MyTile>> mCollisions;
		std::shared_ptr<MyTile> mBackground;

		int		mRows;
		int		mColumns;
		vec2	mPosition;
		vec2	mSize;
		vec2	mTileSize;
		
		bool    mIsScriptLoaded;

	public:
		MyTileManager();

		bool LoadScript(const wstringV _filePath);
		void SetPosition(const vec2 _pos);
		void SetSize(const vec2 _size);
		void Render();
	};
}

