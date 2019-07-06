#include <iostream>
#include <fstream>
#include <stdexcept>
#include <jsoncpp/json/json.h>
#include "controller/Controller.h"

int main()
{

    Controller *controller = Controller::getInstance();

    std::cout << "Welcome!" << std::endl;

    controller->JSONToObjects();

    while (true)
    {
        
        int command;
        std::cout << "1 SignUp" << std::endl;
        std::cout << "2 LogIn" << std::endl;
        std::cout << "3 addGame" << std::endl;
        std::cout << "4 addRecord" << std::endl;
        std::cout << "5 showRecords"<<std::endl;
        std::cout << "0 out / save all to Json" << std::endl;
        try
        {
            std::cin>>command;
            switch (command)
            {
            case 1:
            {

                std::string nickname;
                std::string password;
                std::cout << "Nickname: ";
                std::cin >> nickname;
                std::cout << "Password :";
                std::cin >> password;
                controller->SignUp(nickname,password);
                std::cout<<"User created"<<std::endl;
            }
            break;
            case 2:
            {
                std::string nickname;
                std::string password;
                std::cout << "Nickname: ";
                std::cin >> nickname;
                std::cout << "Password :";
                std::cin >> password;
                controller->LogIn(nickname,password);
                std::cout << "User logged" << std::endl;
            }
                break;
            case 3:
            {
                std::string game_name;
                std::cout<<"Names game: ";
                std::cin>>game_name;
                controller->addGame(game_name);
                std::cout<<"Game add it"<<std::endl;
            }
                break;
            case 4:{
                std::string game_name;
                int points;
                std::cout<<"Record in which game? ";
                std::cin>>game_name;
                std::cout<<"How many points";
                std::cin>>points;
                controller->setRecord(points,game_name);
                std::cout<<"Record setted"<<std::endl;}
                break;
            case 5:{
                controller->showAllRecords();
            }
            break;
            case 0:{
                controller->ObjectsToJSON();
            }
            }
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        system("clear");
    }
    
    

    return 0;
}