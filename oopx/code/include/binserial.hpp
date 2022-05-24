#pragma once

#include <iostream>
#include <fstream>
namespace BinSerial
{
    template <typename T>
    int serialize(T &t, const std::string &a)
    {
        std::ofstream fout(a, std::ios::out | std::ios::binary);
        if (!fout)
        {
            std::cout << "open file error" << std::endl;
            return -1;
        }
        fout.write((char *)&t, sizeof(t));
        fout.close();
        return 0;
    }
    template <typename T>
    int deserialize(T &t, const std::string &a)
    {
        std::ifstream fin(a, std::ios::in | std::ios::binary);
        if (!fin)
        {
            std::cout << "open file error" << std::endl;
            return -1;
        }
        fin.read((char *)&t, sizeof(t));
        fin.close();
        return 0;
    }
}