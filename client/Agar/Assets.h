#pragma once

struct CAssets
{
public:
	CAssets();
	~CAssets();

	void AddImage(sf::Image & image, const std::string & path);
	void AddRepeatedTexture(sf::Texture & texture, const std::string & path);
	void AddTexture(sf::Texture & texture, const std::string & path);

	sf::Image WINDOW_ICON;
	sf::Texture BACKGROUND;

private:
};
