#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

int radf(int argc, char *argv[])
{
    ifstream fin("../data/Problem3_new.lgr");
    if (!fin)
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    string line;
    for (int i = 0; i < 48; i++)
        getline(fin, line);
    // read the data as the format: DRAWER( 1, 1)        0.000000
    bool drawer[28][28];
    for (int i = 0; i < 28 * 28; i++)
    {
        getline(fin, line);
        stringstream ss(line);
        string s;
        getline(ss, s, '(');
        getline(ss, s, ',');
        int x = stoi(s);
        getline(ss, s, ')');
        int y = stoi(s);
        getline(ss, s);
        int z = stoi(s);
        drawer[x - 1][y - 1] = z;
    }
    int index[28];
    for (int i = 0; i < 28; i++)
        for (int j = 0; j < 28; j++)
            if (drawer[i][j])
            {
                index[i] = j;
                break;
            }
    for (int i = 0; i < 28; i++)
        cout << index[i] << " ";
    int freq[28][28];
    // read the data as the format: DRAWER( 1, 1)        0.000000
    for (int i = 0; i < 28 * 28; i++)
        getline(fin, line);
    for (int i = 0; i < 28 * 28; i++)
    {
        getline(fin, line);
        stringstream ss(line);
        string s;
        getline(ss, s, '(');
        getline(ss, s, ',');
        int x = stoi(s);
        getline(ss, s, ')');
        int y = stoi(s);
        getline(ss, s);
        int z = stoi(s);
        freq[x - 1][y - 1] = z;
    }
    ofstream fout("../data/bestn.txt");
    if (!fout)
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    for (int i = 0; i < 28; i++)
        fout << setw(6) << index[i];
    fout << endl;
    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
            fout << setw(6) << freq[i][j] << " ";
        fout << endl;
    }
}