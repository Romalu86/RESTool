#include "NWeaponPropertyParser.h"
#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

// Alien Shooter 1 \ Zombie Shooter 1 Engines

std::string GetNWeaponPropertyText(int value)
{
    std::ifstream file("data\\constants.ini");
    if (file)
    {
        std::string section = "[NWeapon_Property]";
        bool foundSection = false;

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty() || line[0] == ';') continue; // Пропустить пустые строки и комментарии

            if (foundSection)
            {
                size_t pos = line.find('=');
                if (pos != std::string::npos)
                {
                    std::string keyString = line.substr(0, pos);
                    std::string valueString = line.substr(pos + 1);

                    keyString.erase(0, 2); // Удаление префикса "0x"
                    valueString.erase(0, valueString.find_first_not_of(' ')); // Удаление начальных пробелов

                    unsigned int keyValue;
                    try {
                        keyValue = std::stoul(keyString, nullptr, 16); // Преобразование ключа в числовое значение без знака
                    }
                    catch (...) {
                        continue; // Пропуск строки, если ключ не может быть преобразован в число
                    }

                    if (keyValue == static_cast<unsigned int>(value))
                    {
                        return valueString;
                    }
                }
                else
                {
                    break; // Конец секции, выходим из цикла
                }
            }

            if (line == section)
            {
                foundSection = true;
            }
        }

        return ""; // Если значение не найдено, возвращаем пустую строку
    }
}

// Alien Shooter 2 \ Zombie Shooter 2 Engines

    std::string GetNWeapon2PropertyText(int value)
    {
        std::ifstream file("data\\constants.ini");
        if (file)
        {
            std::string section = "[NWeapon2_Property]";
            bool foundSection = false;

            std::string line;
            while (std::getline(file, line))
            {
                if (line.empty() || line[0] == ';') continue; // Пропустить пустые строки и комментарии

                if (foundSection)
                {
                    size_t pos = line.find('=');
                    if (pos != std::string::npos)
                    {
                        std::string keyString = line.substr(0, pos);
                        std::string valueString = line.substr(pos + 1);

                        keyString.erase(0, 2); // Удаление префикса "0x"
                        valueString.erase(0, valueString.find_first_not_of(' ')); // Удаление начальных пробелов

                        unsigned int keyValue;
                        try {
                            keyValue = std::stoul(keyString, nullptr, 16); // Преобразование ключа в числовое значение без знака
                        }
                        catch (...) {
                            continue; // Пропуск строки, если ключ не может быть преобразован в число
                        }

                        if (keyValue == static_cast<unsigned int>(value))
                        {
                            return valueString;
                        }
                    }
                    else
                    {
                        break; // Конец секции, выходим из цикла
                    }
                }

                if (line == section)
                {
                    foundSection = true;
                }
            }

            return ""; // Если значение не найдено, возвращаем пустую строку
        }
    }