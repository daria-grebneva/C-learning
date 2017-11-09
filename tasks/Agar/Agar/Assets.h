#pragma once
struct CAssets
{
public:
	CAssets();
	~CAssets();

	void AddImage(sf::Image & image, const std::string & path);

	sf::Image WINDOW_ICON;

private:
};
