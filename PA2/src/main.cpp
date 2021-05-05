#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include "planar.h"

using namespace std;

void help_message()
{
    cout << "usage: mps <input_file> <output_file>" << endl;
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        cout << "Invalid arg count: " << argc << endl;

        help_message();
        return 0;
    }

    //////////// read the input file /////////////

    char buffer[200];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);

    int start, end;
    map<int, int> data;

    int vertices;

    fin >> vertices;
    fin.getline(buffer, 200);

    while (fin >> start >> end)
    {
        if (start < end)
        {
            data[end] = start;
        }
        else if (start > end)
        {
            data[start] = end;
        }
    }

    //////////// the MPS part ////////////////
    Planar planar = Planar(vertices, data);
    planar.MPS(0, vertices - 1);
    map<int, int> mps = planar.maxChords;

    // //////////// write the output file ///////////
    fout << mps.size() << endl;

    map<int, int>::iterator iter;
    for (iter = mps.begin(); iter != mps.end(); iter++)
    {
        fout << iter->second << " " << iter->first << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
