#include "ObjectsPropertyParser.h"
#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

// Alien Shooter 1 \ Zombie Shooter 1 Engines

std::string GetObjectsPropertyText(int value)
{
    std::ifstream file("constants.ini");
    if (file)
    {
        std::string section = "[Objects_Property]";
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
                    std::string propertyValue = line.substr(pos + 1);
                    if (line.substr(0, pos) == "0x" + std::to_string(value))
                    {
                        return propertyValue;
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

std::string GetObjects2PropertyText(int value)
{
    std::ifstream file("constants.ini");
    if (file)
    {
        std::string section = "[Objects2_Property]";
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
                    std::string propertyValue = line.substr(pos + 1);
                    if (line.substr(0, pos) == "0x" + std::to_string(value))
                    {
                        return propertyValue;
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

// Legend Engine Property2

std::string GetLegendObjectsProperty2Text(int value)
{
    std::ifstream file("constants.ini");
    if (file)
    {
        std::string section = "[LegendEngine_property2]";
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
                    std::string propertyValue = line.substr(pos + 1);
                    if (line.substr(0, pos) == "0x" + std::to_string(value))
                    {
                        return propertyValue;
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

 // AS1 World Property2

std::string GetWorldObjectsProperty2Text(int value)
{
    std::ifstream file("constants.ini");
    if (file)
    {
        std::string section = "[AS1Mobile_property2]";
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
                    std::string propertyValue = line.substr(pos + 1);
                    if (line.substr(0, pos) == "0x" + std::to_string(value))
                    {
                        return propertyValue;
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

 // AS1 World Property3

std::string GetWorldObjectsProperty3Text(int value)
{
    std::ifstream file("constants.ini");
    if (file)
    {
        std::string section = "[AS1Mobile_property3]";
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
                    std::string propertyValue = line.substr(pos + 1);
                    if (line.substr(0, pos) == "0x" + std::to_string(value))
                    {
                        return propertyValue;
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