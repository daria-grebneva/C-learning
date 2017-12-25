#include "stdafx.h"

#include "GameScene.h"

namespace
{

static const unsigned FONT_SIZE = 30;

static const float ROW_MARGIN = 40;

static const float MARGIN_LEFT = 10;

static const unsigned INFO_FONT_SIZE = 45;

static const unsigned INFO_FONT_STYLE = 2;

static const sf::Vector2f INFO_TEXT_MARGIN = { 670, 0 };

static const std::string INFO_TEXT = "You have lost connection with the server, please restart the game";

static const sf::Color BLACK = sf::Color::Black;

static const std::string KEY_ID = "i";

static const std::string KEY_RADIUS = "r";

static const std::string KEY_COLOR = "l";

static const std::string KEY_NICKNAME = "n";

static const std::string KEY_TABLE = "z";

sf::Color TakeJsonColor(const json & colorObj)
{
	const std::string color = colorObj.dump();
	return {
		uint8_t(std::stoi(color.substr(2, 2), nullptr, 16)),
		uint8_t(std::stoi(color.substr(4, 2), nullptr, 16)),
		uint8_t(std::stoi(color.substr(6, 2), nullptr, 16))
	};
}

}

using json = nlohmann::json;

CGameScene::~CGameScene()
{
	m_audioPlayer.Stop();
}

CGameScene::CGameScene(sf::RenderWindow & window, CAssets assets, SocketMaster & socketMaster)
	:m_socketMaster(socketMaster)
	,m_audioPlayer(AUDIO_PATH)
	,m_window(window)
	,m_tableBackground(window, assets)
{
	m_socketMaster.SetHandler(KEY_PLAYER_CREATED, [&](sio::event & e)
	{
		m_heroId = GetId(e.get_message()->get_string());
	});
	m_socketMaster.SetHandler(KEY_UPDATE_DATA, [&](sio::event & e)
	{
		ProcessUpdateData(e.get_message()->get_string());
	});
	m_audioPlayer.SetVolume(100);
	const sf::VideoMode videoMode(WINDOW_SIZE.x, WINDOW_SIZE.y);
	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = ANTIALIASING_LEVEL;
	m_window.create(videoMode, WINDOW_TITLE, WINDOW_STYLE, contextSettings);
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(WINDOW_FRAME_LIMIT);
	const auto icon = m_assets.WINDOW_ICON;
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
}

std::string CGameScene::GetId(const std::string & path) const
{
	return json::parse(path)[KEY_ID];
}

SceneInfo CGameScene::Advance(float dt, bool isConnected)
{
	m_nextSceneType = SceneType::СGameScene;
	CheckEvents();
	Update(dt);
	Render();
	DrawConnectedInfo(isConnected);
	m_window.display();

	return SceneInfo(m_nextSceneType);
}

void CGameScene::DrawConnectedInfo(bool isConnected) const
{
	if (!isConnected)
	{
		sf::Text informationText;
		informationText.setFont(m_assets.ARIAL_FONT);
		informationText.setString(INFO_TEXT);
		informationText.setPosition(m_view.getCenter() - INFO_TEXT_MARGIN);
		informationText.setCharacterSize(INFO_FONT_SIZE);
		informationText.setStyle(INFO_FONT_STYLE);
		informationText.setFillColor(BLACK);
		m_window.draw(informationText);
	}
}

void CGameScene::CheckEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		CheckKeyboardEvents(event);
		CheckMouseEvents(event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void CGameScene::CheckKeyboardEvents(const sf::Event & event)
{
	CheckKeyPressed(event);
}

void CGameScene::CheckKeyPressed(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Space:
			m_nextSceneType = SceneType::PauseScene;
		default:
			break;
		}
	}
}

void CGameScene::ProcessUpdateData(const std::string & path)
{
	const auto data = json::parse(path);
	const auto foodStringLength = data[KEY_FOOD].size();
	const auto food = data[KEY_FOOD];
	const auto enemiesStringLength = data[KEY_ENEMIES].size();
	const auto enemies = data[KEY_ENEMIES];
	const auto players = data[KEY_PLAYERS];
	const auto playerStringLength = data[KEY_PLAYERS].size();
	m_table = data[KEY_TABLE];

	UpdatePlayers(players);
	UpdateFood(foodStringLength, food);
	UpdateEnemies(enemiesStringLength, enemies);
	m_isDataInited = true;
}

void CGameScene::UpdateTable()
{
	for (auto & tableElem : m_allTableNicknames)
	{
		tableElem.setString("");
	}
	while (m_allTableNicknames.size() < m_table.size())
	{
		sf::Text temp;
		temp.setFont(m_assets.ARIAL_FONT);
		temp.setString("");
		temp.setCharacterSize(FONT_SIZE);
		temp.setStyle(INFO_FONT_STYLE);
		temp.setFillColor(BLACK);
		m_allTableNicknames.push_back(temp);
	}
	size_t j = 0;
	for (auto & data : m_table)
	{
		const auto nickname = data;
		if (j < 7)
		{
			if (!nickname.is_string())
			{
				return;
			}
			m_allTableNicknames[j].setString(nickname.get<std::string>());
			m_allTableNicknames[j].setPosition(SetTableTextPosition(m_view.getCenter(), ROW_MARGIN * j));
		}
		++j;
	}
}

const sf::Vector2f CGameScene::SetTableTextPosition(const sf::Vector2f & center, float rowTop)
{
	const int xCoord = WINDOW_SIZE.x / 2;
	const int yCoord = - (WINDOW_SIZE.y / 2);
	return (center + sf::Vector2f(xCoord - TABLE_SIZE.x + MARGIN_LEFT, yCoord + rowTop));
}

void CGameScene::UpdatePlayers(const json & obj)
{
	unsigned index = 0;
	for (auto & player : obj)
	{
		if (obj.size() > m_agarics.size())
		{
			float oldRadius = m_agar.GetRadius();
			float newRadius = float(player[KEY_RADIUS]) * FIELD_COEF;
			sf::Vector2f newPos = sf::Vector2f((float(player["x"]) *  float(FIELD_SIZE.x)), (float(player["y"]) *  float(FIELD_SIZE.y)));
			m_agar.SetColor(TakeJsonColor(player[KEY_COLOR]));
			m_agar.SetPosition(newPos + sf::Vector2f(oldRadius - newRadius, oldRadius - newRadius));
			m_agar.SetRadius(newRadius);
			m_agarics.push_back(m_agar);
			if (player[KEY_ID] == m_heroId)
			{
				m_agarView = m_agar;
			}
		}
		else
		{
			float oldRadius = m_agar.GetRadius();
			float newRadius = float(player[KEY_RADIUS]) * FIELD_COEF;
			sf::Vector2f newPos = sf::Vector2f((float(player["x"]) *  float(FIELD_SIZE.x)), (float(player["y"]) *  float(FIELD_SIZE.y)));
			m_agarics[index].SetColor(TakeJsonColor(player[KEY_COLOR]));
			m_agarics[index].SetPosition(newPos + sf::Vector2f(oldRadius - newRadius, oldRadius - newRadius));
			m_agarics[index].SetRadius(newRadius);
			if (player[KEY_ID] == m_heroId)
			{
				m_agarView = m_agarics[index];
			}
		}
		++index;
	}
}

void CGameScene::UpdateEnemies(size_t arrSize, const json & obj)
{
	for (size_t j = 0; j < arrSize; ++j)
	{
		float oldRadius = m_enemies[j].GetRadius();
		float newRadius = float(obj[j][KEY_RADIUS]) * FIELD_COEF;
		sf::Vector2f newPos = sf::Vector2f(float(obj[j]["x"]) * FIELD_SIZE.x, float(obj[j]["y"]) * FIELD_SIZE.y);
		auto colorEnemy = obj[j][KEY_COLOR];
		m_enemies[j].SetColor(TakeJsonColor(colorEnemy));
		m_enemies[j].SetPosition(newPos + sf::Vector2f(oldRadius - newRadius, oldRadius - newRadius));
		m_enemies[j].SetRadius(newRadius);
	}
}

void CGameScene::UpdateFood(size_t arrSize, const json & obj)
{
	for (size_t j = 0; j < arrSize; ++j)
	{
		auto colorEnemy = obj[j][KEY_COLOR];
		m_meal[j].SetColor(TakeJsonColor(colorEnemy));
		m_meal[j].SetPosition(sf::Vector2f(float(obj[j]["x"]) * FIELD_SIZE.x, float(obj[j]["y"]) * FIELD_SIZE.y));
		m_meal[j].SetRadius(float(obj[j][KEY_RADIUS]) * FIELD_COEF);
	}
}

void CGameScene::DrawTable() const
{
	m_tableBackground.Draw(m_window);
	{
		for (auto & tableElem : m_allTableNicknames)
		{
			m_window.draw(tableElem);
		}
	}
}

void CGameScene::CheckMouseEvents(const sf::Event & event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		m_mousePosition = {
			event.mouseMove.x,
			event.mouseMove.y
		};
	}
}

void CGameScene::Update(float dt)
{
	if (m_isDataInited)
	{
		(void)&dt;
		json playerInfo;
		sf::Vector2f fieldSize(WINDOW_SIZE);
		sf::Vector2f mousePos = m_agarView.GetPosition() - 0.5f * fieldSize + sf::Vector2f((float(m_mousePosition.x)), (float(m_mousePosition.y)));
		playerInfo["x"] = mousePos.x / float(FIELD_SIZE.x);
		playerInfo["y"] = mousePos.y / float(FIELD_SIZE.y);
		m_socketMaster.Emit(KEY_MOVEMENT, playerInfo.dump());
		m_view.setCenter(m_agarView.GetPosition() + m_agarView.GetRadius() * sf::Vector2f(1, 1));
		m_window.setView(m_view);
		m_tableBackground.SetPosition(m_view.getCenter());
		UpdateTable();
		m_audioPlayer.Update(dt);
	}
}

void CGameScene::Render() const
{
	m_window.clear(PURPLE);

	if (m_table.size() == m_agarics.size())
	{
		for (const auto & agar : m_agarics)
		{
			agar.Draw(m_window);
		}
	}

	for (const auto & meal : m_meal)
	{
		meal.Draw(m_window);
	}

	for (const auto & enemy : m_enemies)
	{
		enemy.Draw(m_window);
	}

	m_agarView.Draw(m_window);
	DrawTable();
}
