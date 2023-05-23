#ifndef OBJECTSPROPERTY_PARSER_H
#define OBJECTSPROPERTY_PARSER_H

#include <string>
#include <fstream>
#include "stdafx.h"

std::string GetObjectsPropertyText(int value); // AS1\ZS1 Engines
std::string GetObjects2PropertyText(int value); // AS2\ZS2 Engines
std::string GetLegendObjectsProperty2Text(int value); // Legend Engine Property2
std::string GetWorldObjectsProperty2Text(int value); // AS1 World Property2
std::string GetWorldObjectsProperty3Text(int value); // AS1 World Property3

#endif