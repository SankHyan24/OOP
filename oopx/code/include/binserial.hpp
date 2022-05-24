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
namespace BinSerial
{
    template <typename T>
    int serialize_(T &var, std::ostream &out);
    template <typename T>
    int serialize_(std::vector<T> &var, std::ostream &out);
    template <typename T>
    int serialize_(std::set<T> &var, std::ostream &out);
    template <typename T>
    int serialize_(std::list<T> &var, std::ostream &out);
    template <typename T, typename C>
    int serialize_(std::map<T, C> &var, std::ostream &out);
    template <>
    int serialize_(std::string &var, std::ostream &out);

    /**
     * Function: serialize
     * Description: Serialize a variable to a file
     * @param var: the variable to be serialized
     * @param file_name: the file name to be serialized
     * @return: 0 if success, -1 if failed
     */
    template <typename T>
    int serialize(T &var, const std::string &file_name);

    template <typename T>
    int serialize_(T &var, std::ostream &out)
    {
        out.write(reinterpret_cast<char *>(&var), sizeof(var));
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
    template <typename T>
    int serialize_(std::set<T> &var, std::ostream &out)
    {
        // transform set to vector
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
        return 0;
    }
    template <>
    int serialize_(std::string &var, std::ostream &out)
    {
        std::vector<char> vec(var.begin(), var.end());
        return serialize_(vec, out);
    }
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