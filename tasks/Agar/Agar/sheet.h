#pragma once

static const sf::Vector2u WINDOW_SIZE = { 1400, 800 };
static const std::string WINDOW_TITLE = "AGARIO";
static const auto WINDOW_STYLE = sf::Style::Close;
static const unsigned WINDOW_FRAME_LIMIT = 60;

static const float AGAR_RADIUS = 30;
static const sf::Vector2f AGAR_SIZE = { AGAR_RADIUS,  AGAR_RADIUS };
static const sf::Vector2f AGAR_INITIAL_POSITION = 0.5f * (sf::Vector2f(WINDOW_SIZE) - AGAR_SIZE);

static const auto STEP = 6.f;

static const sf::Color GREEN = { 0, 127, 0 };
static const sf::Color WHITE = { 255, 255, 255 };
