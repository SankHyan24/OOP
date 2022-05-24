#pragma once

#include <iostream>
#include <fstream>
#include <tinyxml2.h>
namespace XMLSerial
{
    using namespace tinyxml2;
    using namespace std;
    using namespace BinSerial;
    using namespace Utility;
    void serialize(const tinyxml2::XMLDocument &doc, const string &file_name);
    void deserialize(tinyxml2::XMLDocument &doc, const string &file_name);

}