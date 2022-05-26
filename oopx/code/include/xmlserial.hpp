#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <tuple>
#include <tinyxml2.h>
#include <macro.hpp>
#include <utility.hpp>
#include <xmlctrl.hpp>
using namespace tinyxml2;
namespace XMLSerial
{
    // Basic Function
    template <typename T>
    int serialize_(T &var, SerialCtrl &a, XMLElement *node, const std::string &varname = "");
    template <typename T>
    int serialize_(std::vector<T> &var, SerialCtrl &a, XMLElement *node, const std::string &varname = "");
    template <typename T, typename C>
    int serialize_(std::pair<T, C> &var, SerialCtrl &a, XMLElement *node, const std::string &varname = "");
    void serialize_(size_t index, std::tuple<> &tuple, SerialCtrl &a, XMLElement *node, const std::string &varname = "");
    template <typename T, typename... Ts>
    void serialize_(size_t index, std::tuple<T, Ts...> &t, SerialCtrl &a, XMLElement *node, const std::string &varname = "");
    // advanced
    template <typename T, typename... Ts>
    int serialize_(std::tuple<T, Ts...> &var, SerialCtrl &a, XMLElement *node, const std::string &varname = "");
    template <typename T>
    int serialize_(std::set<T> &var, SerialCtrl &a, XMLElement *node, const std::string &varname = "");
    template <typename T>
    int serialize_(std::list<T> &var, SerialCtrl &a, XMLElement *node, const std::string &varname = "");
    template <typename T, typename C>
    int serialize_(std::map<T, C> &var, SerialCtrl &a, XMLElement *node, const std::string &varname = "");
    template <>
    int serialize_(std::string &var, SerialCtrl &a, XMLElement *node, const std::string &varname);
    // Interface function
    template <typename T>
    int serialize(T &var, const std::string &file_name, const std::string &class_name = "");

#define OPT_TYPE_NAME(TYPE, VARNAME) ((VARNAME == "") ? TypeParseTraits<TYPE>::name : (VARNAME))
#define OPT_STRING_NAME(STR, VARNAME) ((VARNAME == "") ? STR : (VARNAME))
    template <typename T>
    int serialize_(T &var, SerialCtrl &a, XMLElement *node, const std::string &varname)
    {
        XMLElement *child = nullptr;
        return a.InsertNode(OPT_TYPE_NAME(T, varname), node, child, std::to_string(var));
    }
    template <typename T>
    int serialize_(std::vector<T> &var, SerialCtrl &a, XMLElement *node, const std::string &varname)
    {
        size_t size = var.size();
        XMLElement *child = nullptr;
        a.InsertNode(OPT_STRING_NAME("vector", varname), node, child);
        a.AddAttribute(child, "size", std::to_string(size));
        for (auto &i : var)
            serialize_(i, a, child);
        return 0;
    }
    template <typename T, typename C>
    int serialize_(std::pair<T, C> &var, SerialCtrl &a, XMLElement *node, const std::string &varname)
    {
        XMLElement *child = nullptr;
        a.InsertNode(OPT_STRING_NAME("pair", varname), node, child);
        serialize_(var.first, a, child, "first");
        serialize_(var.second, a, child, "second");
        return 0;
    }
    void serialize_(size_t index, std::tuple<> &tuple, SerialCtrl &a, XMLElement *node, const std::string &varname) {}
    template <typename T, typename... Ts>
    void serialize_(size_t index, std::tuple<T, Ts...> &t, SerialCtrl &a, XMLElement *node, const std::string &varname)
    {
        if (index >= (1 + sizeof...(Ts)))
            throw std::invalid_argument("bad index");
        serialize_(std::get<0>(t), a, node);
        if (index > 0)
            serialize_(index - 1, reinterpret_cast<std::tuple<Ts...> &>(t), a, node);
    }
    template <typename T, typename... Ts>
    int serialize_(std::tuple<T, Ts...> &var, SerialCtrl &a, XMLElement *node, const std::string &varname)
    {
        auto size = std::tuple_size<std::tuple<T, Ts...>>::value;
        XMLElement *child = nullptr;
        a.InsertNode(OPT_STRING_NAME("tuple", varname), node, child);
        a.AddAttribute(child, "size", std::to_string(size));
        serialize_(size - 1, var, a, child);
        return 0;
    }
    template <typename T>
    int serialize_(std::set<T> &var, SerialCtrl &a, XMLElement *node, const std::string &varname)
    {
        XMLElement *child = nullptr;
        a.InsertNode(OPT_STRING_NAME("set", varname), node, child);
        a.AddAttribute(child, "size", std::to_string(var.size()));
        for (auto &i : var)
            serialize_(i, a, child);
        return 0;
    }
    template <typename T>
    int serialize_(std::list<T> &var, SerialCtrl &a, XMLElement *node, const std::string &varname)
    {
        XMLElement *child = nullptr;
        a.InsertNode(OPT_STRING_NAME("list", varname), node, child);
        a.AddAttribute(child, "size", std::to_string(var.size()));
        for (auto &i : var)
            serialize_(i, a, child);
        return 0;
    }
    template <typename T, typename C>
    int serialize_(std::map<T, C> &var, SerialCtrl &a, XMLElement *node, const std::string &varname)
    {
        XMLElement *child = nullptr;
        a.InsertNode(OPT_STRING_NAME("map", varname), node, child);
        a.AddAttribute(child, "size", std::to_string(var.size()));
        for (auto &i : var)
        {
            XMLElement *child2 = nullptr;
            a.InsertNode("pair", child, child2);
            serialize_(i.first, a, child2, "first");
            serialize_(i.second, a, child2, "second");
        }
        return 0;
    }
    template <>
    int serialize_(std::string &var, SerialCtrl &a, XMLElement *node, const std::string &varname)
    {
        XMLElement *child = nullptr;
        a.InsertNode(OPT_STRING_NAME("string", varname), node, child);
        a.AddAttribute(child, "length", std::to_string(var.size()));
        a.InsertText(child, var);
        return 0;
    }
    // Interface Function
    template <typename T>
    int serialize(T &var, const std::string &file_name, const std::string &class_name)
    {
        remove(file_name.c_str());
        SerialCtrl a(file_name, "serialization", "1.0", "UTF-8");
        serialize_(var, a, a.GetRoot(), class_name);
        return a.GetDoc()->SaveFile(file_name.c_str());
    }
#undef OPT_TYPE_NAME
}

REGISTER_PARSE_TYPE(int);
REGISTER_PARSE_TYPE(const int);
REGISTER_PARSE_TYPE(float);
REGISTER_PARSE_TYPE(double);
REGISTER_PARSE_TYPE(char);
REGISTER_PARSE_TYPE(long double);
REGISTER_PARSE_TYPE(std::string);
