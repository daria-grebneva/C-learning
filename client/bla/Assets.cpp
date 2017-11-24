#include "stdafx.h"

#include "Assets.h"
#include "sheet.h"

CAssets::CAssets()
{
	AddImage(WINDOW_ICON, "res/images/icon.png");
}

CAssets::~CAssets()
{

}

void CAssets::AddImage(sf::Image & image, const std::string & path)
{
	if (!image.loadFromFile(path))
	{
		MessageBoxA(nullptr, std::string("File " + path + " not founded").c_str(), "Error", MB_ICONERROR | MB_OK);
		_exit(-1);
	}
}
