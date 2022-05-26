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
    int serialize_(T &var, SerialCtrl &a, XMLElement *node);
    template <typename T>
    int serialize_(T &var, std::string varname, SerialCtrl &a, XMLElement *node);
    template <typename T>
    int serialize_(std::vector<T> &var, SerialCtrl &a, XMLElement *node);
    template <typename T, typename C>
    int serialize_(std::pair<T, C> &var, SerialCtrl &a, XMLElement *node);
    void serialize_(size_t index, std::tuple<> &tuple, SerialCtrl &a, XMLElement *node);
    template <typename T, typename... Ts>
    void serialize_(size_t index, std::tuple<T, Ts...> &t, SerialCtrl &a, XMLElement *node);
    // advanced
    template <typename T, typename... Ts>
    int serialize_(std::tuple<T, Ts...> &var, SerialCtrl &a, XMLElement *node);
    template <typename T>
    int serialize_(std::set<T> &var, SerialCtrl &a, XMLElement *node);
    template <typename T>
    int serialize_(std::list<T> &var, SerialCtrl &a, XMLElement *node);
    template <typename T, typename C>
    int serialize_(std::map<T, C> &var, SerialCtrl &a, XMLElement *node);
    template <>
    int serialize_(std::string &var, SerialCtrl &a, XMLElement *node);
    // Interface function
    template <typename T>
    int serialize(T &var, const std::string &class_name, const std::string &file_name);

    template <typename T>
    int serialize_(T &var, SerialCtrl &a, XMLElement *node)
    {
        XMLElement *child = nullptr;
        return a.InsertNode(TypeParseTraits<T>::name, std::to_string(var), node, child);
    }
    template <typename T>
    int serialize_(T &var, std::string varname, SerialCtrl &a, XMLElement *node)
    {
        XMLElement *child = nullptr;
        return a.InsertNode(varname, std::to_string(var), node, child);
    }
    template <typename T>
    int serialize_(std::vector<T> &var, SerialCtrl &a, XMLElement *node)
    {
        size_t size = var.size();
        XMLElement *child = nullptr;
        a.InsertNode("vector", "", node, child);
        a.AddAttribute(child, "size", std::to_string(size));
        for (auto &i : var)
            serialize_(i, a, child);
        return 0;
    }
    template <typename T, typename C>
    int serialize_(std::pair<T, C> &var, SerialCtrl &a, XMLElement *node)
    {
        XMLElement *child = nullptr;
        a.InsertNode("pair", "", node, child);
        serialize_(var.first, "first", a, child);
        serialize_(var.second, "second", a, child);
        return 0;
    }
    void serialize_(size_t index, std::tuple<> &tuple, SerialCtrl &a, XMLElement *node) {}
    template <typename T, typename... Ts>
    void serialize_(size_t index, std::tuple<T, Ts...> &t, SerialCtrl &a, XMLElement *node)
    {
        if (index >= (1 + sizeof...(Ts)))
            throw std::invalid_argument("bad index");
        serialize_(std::get<0>(t), a, node);
        if (index > 0)
            serialize_(index - 1, reinterpret_cast<std::tuple<Ts...> &>(t), a, node);
    }
    template <typename T, typename... Ts>
    int serialize_(std::tuple<T, Ts...> &var, SerialCtrl &a, XMLElement *node)
    {
        auto size = std::tuple_size<std::tuple<T, Ts...>>::value;
        XMLElement *child = nullptr;
        a.InsertNode("tuple", "", node, child);
        a.AddAttribute(child, "size", std::to_string(size));
        serialize_(size - 1, var, a, child);
        return 0;
    }
    template <typename T>
    int serialize_(std::set<T> &var, SerialCtrl &a, XMLElement *node)
    {
        XMLElement *child = nullptr;
        a.InsertNode("set", "", node, child);
        a.AddAttribute(child, "size", std::to_string(var.size()));
        for (auto &i : var)
            serialize_(i, a, child);
        return 0;
    }
    template <typename T>
    int serialize_(std::list<T> &var, SerialCtrl &a, XMLElement *node)
    {
        XMLElement *child = nullptr;
        a.InsertNode("list", "", node, child);
        a.AddAttribute(child, "size", std::to_string(var.size()));
        for (auto &i : var)
            serialize_(i, a, child);
        return 0;
    }
    template <typename T, typename C>
    int serialize_(std::map<T, C> &var, SerialCtrl &a, XMLElement *node)
    {
        XMLElement *child = nullptr;
        a.InsertNode("map", "", node, child);
        a.AddAttribute(child, "size", std::to_string(var.size()));
        for (auto &i : var)
        {
            XMLElement *child2 = nullptr;
            a.InsertNode("pair", "", child, child2);
            serialize_(i.first, "first", a, child2);
            serialize_(i.second, "second", a, child2);
        }
        return 0;
    }
    template <>
    int serialize_(std::string &var, SerialCtrl &a, XMLElement *node)
    {
        XMLElement *child = nullptr;
        a.InsertNode("string", "", node, child);
        a.AddAttribute(child, "length", std::to_string(var.size()));
        a.InsertText(child, var);
        return 0;
    }
    // Interface Function
    template <typename T>
    int serialize(T &var, const std::string &class_name, const std::string &file_name)
    {
        SerialCtrl a(file_name, "serialization", "1.0", "UTF-8");
        serialize_(var, a, a.GetRoot());
        a.GetDoc()->SaveFile(file_name.c_str());
        return 0;
    }
}

REGISTER_PARSE_TYPE(int);
REGISTER_PARSE_TYPE(const int);
REGISTER_PARSE_TYPE(double);
REGISTER_PARSE_TYPE(char);
REGISTER_PARSE_TYPE(long double);
REGISTER_PARSE_TYPE(std::string);
