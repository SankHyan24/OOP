#include <pd.hpp>
#include <iomanip>
int main(int argc, char const *argv[])
{
    if (argc != 2 && argc != 1)
    {
        cout << "Usage: " << argv[0] << setw(10) << " "
             << " to create a new file" << endl;
        cout << "Usage: " << argv[0] << setw(10) << " <filename>"
             << " to use this file" << endl;
        return -1;
    }
    if (argc == 1)
    {
        data_base db(Default_filename);
        if (db.init())
            cout << "New Diary created!" << endl;
        else
            cout << "Failed to create new Diary!" << endl;
        return 0;
    }
    string filename = argv[1];
    data_base db(filename);
    if (!db.file_valid())
    {
        cout << "Open file <" << filename << "> failed!" << endl;
        return -1;
    }
    db.read();
    if (db.add())
    {
        db.write();
        cout << "Done" << endl;
    }
}
