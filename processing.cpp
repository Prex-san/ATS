#include "ats.h"
#include <string>

using namespace std;

void processing()
{
    string temp;
    vector<string> pos{"the", "a", "an", "of", "and", "&", "as", "her", "his", "him", "they", "their"};
    fstream tokens;
    tokens.open("tokens.txt", ios::in);
    fstream output;
    output.open("processedDoc.txt", ios::out | ios::trunc);
    int term_count = 0;
    while (!tokens.eof())
    {
        int i;
        getline(tokens, temp);
        for (i = 0; i < pos.size(); i++)
        {
            if (temp.compare(pos.at(i)) == 0)
            {
                break;
            }
        }
        if (i == pos.size())
        {
            output << temp << endl;
        }
    }
}