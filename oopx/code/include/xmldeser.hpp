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
#include <cstring>
using namespace tinyxml2;
namespace XMLSerial
{
    // Basic Function
    template <typename T>
    int deserialize_(T &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname = "");
    template <typename T>
    int deserialize_(std::vector<T> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname = "");
    template <typename T, typename C>
    int deserialize_(std::pair<T, C> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname = "");
    void deserialize_(size_t index, std::tuple<> &tuple, SerialCtrl &a, XMLElement *node, XMLElement *formor);
    template <typename T, typename... Ts>
    void deserialize_(size_t index, std::tuple<T, Ts...> &t, SerialCtrl &a, XMLElement *node, XMLElement *formor);
    // advanced
    template <typename T, typename... Ts>
    int deserialize_(std::tuple<T, Ts...> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname = "");
    template <typename T>
    int deserialize_(std::set<T> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname = "");
    template <typename T>
    int deserialize_(std::list<T> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname = "");
    template <typename T, typename C>
    int deserialize_(std::map<T, C> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname = "");
    template <>
    int deserialize_(std::string &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname);
    // Interface function
    template <typename T>
    int deserialize(T &var, const std::string &file_name, const std::string &class_name = "");

#define STANDARD_DESERIALIZE_CHECK                \
    XMLElement *child = nullptr, *prep = nullptr; \
    if (node->FirstChildElement() != nullptr)     \
        if (formor != nullptr)                    \
        {                                         \
            child = formor->NextSiblingElement(); \
            formor = child;                       \
        }                                         \
        else                                      \
        {                                         \
            child = node->FirstChildElement();    \
            formor = child;                       \
        }                                         \
    else                                          \
        throw std::runtime_error("XMLSerial::deserialize_: node has no child");

    template <typename T>
    int deserialize_(T &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname)
    {
        STANDARD_DESERIALIZE_CHECK
        if (child->Name() != varname && varname != "")
            throw std::runtime_error("XMLSerial::deserialize_: node name is not match");
        if (child->Attribute("value") != nullptr)
        {
            std::stringstream ss;
            ss << child->Attribute("value");
            ss >> var;
        }
        else
            return -1;
        return 0;
    }
    template <typename T>
    int deserialize_(std::vector<T> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname)
    {
        STANDARD_DESERIALIZE_CHECK
        if (child->Name() != varname && varname != "")
            throw std::runtime_error("XMLSerial::deserialize_: node name is not match");
        size_t size = 0;
        if (child->Attribute("size") != nullptr)
        {
            std::stringstream ss;
            ss << child->Attribute("size");
            ss >> size;
        }
        else
            return -1;
        var.resize(size);
        int flag = 0;
        for (size_t i = 0; i < size; i++)
        {
            T tmp;
            flag += deserialize_(tmp, a, child, prep);
            var[i] = tmp;
        }
        return flag;
    }
    template <typename T, typename C>
    int deserialize_(std::pair<T, C> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname)
    {
        STANDARD_DESERIALIZE_CHECK
        if (child->Name() != varname && varname != "")
            throw std::runtime_error("XMLSerial::deserialize_: node name is not match");
        int flag = 0;
        T tmp1;
        flag += deserialize_(tmp1, a, child, prep, "first");
        C tmp2;
        flag += deserialize_(tmp2, a, child, prep, "second");
        var = std::make_pair(tmp1, tmp2);
        return flag;
    }
    void deserialize_(size_t index, std::tuple<> &tuple, SerialCtrl &a, XMLElement *node, XMLElement *formor) {}
    template <typename T, typename... Ts>
    void deserialize_(size_t index, std::tuple<T, Ts...> &t, SerialCtrl &a, XMLElement *node, XMLElement *formor)
    {
        if (index >= (1 + sizeof...(Ts)))
            throw std::invalid_argument("bad index");
        deserialize_(std::get<0>(t), a, node, formor);
        if (index > 0)
            deserialize_(index - 1, reinterpret_cast<std::tuple<Ts...> &>(t), a, node, formor);
    }
    template <typename T, typename... Ts>
    int deserialize_(std::tuple<T, Ts...> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname)
    {
        STANDARD_DESERIALIZE_CHECK
        if (child->Name() != varname && varname != "")
            throw std::runtime_error("XMLSerial::deserialize_: node name is not match");
        size_t size = 0;
        if (child->Attribute("size") != nullptr)
        {
            std::stringstream ss;
            ss << child->Attribute("size");
            ss >> size;
        }
        else
            return -1;
        if (size != std::tuple_size<std::tuple<T, Ts...>>::value)
            throw std::runtime_error("XMLSerial::deserialize_: size is not match");
        deserialize_(size - 1, var, a, child, prep);
        return 0;
    }
    template <typename T>
    int deserialize_(std::set<T> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname)
    {
        STANDARD_DESERIALIZE_CHECK
        if (child->Name() != varname && varname != "")
            throw std::runtime_error("XMLSerial::deserialize_: node name is not match");
        size_t size = 0;
        if (child->Attribute("size") != nullptr)
        {
            std::stringstream ss;
            ss << child->Attribute("size");
            ss >> size;
        }
        else
            return -1;
        var.clear();
        int flag = 0;
        for (size_t i = 0; i < size; i++)
        {
            T tmp;
            flag += deserialize_(tmp, a, child, prep);
            var.insert(tmp);
        }
        return flag;
    }
    template <typename T>
    int deserialize_(std::list<T> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname)
    {
        STANDARD_DESERIALIZE_CHECK
        if (child->Name() != varname && varname != "")
            throw std::runtime_error("XMLSerial::deserialize_: node name is not match");
        size_t size = 0;
        if (child->Attribute("size") != nullptr)
        {
            std::stringstream ss;
            ss << child->Attribute("size");
            ss >> size;
        }
        else
            return -1;
        var.clear();
        int flag = 0;
        for (size_t i = 0; i < size; i++)
        {
            T tmp;
            flag += deserialize_(tmp, a, child, prep);
            var.push_back(tmp);
        }
        return 0;
    }
    template <typename T, typename C>
    int deserialize_(std::map<T, C> &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname)
    {
        STANDARD_DESERIALIZE_CHECK
        if (child->Name() != varname && varname != "")
            throw std::runtime_error("XMLSerial::deserialize_: node name is not match");
        size_t size = 0;
        if (child->Attribute("size") != nullptr)
        {
            std::stringstream ss;
            ss << child->Attribute("size");
            ss >> size;
        }
        else
            return -1;
        var.clear();
        int flag = 0;
        for (size_t i = 0; i < size; i++)
        {
            std::pair<T, C> tmp;
            flag += deserialize_(tmp, a, child, prep);
            var.insert(tmp);
        }
        return flag;
    }
    template <>
    int deserialize_(std::string &var, SerialCtrl &a, XMLElement *node, XMLElement *&formor, const std::string &varname)
    {
        STANDARD_DESERIALIZE_CHECK
        var = child->GetText();
        if (child->Attribute("length") != nullptr)
        {
            std::stringstream ss(child->Attribute("length"));
            int length;
            ss >> length;
            if (length != var.size())
                throw std::runtime_error("XMLSerial::deserialize_: string length is not match");
        }
        else
            return -1;
        return 0;
    }
    // Interface Function
    template <typename T>
    int deserialize(T &var, const std::string &file_name, const std::string &class_name)
    {
        SerialCtrl a(file_name);
        XMLElement *formor = nullptr;
        return deserialize_(var, a, a.GetRoot(), formor, class_name);
    }
#undef STANDARD_DESERIALIZE_CHECK
}