#include<iostream>
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/interfaces/ICollection.h"

/* user */

class User:public ICollectible{

    private:
    std::string nickname;
    std::string password;
    
    ICollection * colRecords;
    
    public:
    User(std::string nickname,std::string password);
    
    std::string getNickname();
    std::string getPassword();
    ICollection* getColRecord();

    void setNickname(std::string new_nick);
    void setPassword(std::string new_pass);
    void setRecord(ICollectible* r);
    void mostrarRecords();
    ~User();
};