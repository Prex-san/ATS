#include "ats.h"
#include <string>
#include <cstring>

using namespace std;
void sentence_to_tokens();
// int main()
// {
//     fstream text;
//     text.open("text.txt", ios::in);
//     tokenizer(text);
// }
int tokenizer(fstream &document)
{
    int sentence_count = 0;
    string temp;
    fstream output;
    output.open("sentences.txt", ios::out | ios::trunc);
    while (getline(document, temp))
    {
        bool f = false;
        int j;
        for (int i = 0; i < temp.length(); i++)
        {
            if (temp.at(i) == '.')
            {
                if (i == temp.length() - 1)
                {
                    temp.at(i) = '$';
                    output << temp.at(i) << endl;
                    sentence_count++;
                }
                else if (temp.at(i + 1) == ' ')
                {
                    if (isupper(temp.at(i - 1)) && temp.at(i - 2) == ' ')
                    {
                        output << temp.at(i);
                    }
                    else if (isupper(temp.at(i + 2)))
                    {
                        temp.at(i) = '$';
                        f = true;
                        output << temp.at(i) << endl;
                        sentence_count++;
                    }
                    else
                        output << temp.at(i);
                }
                else
                {
                    output << temp.at(i);
                }
            }
            else
            {
                if (!f)
                    output << temp.at(i);
                else
                    f = false;
            }
        }
    }
    output.close();
    sentence_to_tokens();
    cout << sentence_count << endl;
    return sentence_count;
}
void sentence_to_tokens()
{
    fstream output, sentences;
    vector<char> delim{' ', '!', '?', ',', '(', ')'};
    output.open("tokens.txt", ios::out | ios::trunc);
    string temp;
    sentences.open("sentences.txt", ios::in);
    while (getline(sentences, temp))
    {
        bool f = false;
        int j;
        for (int i = 0; i < temp.length(); i++)
        {
            if (temp.at(i) == '.' && temp.at(i + 1) == ' ')
            {
                output << temp.at(i);
                i++;
                continue;
            }
            if (temp.at(i) == '$')
            {
                output << endl;
                continue;
            }
            if (temp.at(i) == '"')
            {
                continue;
            }
            for (j = 0; j < delim.size(); j++)
            {
                if (temp.at(i) == delim.at(j) && !f)
                {
                    output << endl;
                    f = true;
                    break;
                }
                else if (temp.at(i) == delim.at(j) && f)
                {
                    break;
                }
            }
            if (j == delim.size())
            {
                if (isupper(temp.at(i)))
                {
                    char lower = tolower(temp.at(i));
                    output << lower;
                }
                else
                    output << temp.at(i);
                f = false;
            }
        }
    }
    output.close();
}
