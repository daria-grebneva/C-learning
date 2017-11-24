#pragma once

static const sf::Vector2u WINDOW_SIZE = { 1400, 800 };
static const sf::Vector2i FIELD_SIZE = { 1700, 1200 };
static const float FIELD_COEF = 3500;
static const std::string WINDOW_TITLE = "AGARIO";
static const auto WINDOW_STYLE = sf::Style::Close;
static const unsigned WINDOW_FRAME_LIMIT = 60;

static const sf::Color PURPLE = { 245, 235, 245 };

static const unsigned NUMBER_ENEMIES = 6;  

static const unsigned NUMBER_MEAL = 40; 

static const auto KEY_MOVEMENT = "m";
static const auto KEY_NEW_PLAYER = "n";
static const auto KEY_UPDATE_DATA = "u";
static const auto KEY_PLAYERS = "p";
static const auto KEY_FOOD = "f";
static const auto KEY_ENEMIES = "e";
