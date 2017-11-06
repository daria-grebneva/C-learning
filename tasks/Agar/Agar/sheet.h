#pragma once

static const sf::Vector2u WINDOW_SIZE = { 1400, 800 };
static const sf::Vector2i FIELD_SIZE = { 1700, 1200 };
static const std::string WINDOW_TITLE = "AGARIO";
static const auto WINDOW_STYLE = sf::Style::Close;
static const unsigned WINDOW_FRAME_LIMIT = 60;
static const unsigned CONVERGENCE_RADIUS = 50;
static const float LIMIT_RADIUS = 150;

static const float AGAR_RADIUS = 30;
static const sf::Vector2f AGAR_SIZE = { AGAR_RADIUS,  AGAR_RADIUS };
static const sf::Vector2f AGAR_INITIAL_POSITION = 0.5f * (sf::Vector2f(WINDOW_SIZE) - AGAR_SIZE);

static const sf::Color PURPLE = { 245, 235, 245 };

static const float ENEMY_RADIUS = 25;
static const sf::Vector2f ENEMY_SIZE = { ENEMY_RADIUS,  ENEMY_RADIUS };
static const sf::Vector2f ENEMY_INITIAL_POSITION = { WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y + AGAR_INITIAL_POSITION.y };
static const unsigned NUMBER_ENEMIES = 8;  

static const float MEAL_RADIUS = 10;
static const sf::Vector2f MEAL_SIZE = { MEAL_RADIUS,  MEAL_RADIUS };
static const sf::Vector2f MEAL_INITIAL_POSITION = { WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y + AGAR_INITIAL_POSITION.y };
static const unsigned NUMBER_MEAL = 50; 
