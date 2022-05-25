#pragma once
/**
 * Binary Deserialization
 *
 * Contains functions for deserializing data
 * to and from binary files.
 */
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <macro.hpp>
#include <utility.hpp>

namespace BinSerial
{
    // Basic Function
    template <typename T>
    int deserialize_(T &var, std::istream &in);
    template <typename T>
    int deserialize_(std::vector<T> &var, std::istream &in);
    template <typename T, typename C>
    int deserialize_(std::pair<T, C> &var, std::istream &in);
    void deserialize_(size_t index, std::tuple<> &tuple, std::istream &in);
    template <typename T, typename... Ts>
    void deserialize_(size_t index, std::tuple<T, Ts...> &t, std::istream &in);
    // Advance Function
    template <typename T, typename... Ts>
    int deserialize_(std::tuple<T, Ts...> &var, std::istream &in);
    template <typename T>
    int deserialize_(std::set<T> &var, std::istream &in);
    template <typename T>
    int deserialize_(std::list<T> &var, std::istream &in);
    template <typename T, typename C>
    int deserialize_(std::map<T, C> &var, std::istream &in);
    // Interface function
    template <>
    int deserialize_(std::string &var, std::istream &in);

    template <typename T>
    int deserialize(T &var, const std::string &file_name);

    template <typename T>
    int deserialize_(T &var, std::istream &in)
    {
        in.read(reinterpret_cast<char *>(&var), sizeof(var));
        return 0;
    }
    template <typename T>
    int deserialize_(std::vector<T> &var, std::istream &in)
    {
        size_t size;
        in.read(reinterpret_cast<char *>(&size), sizeof(size));
        for (int i = 0; i < size; i++)
        {
            T tmp;
            deserialize_(tmp, in);
            var.push_back(tmp);
        }
        return 0;
    }
    template <typename T, typename C>
    int deserialize_(std::pair<T, C> &var, std::istream &in)
    {
        deserialize_(var.first, in);
        deserialize_(var.second, in);
        return 0;
    }
    void deserialize_(size_t index, std::tuple<> &tuple, std::istream &in) {}
    template <typename T, typename... Ts>
    void deserialize_(size_t index, std::tuple<T, Ts...> &t, std::istream &in)
    {
        if (index >= (1 + sizeof...(Ts)))
            throw std::invalid_argument("bad index");
        if (index > 0)
            deserialize_(index - 1, reinterpret_cast<std::tuple<Ts...> &>(t), in);
        deserialize_(std::get<0>(t), in);
    }
    template <typename T, typename... Ts>
    int deserialize_(std::tuple<T, Ts...> &var, std::istream &in)
    {
        auto size = std::tuple_size<std::tuple<T, Ts...>>::value;
        deserialize_(size - 1, var, in);
        return 0;
    }
    template <typename T>
    int deserialize_(std::set<T> &var, std::istream &in)
    {
        std::vector<T> vec;
        int res = deserialize_(vec, in);
        for (auto &i : vec)
            var.insert(i);
        return res;
    }
    template <typename T>
    int deserialize_(std::list<T> &var, std::istream &in)
    {
        std::vector<T> vec;
        int res = deserialize_(vec, in);
        for (auto &i : vec)
            var.push_back(i);
        return res;
    }
    template <typename T, typename C>
    int deserialize_(std::map<T, C> &var, std::istream &in)
    {
        size_t size;
        in.read(reinterpret_cast<char *>(&size), sizeof(size));
        for (int i = 0; i < size; i++)
        {
            T key;
            C value;
            deserialize_(key, in);
            deserialize_(value, in);
            var.insert(std::make_pair(key, value));
        }
        return 0;
    }
    template <>
    int deserialize_(std::string &var, std::istream &in)
    {
        std::vector<char> vec;
        int res = deserialize_(vec, in);
        var = std::string(vec.begin(), vec.end());
        return res;
    }
    /**
     * Function: deserialize
     * Description: Deserialize a variable from a file
     * @param var: the variable to be deserialized
     * @param file_name: the file name to be deserialized
     * @return: 0 if success, -1 if failed
     */
    template <typename T>
    int deserialize(T &var, const std::string &file_name)
    {
        std::ifstream fin(file_name, std::ios::in | std::ios::binary);
        if (!fin)
            return -1;
        deserialize_(var, fin);
        fin.close();
        return 0;
    }
}