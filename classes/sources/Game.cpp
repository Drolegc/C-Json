#include "../headers/Game.h"

Game::Game(std::string name){
    this->game_name = name;
}

std::string Game::getName(){
    return this->game_name;
}

void Game::setName(std::string new_name){
    this->game_name = new_name;
}

Game::~Game(){}