#include "Controller.h"
#include "../ICollection/collections/List.h"
#include "../ICollection/collections/OrderedDictionary.h"
#include "../ICollection/StringKey.h"

#include "../classes/headers/Record.h"

Controller *Controller::instance = 0;

Controller::Controller()
{
    this->dicGames = new OrderedDictionary();
    this->dicUsers = new OrderedDictionary();
    this->session = NULL;
}

void Controller::JSONToObjects()
{
    //First, open the JSON file

    std::fstream JSONfile;
    JSONfile.open("testJSON.json", std::fstream::in);

    //Put the info into a JSON Object

    Json::Value *obj = new Json::Value(Json::ValueType::nullValue);
    Json::Reader *reader = new Json::Reader();

    bool ok_parse = reader->parse(JSONfile, *obj);
    JSONfile.close();

    if (ok_parse)
    {
        std::cout << "Creating all..." << std::endl;

        //We have the Json "father"
        //Now we need to iterate for each object

        //Json::Value::const_iterator it;
        std::string nickname;
        std::string password;

        Json::ValueIterator it;
        for (it = obj->begin(); it.operator!=(obj->end()); ++it)
        {

            //Because it isnt a pointer, we need the memory location to point it (?)
            Json::Value *new_obj = &(*it);

            nickname = new_obj->get("Nickname", Json::ValueType::nullValue).asString();
            password = new_obj->get("Password", Json::ValueType::nullValue).asString();

            //Now, to make use of setRecord from the controller, each time
            //that we have a user, we make it "log in"
            User *user = new User(nickname, password);

            //Take the records in to a Json::value
            Json::Value *records = new Json::Value(new_obj->get("records", Json::ValueType::nullValue));

            Json::ValueIterator records_it;
            for (records_it = records->begin(); records_it.operator!=(records->end()); ++records_it)
            {
                /*
                    The object Record needs the points and the game
                    First: Check if the game is in the dictionary of Controller
                    if isnt, create the game and add it
                */

                std::string game_name = (*records_it).get("Game", Json::ValueType::nullValue).asString();
                int points = (*records_it).get("points", Json::ValueType::nullValue).asInt();

                StringKey *k = new StringKey(game_name);
                Game *g;

                if (!dicGames->member(k))
                {
                    g = new Game(game_name);
                    dicGames->add(k, g);
                }
                else
                {
                    g = dynamic_cast<Game *>(dicGames->find(k));
                }

                Record *r = new Record(points, g);
                //Now we have the record, its time to add it to the collection of Records from the user
                user->setRecord(r);

                StringKey *k_user = new StringKey(nickname);
                dicUsers->add(k_user, dynamic_cast<ICollectible *>(user));
            }
        }
    }
    else
    {
        std::ofstream f;
        f.open("testJSON.json", std::ios::trunc);
        if (!f.is_open())
        {
            std::cout << "Error JSONToObjects" << std::endl;
        }
        else
        {
            f.close();
        }
    }
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
        delete k;
        throw std::invalid_argument("User nor sign up");
    }
}

void Controller::addGame(std::string game)
{

    StringKey *k = new StringKey(game);
    if (dicGames->member(k))
    {
        delete k;
        throw std::invalid_argument("That game its already exists");
    }
    Game *g = new Game(game);

    dicGames->add(k, g);
}

void Controller::SignUp(std::string name, std::string pass)
{
    StringKey *k = new StringKey(name);
    if (dicUsers->member(k))
    {
        delete k;
        throw std::invalid_argument("User already exists");
    }
    User *user = new User(name, pass);
    dicUsers->add(k, user);
}

void Controller::setRecord(int points, std::string name_game)
{

    ICollection *colRecord = session->getColRecord();
    StringKey *k = new StringKey(name_game);
    Game *g = dynamic_cast<Game *>(dicGames->find(k));
    Record *new_record = new Record(points, g);
    colRecord->add(new_record);
    std::cout << "Add it to the records of the user" << std::endl;
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

void Controller::ObjectsToJSON()
{

    std::ifstream read;
    std::ofstream write;
    read.open("testJSON.json");

    Json::Value JsonFile;
    Json::Reader reader;

    //Use read.open to know if the file exists
    if (read.is_open())
    {

        //Iterate for each user and make it session

        IIterator *it = dicUsers->getIterator();
        //Insert data into User JSON
        while (it->hasCurrent())
        {
            //Create a User JSON
            Json::Value userJson;
            User *user = dynamic_cast<User *>(it->getCurrent());

            userJson["Nickname"] = user->getNickname();
            userJson["Password"] = user->getPassword();
            //append a JSON object that is the record of the user
            //Get the collections of records and the iterator
            ICollection *records = user->getColRecord();
            IIterator *itR = records->getIterator();

            //foreach record, append a Json value thats equals to the record
            while (itR->hasCurrent())
            {
                Record *record = dynamic_cast<Record *>(itR->getCurrent());
                Json::Value JsonRecord;
                JsonRecord["points"] = record->getPoints();
                JsonRecord["Game"] = record->getGame();
                //Once the JsonRecord its ready, we append it to userJson
                userJson["records"].append(JsonRecord);

                itR->next();
            }
            JsonFile.append(userJson);
            it->next();
        }
        //Json ready to upload
        //Here we need to parse to JsonFile and then delete all from the file
        write.open("testJSON.json", std::ios_base::out | std::ios_base::trunc);

        if (write.is_open())
        {

            Json::StyledWriter sw;

            std::cout << "Uploading information" << std::endl;
            std::string f = sw.write(JsonFile);

            write << f;
            write.close();
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
