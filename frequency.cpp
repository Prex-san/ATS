#include "ats.h"
#include <vector>
#include <string>
#include <cstring>

using namespace std;
void term_frequency()
{
    fstream tokens;
    tokens.open("processedDoc.txt", ios::in);
    string temp;
    typedef struct count
    {
        string term;
        int count = 0;
    } count;
    int term_count = 0;
    vector<count> counter;
    bool f = false;
    while (getline(tokens, temp))
    {
        count current;
        if (counter.size() == 0)
        {
            current.term = temp;
            current.count = 1;
            term_count++;
            f = true;
        }
        else
        {
            for (int i = 0; i < counter.size(); i++)
            {
                if (temp.compare(counter.at(i).term) == 0)
                {
                    counter.at(i).count++;
                    f = false;
                }
                else
                {
                    current.term = temp;
                    current.count = 1;
                    term_count++;
                    f = true;
                }
            }
        }
        if (f)
        {
            counter.push_back(current);
        }
    }
    fstream output;
    output.open("term_frequency.txt", ios::out | ios::trunc);
    output << "Total terms: " << term_count << endl;
    for (int i = 0; i < counter.size(); i++)
    {
        output << "Term: " << counter.at(i).term << "\t Freq: " << counter.at(i).count << endl;
    }
}
