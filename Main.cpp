#include <iostream>
#include "controller/Controller.h"

int main(){

    Controller* controller = Controller::getInstance();
    std::cout<<"Welcome!";
    std::cout<<"Adding a game: Rampage";

    controller->addGame("Rampage");

    std::cout<<std::endl;
    std::cout<<"Adding a record from teh preload user"<<std::endl;
    controller->setRecord("Rampage");

    std::cout<<std::endl;
    std::cout<<"Showing all records"<<std::endl;
    controller->showAllRecords();


    return 0;
}