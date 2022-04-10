#include <pd.hpp>
#include <fstream>
#include <sstream>
#include <algorithm>
bool data_base::check()
{
    ifstream fin(filename);
    if (!fin)
        return false;
    fin.close();
    file_exist = true;
    return true;
}
bool data_base::init()
{
    ofstream fout(filename);
    if (!fout)
        return false;
    fout.close();
    file_exist = true;
    return true;
}
int data_base::locate_date(date d)
{
    int i = 0;
    while (i < diaries.size() && diaries[i].get_date() < d)
        i++;
    return i;
}
void data_base::read()
{
    if (!file_exist)
        return;
    ifstream fin(filename);
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string sdate;
        getline(ss, sdate, ' ');
        int y = atoi(sdate.c_str());
        getline(ss, sdate, ' ');
        int m = atoi(sdate.c_str());
        getline(ss, sdate, ' ');
        int d = atoi(sdate.c_str());
        date this_date(d, m, y);
        string entry;
        cin.clear();
        while (getline(fin, line))
        {
            size_t pos = line.find('.');
            if (pos != string::npos)
            {
                entry += line.substr(0, pos) + ".\n";
                break;
            }
            else
                entry += line + "\n";
        }
        diaries.push_back(diary(this_date, entry));
    }
}
void data_base::write()
{
    if (!file_exist)
        return;
    ofstream fout(filename);
    for (auto &d : diaries)
        fout << d.get_date().get_year() << " " << d.get_date().get_month() << " " << d.get_date().get_day() << endl
             << d.get_text();
    fout.close();
}
bool data_base::add()
{

    date this_date;
    if (!this_date.set_day())
        return false;
    cout << "Please input the entry: ";
    string entry, line;
    while (getline(cin, line))
    {
        size_t pos = line.find('.');
        if (pos != string::npos)
        {
            entry += line.substr(0, pos) + ".\n";
            break;
        }
        else
            entry += line + "\n";
    }
    entry = entry.substr(1, entry.size() - 1);
    for (auto &d : diaries)
        if (d.get_date() == this_date)
        {
            d.add(entry);
            return true;
        }
    diaries.push_back(diary(this_date, entry));
    sort(diaries.begin(), diaries.end());
    return true;
}
bool data_base::remove(date d)
{
    int i = locate_date(d);
    if (i == diaries.size())
        return false;
    diaries.erase(diaries.begin() + i);
    return true;
}
void data_base::print() const
{
    for (auto &d : diaries)
        d.print();
}
bool data_base::print(date start, date end) const
{
    bool ifprint = false;
    for (auto &d : diaries)
        if (d.get_date() >= start && d.get_date() <= end)
            d.print(), ifprint = true;
    return ifprint;
}
bool data_base::print_after(date start) const
{
    bool ifprint = false;
    for (auto &d : diaries)
        if (d.get_date() >= start)
            d.print(), ifprint = true;
    return ifprint;
}
bool data_base::print_before(date end) const
{
    bool ifprint = false;
    for (auto &d : diaries)
        if (d.get_date() <= end)
            d.print(), ifprint = true;
    return ifprint;
}