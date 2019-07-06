#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

#include "../ICollection/interfaces/ICollectible.h"
#include "../ICollection/interfaces/ICollection.h"
#include "../ICollection/interfaces/IDictionary.h"
#include "../classes/headers/User.h"
//#include "../classes/headers/Game.h"

class Controller{
    
    private:
    IDictionary* dicUsers;
    IDictionary* dicGames;
    User* session;
    
    static Controller* instance;
    Controller();
    public:

    
    static Controller* getInstance();

    void LogIn(std::string nick,std::string pass);
    void addGame(std::string game);
    void SignUp(std::string name,std::string pass);
    void setRecord(int points,std::string names_game);
    void showAllRecords();
    /* JSON */
    void ObjectsToJSON();
    void JSONToObjects();

    User* getSession();
};