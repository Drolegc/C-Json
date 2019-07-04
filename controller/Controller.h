#include <iostream>
#include "../ICollection/interfaces/ICollectible.h"
#include "../ICollection/interfaces/ICollection.h"
#include "../ICollection/interfaces/IDictionary.h"
#include "../classes/headers/User.h"

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
    void SignUp();
    void setRecord(std::string names_game);
    void showAllRecords();
};