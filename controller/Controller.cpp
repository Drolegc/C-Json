#include "Controller.h"
#include "../ICollection/collections/List.h"
#include "../ICollection/collections/OrderedDictionary.h"
#include "../ICollection/StringKey.h"
//#include "../classes/headers/Game.h"
#include "../classes/headers/Record.h"

Controller *Controller::instance = 0;

Controller::Controller()
{
    this->dicGames = new OrderedDictionary();
    this->dicUsers = new OrderedDictionary();
    this->session = new User("Apolo", "1234");
    SignUp();
}

Controller *Controller::getInstance()
{
    if (instance == NULL)
    {
        instance = new Controller();
    }
    return instance;
}

void Controller::LogIn(std::string nick, std::string pass)
{
    StringKey *k = new StringKey(nick);
    if (dicUsers->member(k))
    {
        session = dynamic_cast<User *>(dicUsers->find(k));
        std::cout << session->getNickname() << " log in" << std::endl;
    }
    else
    {
        std::cout << "User doesnt exist" << std::endl;
    }
}

void Controller::addGame(std::string game)
{
    StringKey *k = new StringKey(game);
    Game *g = new Game(game);
    dicGames->add(k, g);
}

void Controller::SignUp()
{
    StringKey *k = new StringKey(session->getNickname());
    dicUsers->add(k, session);
}

void Controller::setRecord(std::string name_game)
{

    ICollection *colRecord = session->getColRecord();
    StringKey *k = new StringKey(name_game);
    Game *g = dynamic_cast<Game *>(dicGames->find(k));
    Record *new_record = new Record(12, g);
    colRecord->add(new_record);
    std::cout << "Add it to teh records of the user" << std::endl;
}

void Controller::showAllRecords()
{
    IIterator *it = dicUsers->getIterator();
    while (it->hasCurrent())
    {
        User *user = dynamic_cast<User *>(it->getCurrent());
        user->mostrarRecords();
        it->next();
    }
}

User *Controller::getSession()
{
    return this->session;
}

void Controller::ObjectsToJSON(User *user)
{

    std::fstream read;
    std::ofstream write;
    read.open("testJSON.json", std::fstream::in);
    
    

    Json::Value JsonFile;
    Json::Reader reader;
    //bool ok_parse = reader.parse(read,JsonFile);

    if (read.is_open())
    {
        //Create a User JSON

        Json::Value userJson;
        //Insert data into User JSON

        userJson["Nickname"] = user->getNickname();
        userJson["Password"] = user->getPassword();
        //append a JSON object that is the record of the user
        //Get the collections of records and the iterator
        ICollection *records = user->getColRecord();
        IIterator *it = records->getIterator();

        //foreach record, append a Json value thats equals to the record
        while (it->hasCurrent())
        {
            Record *record = dynamic_cast<Record *>(it->getCurrent());
            Json::Value JsonRecord;
            JsonRecord["points"] = record->getPoints();
            JsonRecord["Game"] = record->getGame();
            //Once the JsonRecord its ready, we append it to userJson
            userJson["records"].append(JsonRecord);

            it->next();
        }

        //Json ready to upload
        //Here we need to parse to JsonFile and then delete all from the file
        bool ok_parse = reader.parse(read, JsonFile);

        if (ok_parse)
        {
            std::cout << "Parse ok"<<std::endl;
            write.open("testJSON.json", std::ofstream::out | std::ofstream::trunc);
        }
        else
        {
            std::cout << "Parse Error"<<std::endl;
            write.open("testJSON.json", std::ofstream::out );
        }

        if (write.is_open())
        {
            JsonFile.append(userJson);
            Json::StyledWriter sw;

            std::cout << "Uploading " << user->getNickname() << " information" << std::endl;
            std::string f = sw.write(JsonFile);
            std::cout << f << std::endl;

            write << f;
            write.close();
            read.close();
        }
        else
        {
            std::cout << "Error file";
        }
        read.close();
    }
    else
    {
        std::cout << "Error file" << std::endl;
    }

}
