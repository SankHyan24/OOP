#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include <tinyxml2.h>
#include <utility.hpp>
#include <xmlctrl.hpp>
using namespace tinyxml2;
namespace XMLSerial
{
    // Basic Function
    template <typename T>
    int serialize_(T &var, SerialCtrl &a, XMLElement *node);
    template <typename T>
    int serialize_(std::vector<T> &var, SerialCtrl &a, XMLElement *node);
    template <typename T>
    int serialize(T &var, const std::string &class_name, const std::string &file_name);

    template <typename T>
    int serialize_(T &var, SerialCtrl &a, XMLElement *node)
    {
        XMLElement *child = nullptr;
        std::stringstream ss;
        ss << var;
        std::string str = ss.str(), type_name = TypeParseTraits<T>::name;
        return a.InsertNode(type_name, str, node, child);
    }
    template <typename T>
    int serialize_(std::vector<T> &var, SerialCtrl &a, XMLElement *node)
    {
        size_t size = var.size();
        XMLElement *child = nullptr;
        a.InsertNode("vector", "", node, child);
        for (auto &i : var)
            serialize_(i, a, child);
        return 0;
    }

    // Interface Function
    template <typename T>
    int serialize(T &var, const std::string &class_name, const std::string &file_name)
    {
        SerialCtrl a(file_name, "serialization", "1.0", "UTF-8");
        serialize_(var, a, a.GetRoot());
        a.doc_->SaveFile(file_name.c_str());
        return 0;
    }
}

REGISTER_PARSE_TYPE(int);
REGISTER_PARSE_TYPE(double);
REGISTER_PARSE_TYPE(char);
REGISTER_PARSE_TYPE(long double);