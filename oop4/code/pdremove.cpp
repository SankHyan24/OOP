// pdremove removes one entity of the date.It returns 0 on success and -1 on failure.
#include <pd.hpp>
int main(int argc, char const *argv[])
{
    if (argc != 5)
    {
        cout << "Usage: " << argv[0] << " <filename> <year month day>" << endl;
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
    date to_be_removed;
    if (!to_be_removed.set_day(string(argv[2]) + " " + string(argv[3]) + " " + string(argv[4])))
    {
        cout << "Invalid date!" << endl;
        return -1;
    }
    if (!db.remove(to_be_removed))
        return -1;
}