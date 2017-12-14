#include "stdafx.h"

#include "GameScene.h"

namespace
{

static const unsigned FONT_SIZE = 30;

static const float ROW_MARGIN = 10;

static const sf::Color BLACK = sf::Color::Black;

sf::Color TakeJsonColor(nlohmann::basic_json<> colorObj)
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

ÑGameScene::~ÑGameScene()
{
	m_audioPlayer.Stop();
}

ÑGameScene::ÑGameScene(sf::RenderWindow & window, CAssets assets, SocketMaster & socketMaster)
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
	m_audioPlayer.SetVolume(0);
	const sf::VideoMode videoMode(WINDOW_SIZE.x, WINDOW_SIZE.y);
	sf::ContextSettings contextSettings;
	contextSettings.antialiasingLevel = ANTIALIASING_LEVEL;
	m_window.create(videoMode, WINDOW_TITLE, WINDOW_STYLE, contextSettings);
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(WINDOW_FRAME_LIMIT);
	m_tableElement.setFont(m_assets.ARIAL_FONT);
	m_tableElement.setCharacterSize(FONT_SIZE);
	m_tableElement.setFillColor(BLACK);
	const auto icon = m_assets.WINDOW_ICON;
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	m_view.reset(sf::FloatRect(0, 0, float(WINDOW_SIZE.x), float(WINDOW_SIZE.y)));
}

std::string ÑGameScene::GetId(const std::string & path) const
{
	return json::parse(path)["id_player"];
}

SceneInfo ÑGameScene::Advance(float dt)
{
	m_nextSceneType = SceneType::ÑGameScene;
	CheckEvents();
	Update(dt);
	Render();
	m_window.display();

	return SceneInfo(m_nextSceneType);
}

void ÑGameScene::CheckEvents()
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

void ÑGameScene::CheckKeyboardEvents(const sf::Event & event)
{
	CheckKeyPressed(event);
}

void ÑGameScene::CheckKeyPressed(const sf::Event & event)
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

void ÑGameScene::ProcessUpdateData(const std::string & path)
{
	const auto data = json::parse(path);
	const auto foodStringLength = data[KEY_FOOD].size();
	const auto food = data[KEY_FOOD];
	const auto enemiesStringLength = data[KEY_ENEMIES].size();
	const auto enemies = data[KEY_ENEMIES];
	const auto players = data[KEY_PLAYERS];
	const auto playerStringLength = data[KEY_PLAYERS].size();
	const auto table = data["t"];

	SetElementsForTable(table);
	DrawPlayers(m_agarics, m_agar, players, m_heroId, m_agarView); 
	DrawFood(m_meal, foodStringLength, food);
	DrawEnemies(m_enemies, enemiesStringLength, enemies);
}

void ÑGameScene::SetTableTextPosition(const sf::Vector2f & center, float rowTop)
{
	const int xCoord = WINDOW_SIZE.x / 2;
	const int yCoord = -(WINDOW_SIZE.y / 2);
	m_tableElement.setPosition(center + sf::Vector2f(xCoord - TABLE_SIZE.x + ROW_MARGIN, yCoord + rowTop));
}

void ÑGameScene::SetElementsForTable(const nlohmann::basic_json<> obj)
{
	for (auto & player : obj)
	{
		std::string newStr = player["nickname"];
		m_tableNicknames.push_back(newStr);
	}
}

const sf::Vector2f ÑGameScene::SetPosition(const sf::Vector2f & center)
{
	const int xCoord = WINDOW_SIZE.x / 2;
	const int yCoord = -(WINDOW_SIZE.y / 2);
	return (center + sf::Vector2f(xCoord, yCoord));
}

void ÑGameScene::DrawPlayers(std::vector<CAgar> & agarics, CAgar & agar, const nlohmann::basic_json<> obj, std::string & id, CAgar & agarView)
{
	unsigned index = 0;
	for (auto & player : obj)
	{
		if (obj.size() > agarics.size())
		{
			agar.SetColor(TakeJsonColor(player["color"]));
			agar.SetPosition(sf::Vector2f((float(player["x"]) *  float(FIELD_SIZE.x)), (float(player["y"]) *  float(FIELD_SIZE.y))));
			agar.SetRadius(float(player["radius"]) * FIELD_COEF);
			agarics.push_back(agar);
			if (player["id_player"] == id)
			{
				agarView = agar;
			}
		}
		else
		{
			agarics[index].SetColor(TakeJsonColor(player["color"]));
			agarics[index].SetPosition(sf::Vector2f((float(player["x"]) *  float(FIELD_SIZE.x)), (float(player["y"]) *  float(FIELD_SIZE.y))));
			agarics[index].SetRadius(float(player["radius"]) * FIELD_COEF);
			if (player["id_player"] == id)
			{
				agarView = agarics[index];
			}
		}
		++index;
	}
}

void ÑGameScene::DrawEnemies(std::array<CEnemy, NUMBER_ENEMIES> & enemy, size_t arrSize, const nlohmann::basic_json<> obj)
{
	for (size_t j = 0; j < arrSize; ++j)
	{
		auto colorEnemy = obj[j]["color"];
		enemy[j].SetColor(TakeJsonColor(colorEnemy));
		enemy[j].SetPosition(sf::Vector2f(float(obj[j]["x"]) * FIELD_SIZE.x, float(obj[j]["y"]) * FIELD_SIZE.y));
		enemy[j].SetRadius(float(obj[j]["radius"]) * FIELD_COEF);
	}
}

void ÑGameScene::DrawFood(std::array<CMeal, NUMBER_MEAL> & meal, size_t arrSize, const nlohmann::basic_json<> obj)
{
	for (size_t j = 0; j < arrSize; ++j)
	{
		auto colorEnemy = obj[j]["color"];
		meal[j].SetColor(TakeJsonColor(colorEnemy));
		meal[j].SetPosition(sf::Vector2f(float(obj[j]["x"]) * FIELD_SIZE.x, float(obj[j]["y"]) * FIELD_SIZE.y));
		meal[j].SetRadius(float(obj[j]["radius"]) * FIELD_COEF);
	}
}

void ÑGameScene::CheckMouseEvents(const sf::Event & event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		m_mousePosition = { 
			event.mouseMove.x,
			event.mouseMove.y
		};
	}
}

void ÑGameScene::Update(float dt)
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
	for (size_t j = 0; j < m_tableNicknames.size(); ++j)
	{
		m_tableElement.setString(m_tableNicknames[j]);
		SetTableTextPosition(m_view.getCenter(), ROW_MARGIN * j);
		m_window.draw(m_tableElement);
	}
}

void ÑGameScene::Render()
{
	m_window.clear(PURPLE);

	for (const auto & agar : m_agarics)
	{
		agar.Draw(m_window);
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
	m_tableBackground.Draw(m_window);
	m_window.draw(m_tableElement);
}
