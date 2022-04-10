#pragma once
#include <iostream>
#include <vector>
using namespace std;
const string Default_filename = "pd.txt";
// Date Class
// Date class is used to store the date and the related functions
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
    date();                        // 设置日期，默认是今天
    date(int d, int m, int y);     // 通过int设置日期
    date(string s) { set_day(s); } // 通过字符串设置日期
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
    bool set_day();       // 外界调用从cin输入日期的接口
    bool set_day(string); // 外界调用从字符串输入日期的接口
};

// Diary Class
// Diary class is used to store the diary and the related functions
class diary
{
private:
    date this_day; // 存储日记所属的日期
    string text;   // 存储日记的内容

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

// Diary_book Class
// Diary_book class is used to store the diary_book and the related functions
class data_base
{
private:
    bool file_exist;             // 外部程序调用时，判断文件是否存在的flag
    string filename;             // 对应外部文件的文件名
    vector<diary> diaries;       // 存储日记的vector
    bool check();                // 检查外部文件是否存在
    bool check(string filename_) // 重设外部文件并检查
    {
        filename = filename_;
        return check();
    }
    int locate_date(date d); // 返回指定日期的位置

public:
    data_base() { check(Default_filename); }
    data_base(string filename_)
    {
        filename = filename_;
        check();
    }
    bool init(); //没有文件名，则创建文件
    // Status
    bool file_valid() { return file_exist; }
    // Manuplation
    void read();       // 从文件中读取日记到内存
    void write();      // 从内存中向文件中写入日记
    bool add();        // 增加内存中的日记记录，包括了日期覆盖逻辑
    bool remove(date); // 删除特定日期的日记
    // Query
    void print() const;                     // 全部日记的输出
    bool print(date start, date end) const; // 指定日期范围内的日记的输出
    bool print_before(date) const;          // 指定日期之前的日记的输出
    bool print_after(date) const;           // 指定日期之后的日记的输出
};