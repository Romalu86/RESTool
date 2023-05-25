#include "SpriteClassParser.h"
#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

// Alien Shooter 1 \ Zombie Shooter 1 Engines

std::string GetSpriteClassText(int value)
{
    std::ifstream file("data\\constants.ini");
    if (file)
    {
        std::string section = "[SpriteClass]";
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

std::string GetSpriteClass2Text(int value)
{
    std::ifstream file("data\\constants.ini");
    if (file)
    {
        std::string section = "[SpriteClass2]";
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