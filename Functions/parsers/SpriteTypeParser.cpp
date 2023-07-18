#include "SpriteTypeParser.h"

// Alien Shooter 1 \ Zombie Shooter 1 Engines

std::string GetSpriteTypeText(int value)
{
    std::ifstream file("data\\constants.ini");
    if (file)
    {
        std::string section = "[SpriteType]";
        bool foundSection = false;

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty() || line[0] == ';') continue; // Пропустить пустые строки и комментарии

            if (line == section)
            {
                foundSection = true;
                continue;
            }

            if (foundSection)
            {
                size_t pos = line.find('=');
                if (pos != std::string::npos)
                {
                    int intValue = std::stoi(line.substr(0, pos));
                    if (intValue == value)
                    {
                        return line.substr(pos + 1);
                    }
                }
                else
                {
                    break; // Конец секции, выходим из цикла
                }
            }
        }
    }

    return ""; // Если значение не найдено, возвращаем пустую строку
}

// Alien Shooter 2 \ Zombie Shooter 2 Engines

std::string GetSpriteType2Text(int value)
{
    std::ifstream file("data\\constants.ini");
    if (file)
    {
        std::string section = "[SpriteType2]";
        bool foundSection = false;

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty() || line[0] == ';') continue; // Пропустить пустые строки и комментарии

            if (line == section)
            {
                foundSection = true;
                continue;
            }

            if (foundSection)
            {
                size_t pos = line.find('=');
                if (pos != std::string::npos)
                {
                    int intValue = std::stoi(line.substr(0, pos));
                    if (intValue == value)
                    {
                        return line.substr(pos + 1);
                    }
                }
                else
                {
                    break; // Конец секции, выходим из цикла
                }
            }
        }
    }

    return ""; // Если значение не найдено, возвращаем пустую строку
}
