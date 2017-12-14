#pragma once

static const sf::Vector2u WINDOW_SIZE = { 1400, 800 };
static const sf::Vector2i FIELD_SIZE = { 1700, 1200 };
static const sf::Vector2f TABLE_SIZE = { 250, 300 };
static const float FIELD_COEF = 3500;
static const std::string WINDOW_TITLE = "AGARIO";
static const auto WINDOW_STYLE = sf::Style::Close;
static const unsigned WINDOW_FRAME_LIMIT = 60;
static const std::string ICON_IMAGE_PATH = "res/images/icon.png";
static const std::string BACKGROUND_PATH = "res/images/screen_saver_5.png";
static const std::string START_BACKGROUND_PATH = "res/images/start_screen.png";
static const std::string FONTS_PATH = "res/fonts/arial.ttf";
static const std::string AUDIO_PATH = "res/sounds/";
static unsigned ANTIALIASING_LEVEL = 8; 

static const sf::Vector2f PAUSE_TEXT_SIZE(250, 100);

static const sf::Color PURPLE = { 245, 235, 245 };
static const sf::Color BLUE = { 8, 141,	165 };

static const unsigned NUMBER_ENEMIES = 6;  
static const unsigned NUMBER_MEAL = 40; 

static const auto KEY_MOVEMENT = "m";
static const auto KEY_NEW_PLAYER = "n";
static const auto KEY_NICKNAME = "a";
static const auto KEY_UPDATE_DATA = "u";
static const auto KEY_PLAYERS = "p";
static const auto KEY_FOOD = "f";
static const auto KEY_ENEMIES = "e";
static const auto KEY_PLAYER_CREATED = "c";

enum class SceneType
{
	PauseScene = 0,
	CStartScene,
	ÑGameScene,
};

struct SceneInfo
{
public:
	SceneInfo() = delete;
	SceneInfo(SceneType type)
		:nextSceneType(type)
	{}

	SceneType nextSceneType;
};
