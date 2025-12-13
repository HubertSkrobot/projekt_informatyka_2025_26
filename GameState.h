#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "klocek.h"

enum class GameState { Menu, Playing, Exiting }; //zdefiniowanie wszystkich stanow w ktorych moze byc gra

// Deklaracje funkcji do zapisu/odczytu stamu gry
void saveGame(const std::string& filename, const Ball& ball, const Paddle& paddle, const std::vector<Brick>& bricks, int score);
bool loadGame(const std::string& filename, Ball& ball, Paddle& paddle, std::vector<Brick>& bricks, int& score, sf::Vector2f brickSize);
