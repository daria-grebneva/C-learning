#pragma once

struct CAssets
{
public:
	CAssets();
	~CAssets();

	void AddImage(sf::Image & image, const std::string & path);
	void AddRepeatedTexture(sf::Texture & texture, const std::string & path);
	void AddTexture(sf::Texture & texture, const std::string & path);
	void AddFont(sf::Font & font, const std::string & path);

	sf::Image WINDOW_ICON;
	sf::Texture BACKGROUND;

	sf::Texture BACKGROUND_TEXTURE;
	sf::Texture BUTTON_ACTIVE_TEXTURE;
	sf::Texture BUTTON_INACTIVE_TEXTURE;

	sf::Font ARIAL_FONT;


private:
};
