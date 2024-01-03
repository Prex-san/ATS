#include "ats.h"
#include <string>
#include <sstream>
#define MODIFYING_FACTOR 1

using namespace std;

void summarizer()
{
    string temp;
    fstream input;
    input.open("sentence_rank.txt", ios::in);
    vector<sentence_score> sentence_rank;
    sentence_score current_sentence;
    double sum = 0;
    int sentence_count = 0;
    while (getline(input, temp))
    {
        sentence_count++;
        stringstream s(temp);
        s >> current_sentence.sentence >> current_sentence.tf_idf;
        sum += current_sentence.tf_idf;
        sentence_rank.push_back(current_sentence);
    }
    double average = sum / sentence_count;
    average = average * MODIFYING_FACTOR; // MODIFYING FACTOR
    cout << average << endl;
    sentence_score temp_container;
    for (int i = 0; i < sentence_rank.size(); i++)
    {
        for (int j = i; j < sentence_rank.size(); j++)
        {
            if (i == j)
                continue;
            else if (sentence_rank.at(i).tf_idf < sentence_rank.at(j).tf_idf)
            {
                temp_container = sentence_rank.at(i);
                sentence_rank.at(i) = sentence_rank.at(j);
                sentence_rank.at(j) = temp_container;
            }
        }
    }
    input.close();
    input.open("sentences.txt", ios::in);
    vector<string> text;

    while (getline(input, temp))
    {
        if (temp.at(temp.length() - 1) == '$')
        {
            temp.at(temp.length() - 1) = '.';
        }
        text.push_back(temp);
    }
    input.close();

    fstream output;
    output.open("summary.txt", ios::out | ios::trunc);
    for (int i = 0; i < sentence_rank.size(); i++)
    {
        if (sentence_rank.at(i).tf_idf > average)
        {
            output << text.at(sentence_rank.at(i).sentence - 1) << endl;
        }
    }
}