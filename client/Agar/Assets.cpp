#include "stdafx.h"

#include "Assets.h"
#include "sheet.h"

CAssets::CAssets()
{
	AddImage(WINDOW_ICON, ICON_IMAGE_PATH);
	AddRepeatedTexture(BACKGROUND, BACKGROUND_PATH);
	
	AddImage(WINDOW_ICON, "res/images/icon.png");
	AddTexture(BUTTON_ACTIVE_TEXTURE, "res/images/button_active.png");
	AddTexture(BUTTON_INACTIVE_TEXTURE, "res/images/button_inactive.png");
	AddFont(ARIAL_FONT, "res/fonts/arial.ttf");
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

void CAssets::AddRepeatedTexture(sf::Texture & texture, const std::string & path)
{
	AddTexture(texture, path);
	texture.setRepeated(true);
}

void CAssets::AddTexture(sf::Texture & texture, const std::string & path)
{
	if (!texture.loadFromFile(path))
	{
		MessageBoxA(nullptr, std::string("File " + path + " not founded").c_str(), "Error", MB_ICONERROR | MB_OK);
		_exit(-1);
	}

	texture.setSmooth(true);
	texture.setRepeated(false);
}

void CAssets::AddFont(sf::Font & font, const std::string & path)
{
	if (!font.loadFromFile(path))
	{
		MessageBoxA(nullptr, std::string("File " + path + " not founded").c_str(), "Error", MB_ICONERROR | MB_OK);
		_exit(-1);
	}
}
