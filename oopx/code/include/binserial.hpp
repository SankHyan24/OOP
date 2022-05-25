#pragma once
/**
 * Binary Serialization
 *
 * Contains functions for serializing data
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
    int serialize_(T &var, std::ostream &out);
    template <typename T>
    int serialize_(std::vector<T> &var, std::ostream &out);
    template <typename T, typename C>
    int serialize_(std::pair<T, C> &var, std::ostream &out);
    void serialize_(size_t index, std::tuple<> &tuple, std::ostream &out);
    template <typename T, typename... Ts>
    void serialize_(size_t index, std::tuple<T, Ts...> &t, std::ostream &out);
    // Advance Function
    template <typename T, typename... Ts>
    int serialize_(std::tuple<T, Ts...> &var, std::ostream &out);
    template <typename T>
    int serialize_(std::set<T> &var, std::ostream &out);
    template <typename T>
    int serialize_(std::list<T> &var, std::ostream &out);
    template <typename T, typename C>
    int serialize_(std::map<T, C> &var, std::ostream &out);
    template <>
    int serialize_(std::string &var, std::ostream &out);
    // Interface function
    template <typename T>
    int serialize(T &var, const std::string &file_name);

    template <typename T>
    int serialize_(T &var, std::ostream &out)
    {
        out.write(reinterpret_cast<const char *>(&var), sizeof(var));
        return 0;
    }
    template <typename T>
    int serialize_(std::vector<T> &var, std::ostream &out)
    {
        size_t size = var.size();
        out.write(reinterpret_cast<char *>(&size), sizeof(size));
        for (auto &i : var)
            serialize_(i, out);
        return 0;
    }
    template <typename T, typename C>
    int serialize_(std::pair<T, C> &var, std::ostream &out)
    {
        serialize_(var.first, out);
        serialize_(var.second, out);
        return 0;
    }
    void serialize_(size_t index, std::tuple<> &tuple, std::ostream &out) {}
    template <typename T, typename... Ts>
    void serialize_(size_t index, std::tuple<T, Ts...> &t, std::ostream &out)
    {
        if (index >= (1 + sizeof...(Ts)))
            throw std::invalid_argument("bad index");
        if (index > 0)
            serialize_(index - 1, reinterpret_cast<std::tuple<Ts...> &>(t), out);
        serialize_(std::get<0>(t), out);
    }
    template <typename T, typename... Ts>
    int serialize_(std::tuple<T, Ts...> &var, std::ostream &out)
    {
        auto size = std::tuple_size<std::tuple<T, Ts...>>::value;
        serialize_(size - 1, var, out);
        return 0;
    }
    template <typename T>
    int serialize_(std::set<T> &var, std::ostream &out)
    {
        std::vector<T> vec;
        for (auto &i : var)
            vec.push_back(i);
        return serialize_(vec, out);
    }
    template <typename T>
    int serialize_(std::list<T> &var, std::ostream &out)
    {
        std::vector<T> vec;
        for (auto &i : var)
            vec.push_back(i);
        return serialize_(vec, out);
    }
    template <typename T, typename C>
    int serialize_(std::map<T, C> &var, std::ostream &out)
    {
        std::vector<std::pair<T, C>> vec;
        for (auto &i : var)
            vec.push_back(std::make_pair(i.first, i.second));
        return serialize_(vec, out);
    }
    template <>
    int serialize_(std::string &var, std::ostream &out)
    {
        std::vector<char> vec(var.begin(), var.end());
        return serialize_(vec, out);
    }
    /**
     * Function: serialize
     * Description: Serialize a variable to a file
     * @param var: the variable to be serialized
     * @param file_name: the file name to be serialized
     * @return: 0 if success, -1 if failed
     */
    template <typename T>
    int serialize(T &var, const std::string &file_name)
    {
        std::ofstream fout(file_name, std::ios::out | std::ios::binary);
        if (!fout)
            return -1;
        serialize_(var, fout);
        fout.close();
        return 0;
    }
}