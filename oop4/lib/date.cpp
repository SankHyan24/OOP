#include <pd.hpp>
#include <sstream>
#include <chrono>
date date::today()
{
    date d;
    return d;
}
date::date()
{
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    tm *now_tm = localtime(&now_c);
    day = now_tm->tm_mday;
    month = now_tm->tm_mon + 1;
    year = now_tm->tm_year + 1900;
}
date::date(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}
void date::print() const
{
    std::cout << year << "/" << month << "/" << day << std::endl;
}
bool date::operator<(date d)
{
    if (year < d.year)
        return true;
    else if (year == d.year)
    {
        if (month < d.month)
            return true;
    }
    else if (year == d.year && month == d.month)
    {
        if (day < d.day)
            return true;
    }
    return false;
}
bool date::operator>(date d)
{
    if (year > d.year)
        return true;
    else if (year == d.year)
    {
        if (month > d.month)
            return true;
    }
    else if (year == d.year && month == d.month)
    {
        if (day > d.day)
            return true;
    }
    return false;
}
bool date::operator==(date d)
{
    return d.day == day && d.month == month && d.year == year;
}
bool date::operator>=(date d)
{
    return !(*this < d);
}
bool date::operator<=(date d)
{
    return !(*this > d);
}
date date::operator+(int n)
{
    date d(day, month, year);
    if (n > 28)
    {
        d = d + (n - 28);
        d = d + 28;
        return d;
    }
    d.day = day + n;
    if (month == 2)
    {
        if (day == 28 && d.day >= 29)
            d.day = d.day - 29, d.month = 3;
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (d.day > 31)
            d.day = d.day - 31, d.month = month + 1;
    }
    else if (d.day > 30)
        d.day = d.day - 30, d.month = month + 1;
    return d;
}
bool date::set_day()
{
    cout << "Please input the date: ";
    int d, m, y;
    while (1)
    {
        cin >> y >> m >> d;
        if (d < 1 || d > 31 || m < 1 || m > 12 || y < 0)
        {
            cout << "Invalid date, please input valid date!" << endl;
            return false;
        }
        break;
    }
    reset(d, m, y);
    return true;
}
bool date::set_day(string str)
{
    int d, m, y;
    stringstream ss(str);
    ss >> y >> m >> d;
    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 0)
    {
        cout << "Invalid date, please input valid date!" << endl;
        return false;
    }
    reset(d, m, y);
    return true;
}
