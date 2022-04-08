#include <pd.hpp>
int main(int argc, char const *argv[])
{
    if (argc != 2 && argc != 6)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        cout << "or" << endl;
        cout << "Usage: " << argv[0] << " <filename> <year month day> <year month day>" << endl;
        return -1;
    }
    string filename = argv[1];
    data_base db(filename);
    if (!db.file_valid())
    {
        cout << "Open file <" << filename << "> failed!" << endl;
        return -1;
    }
    db.read();
    if (argc == 2)
        db.print();
    else
    {
        date start, end;
        bool valid = start.set_day(string(argv[2]) + " " + string(argv[3]) + " " + string(argv[4]));
        valid = valid && end.set_day(string(argv[5]) + " " + string(argv[6]) + " " + string(argv[7]));
        if (!valid)
            cout << "Invalid date!" << endl;
        else if (!db.print(start, end))
            cout << "Not found!" << endl;
    }
}