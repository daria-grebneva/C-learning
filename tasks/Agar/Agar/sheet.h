#pragma once

static const sf::Vector2u WINDOW_SIZE = { 1400, 800 };
static const std::string WINDOW_TITLE = "AGARIO";
static const auto WINDOW_STYLE = sf::Style::Close;
static const unsigned WINDOW_FRAME_LIMIT = 60;

static const float AGAR_RADIUS = 30;
static const sf::Vector2f AGAR_SIZE = { AGAR_RADIUS,  AGAR_RADIUS };
static const sf::Vector2f AGAR_INITIAL_POSITION = 0.5f * (sf::Vector2f(WINDOW_SIZE) - AGAR_SIZE);

static const sf::Color GREEN = { 0, 127, 0 };
static const sf::Color WHITE = { 255, 255, 255 };
static const sf::Color VIOLET = { 102, 60, 124 };

static const float ENEMY_RADIUS = 30;
static const sf::Vector2f ENEMY_SIZE = { ENEMY_RADIUS,  ENEMY_RADIUS };
static const sf::Vector2f ENEMY_INITIAL_POSITION = { WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y + AGAR_INITIAL_POSITION.y };
static const unsigned NUMBER_ENEMIES = 20;  // = 2 * (WINDOW_SIZE.y / PLATE_SIZE.y);