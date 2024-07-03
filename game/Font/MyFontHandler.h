#pragma once
#include "MyWriterFont.h"
#include "ResourceHandler.h"

namespace MyProject
{
	class MyFontHandler : public ResourceHandler<MyWriterFont, FONT_KEY>
	{
	private:
		std::vector<wstringV> externalFontNames;

	public:
		~MyFontHandler();

		bool CreateFontResource(const FONT_KEY _key, const FontDesc& _desc);
		void DrawTextAsKey(FONT_KEY _key, wstringV _msg, RECT_F _rect, COLOR_F _color);
		bool LoadExternalFont(const wstringV _fontPath);
		void LoadExternalFontsAsFolder(const wstringV _fontFolder);
		
#ifdef _DEBUG
		void DrawTextForDebugging(const wchar_t* format, ...);
#endif
	};
}
