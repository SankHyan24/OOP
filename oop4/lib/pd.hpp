#pragma once
#include <iostream>
#include <vector>
using namespace std;
const string Default_filename = "pd.txt";
class date
{
private:
    int day;
    int month;
    int year;
    void reset(int d) { day = d; }
    void reset(int d, int m) { day = d, month = m; }
    void reset(int d, int m, int y) { day = d, month = m, year = y; }
    date today();

public:
    date();
    date(int d, int m, int y);
    date(string s) { set_day(s); }
    // Get data
    int get_day() const { return day; }
    int get_month() const { return month; }
    int get_year() const { return year; }
    // Output
    void print() const;
    // Operator overload
    bool operator<(date d);
    bool operator>(date d);
    bool operator==(date d);
    bool operator>=(date d);
    bool operator<=(date d);
    date operator+(int n);
    // Std setter
    bool set_day();
    bool set_day(string);
};

class diary
{
private:
    date this_day;
    string text;

public:
    diary(date d, string t) : this_day(d), text(t){};
    void add(string entry) { text = entry; }
    void print_text() const { cout << text << endl; }
    date get_date() const { return this_day; }
    string get_text() const { return text; }
    void print() const
    {
        this_day.print();
        print_text();
    }
    bool operator<(diary d) { return this_day < d.this_day; };
};

class data_base
{
private:
    bool file_exist;
    string filename;
    vector<diary> diaries;
    bool check();
    bool check(string filename_)
    {
        filename = filename_;
        return check();
    }
    int locate_date(date d);

public:
    data_base() { check(Default_filename); }
    data_base(string filename_)
    {
        filename = filename_;
        check();
    }
    bool init();
    // Status
    bool file_valid() { return file_exist; }
    // Manuplation
    void read();
    void write();
    bool add();
    bool remove(date);
    // Query
    void print() const;
    bool print(date start, date end) const;
    bool print_before(date) const;
    bool print_after(date) const;
};