#include<iostream>
#include "../../ICollection/interfaces/ICollectible.h"


class Game:public ICollectible{

    private:
    std::string game_name;
    public:

    Game(std::string name);
    std::string getName();
    void setName(std::string new_name);
    ~Game();
};