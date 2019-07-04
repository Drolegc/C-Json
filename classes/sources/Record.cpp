#include "../headers/Record.h"

Record::Record(int points,Game* g){
    this->points = points;
    this->game = g;
}

int Record::getPoints(){
    return this->points;
}

std::string Record::getGame(){
    return game->getName();
}

void Record::setPoints(int new_points){
    this->points = new_points;
}

Record::~Record(){}
