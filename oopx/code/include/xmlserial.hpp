#pragma once

#include <iostream>
#include <fstream>
#include <tinyxml2.h>
using namespace tinyxml2;
namespace XMLSerial
{
    void serialize(const tinyxml2::XMLDocument &doc, const std::string &file_name);
    void deserialize(tinyxml2::XMLDocument &doc, const std::string &file_name);
}