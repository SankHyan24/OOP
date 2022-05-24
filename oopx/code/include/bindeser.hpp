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
namespace BinSerial
{
    template <typename T>
    int deserialize_(T &var, std::istream &in);
    template <typename T>
    int deserialize_(std::vector<T> &var, std::istream &in);
    template <typename T>
    int deserialize_(std::set<T> &var, std::istream &in);
    template <typename T>
    int deserialize_(std::list<T> &var, std::istream &in);
    template <typename T, typename C>
    int deserialize_(std::map<T, C> &var, std::istream &in);
    template <>
    int deserialize_(std::string &var, std::istream &in);

    /**
     * Function: deserialize
     * Description: Deserialize a variable from a file
     * @param var: the variable to be deserialized
     * @param file_name: the file name to be deserialized
     * @return: 0 if success, -1 if failed
     */
    template <typename T>
    int deserialize(T &var, const std::string &file_name);

    template <typename T>
    int deserialize_(T &var, std::istream &in)
    {
        in.read(reinterpret_cast<char *>(&var), sizeof(T));
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