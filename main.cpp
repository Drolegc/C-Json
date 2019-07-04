#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

int main()
{

    std::fstream file;
    std::ofstream fileW;
    file.open("testJSON.json", std::fstream::in | std::fstream::out | std::fstream::app);
    fileW.open("testJSON.json", std::fstream::in | std::fstream::out | std::fstream::app);


    /*

    JSON

    {
        'name':'Leandro',
        'apellido':'Gonzalez',
    }
    {
        'name':'Felipe',
        'apellido':'Gonzalez',
    }

    */

    Json::Value object;
    Json::Reader reader;

    
    if (file.is_open())
    {
        

        std::string nombre;
        std::string apellido;
        bool ok_parse = reader.parse(file, object);
        if (ok_parse)
        {
            
            std::cout<<"Name: ";
            std::cin >> nombre;
            std::cout << "Lastname: ";
            std::cin >> apellido;

            const Json::Value object_a;

            object_a["name"] = nombre;
            object_a["lastname"] = apellido;
            object.append(object_a);
        }
        else
        {
            std::cout << "Error: " << reader.getFormattedErrorMessages();
        }
    }
    Json::StyledWriter sw;
    std::string f = sw.write(object);

    std::cout << "Para subir: " << f << std::endl;

    if (fileW.is_open())
    {
        fileW << f;
        file.close();
        fileW.close();
    }

    return 0;
}