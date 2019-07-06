#include "../headers/User.h"
#include "../headers/Record.h"
#include "../../ICollection/collections/List.h"

User::User(std::string nickname,std::string password){
    this->nickname = nickname;
    this->password = password;
    this->colRecords = new List();
}

std::string User::getNickname(){
    return this->nickname;
}

std::string User::getPassword(){
    return this->password;
}

ICollection* User::getColRecord(){
    return this->colRecords;
}

void User::setNickname(std::string new_nick){
    this->nickname = new_nick;
}

void User::setPassword(std::string new_pass){
    this->password = new_pass;
}

void User::mostrarRecords(){
    IIterator* it = colRecords->getIterator();
    std::cout<<this->nickname<<" records:"<<std::endl;
    while(it->hasCurrent()){
        Record* r = dynamic_cast<Record*>(it->getCurrent());
        std::cout<<"*"<<r->getPoints()<<std::endl<<r->getGame()<<std::endl;
        it->next();
    }
}

User::~User(){

}