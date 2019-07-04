#include "Controller.h"
#include "../ICollection/collections/List.h"
#include "../ICollection/collections/OrderedDictionary.h"
#include "../ICollection/StringKey.h"
//#include "../classes/headers/Game.h"
#include "../classes/headers/Record.h"

Controller* Controller::instance = 0;

Controller::Controller(){
    this->dicGames = new OrderedDictionary();
    this->dicUsers = new OrderedDictionary();
    this->session = new User("Apolo","1234");
    SignUp();
}

Controller* Controller::getInstance(){
    if(instance == NULL){
        instance = new Controller();
    }
    return instance;
}

void Controller::LogIn(std::string nick, std::string pass){
    StringKey* k = new StringKey(nick);
    if(dicUsers->member(k)){
        session = dynamic_cast<User*>(dicUsers->find(k));
        std::cout<<session->getNickname()<<" log in"<<std::endl;
    }else{
        std::cout<<"User doesnt exist"<<std::endl;
    }
}

void Controller::addGame(std::string game){
    StringKey* k = new StringKey(game);
    Game* g = new Game(game);
    dicGames->add(k,g);
}

void Controller::SignUp(){
    StringKey* k = new StringKey(session->getNickname());
    dicUsers->add(k,session);
}

void Controller::setRecord(std::string name_game){
    
    ICollection* colRecord = session->getColRecord();
    StringKey* k = new StringKey(name_game);
    Game* g = dynamic_cast<Game*>(dicGames->find(k));
    Record* new_record = new Record(12,g);
    colRecord->add(new_record);
    std::cout<<"Add it to teh records of the user"<<std::endl;

}

void Controller::showAllRecords(){
    IIterator* it = dicUsers->getIterator();
    while(it->hasCurrent()){
        User* user = dynamic_cast<User*>(it->getCurrent());
        user->mostrarRecords();
        it->next();
    }
}

