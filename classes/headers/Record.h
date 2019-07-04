
#include <iostream>
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/interfaces/ICollection.h"
#include "Game.h"

class Record:public ICollectible{

    private:
    int points;
    Game* game;

    public:
    Record(int points,Game* g);

    int getPoints();
    std::string getGame();

    void setPoints(int new_points);

    ~Record();

};