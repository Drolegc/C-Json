#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "controller/Controller.h"

int main(){

    Controller* controller = Controller::getInstance();

    std::cout<<"Welcome!"<<std::endl;



    std::cout<<"Adding a game: Rampage";

    controller->addGame("Rampage");

    std::cout<<std::endl;
    std::cout<<"Adding a record from the preloaded user"<<std::endl;
    controller->setRecord("Rampage");

    std::cout<<std::endl;
    std::cout<<"Showing all records"<<std::endl;
    controller->showAllRecords();

    std::cout<<"Creating file -> Objects to JSON"<<std::endl;

    controller->ObjectsToJSON(controller->getSession());


    return 0;
}