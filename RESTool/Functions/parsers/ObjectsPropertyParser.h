#ifndef OBJECTSPROPERTY_PARSER_H
#define OBJECTSPROPERTY_PARSER_H

#include <string>
#include <fstream>
#include "stdafx.h"

std::string GetObjectsPropertyText(int value); // AS1\ZS1 Engines
std::string GetObjects2PropertyText(int value); // AS2\ZS2 Engines
std::string GetExt1PropertyText(int value); // New Engine ext1Property
std::string GetExt2PropertyText(int value); // New Engine ext2Property

#endif