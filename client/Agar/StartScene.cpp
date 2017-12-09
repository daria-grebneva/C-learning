#include "StartScene.h"

namespace
{

static const auto START_TEXT = "START GAME";

static const sf::Vector2f START_TEXT_POSITION((WINDOW_SIZE.x / 2 - PAUSE_TEXT_SIZE.x), (WINDOW_SIZE.y / 2 - PAUSE_TEXT_SIZE.y));
static const std::string DEFALUT_INPUT_STRING = "Enter Your Nickname";
static const sf::Vector2f TEXT_POSITION = { 510, 352 };
static const sf::Vector2f INFO_TEXT_POSITION = { 10, 750 };
static const std::string INFO_TEXT = "Wait for connection with server...";
static const unsigned BACKSPACE = 8;
static const unsigned CTRL = 13;
static const unsigned ENTER = 10;
static const unsigned NUMBER_OF_SYMBOLS = 18;
static const unsigned ASCII_MAX_SYMBOLS_NUMBER = 128;

}

CStartScene::CStartScene(sf::RenderWindow & window, CAssets & assets, SocketMaster & socketMaster)
	:m_window(window)
	, m_assets(assets)
	, m_socket(socketMaster)
{
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
	nickname = DEFALUT_INPUT_STRING;

	m_text.setFont(m_assets.ARIAL_FONT);
	m_text.setString(nickname);
	m_text.setPosition(TEXT_POSITION);
	m_text.setCharacterSize(30);
	m_text.setFillColor(sf::Color::Black);

	m_information_text.setFont(m_assets.ARIAL_FONT);
	m_information_text.setString(INFO_TEXT);
	m_information_text.setPosition(INFO_TEXT_POSITION);
	m_information_text.setCharacterSize(35);
	m_information_text.setStyle(2);
	m_information_text.setFillColor(sf::Color::Black);
}

SceneInfo CStartScene::Advance(float dt, bool isConnected)
{
	m_nextSceneType = SceneType::CStartScene;
	CheckEvents(isConnected);
	Update(dt);
	m_window.setView(m_view);
	Render();
	DrawConnectedInfo(isConnected);
	m_window.display();

	return SceneInfo(m_nextSceneType);
}

void CStartScene::CheckInputText(const sf::Event & event)
{
	if (event.type == sf::Event::TextEntered)
	{
		const auto codeKey = event.text.unicode;
		if (codeKey < ASCII_MAX_SYMBOLS_NUMBER)
		{
			if (codeKey == int(sf::Keyboard::Return))
			{
				if (!nickname.empty() && nickname != DEFALUT_INPUT_STRING)
				{
					nickname.pop_back();
				}
				else
				{
					nickname = "";
				}
			}
			else if (codeKey == BACKSPACE)
			{
				if (!nickname.empty() && nickname != DEFALUT_INPUT_STRING)
				{
					nickname.pop_back();
				}
				else
				{
					nickname = "";
				}
			}
			else if ((codeKey != CTRL) && (codeKey != ENTER))
			{
				if (nickname == DEFALUT_INPUT_STRING)
				{
					nickname = "";
				}
				if (nickname.size() < NUMBER_OF_SYMBOLS)
				{
					nickname += static_cast<char>(codeKey);
				}
			}
			m_text.setString(nickname);
		}
	}
}

void CStartScene::DrawConnectedInfo(bool isConnected)
{
	if (!isConnected)
	{
		m_window.draw(m_information_text);
	}
}

bool CStartScene::IsNicknameStringEmpty() const
{
	return (!nickname.empty() && nickname != DEFALUT_INPUT_STRING);
}

void CStartScene::CheckEvents(bool isConnected)
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		CheckInputText(event);
		CheckKeyboardEvents(event, isConnected);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void CStartScene::CheckKeyboardEvents(const sf::Event & event, bool isConnected)
{
	CheckKeyPressed(event, isConnected);
}

void CStartScene::CheckKeyPressed(const sf::Event & event, bool isConnected)
{
	if ((event.type == sf::Event::KeyPressed) && isConnected && IsNicknameStringEmpty())
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Return:
			m_nextSceneType = SceneType::ÑGameScene;
			m_socket.Emit(KEY_NICKNAME, nickname);
		default:
			break;
		}
	}
}

void CStartScene::Update(float dt)
{
	(void)&dt;
}

void CStartScene::Render()
{
	m_window.clear(sf::Color::White);
	m_background.setTexture(m_assets.START_BACKGROUND);
	m_window.draw(m_background);
	m_window.draw(m_text);
}
