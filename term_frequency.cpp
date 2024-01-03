#include "ats.h"
#include <string>
#include <cmath>
using namespace std;
void tf_idf(int sentence_count)
{
    int total_words = 0;
    fstream input;
    input.open("sentences.txt", ios::in);
    string temp;
    struct word_count
    {
        string word;
        int count = 0;
        double TF = 0;
        double tf_idf = 0;
    };
    struct word_count_df
    {
        string word;
        bool alreadyVisited = false;
        int DF = 0;
        double IDF = 0;
    };

    vector<vector<word_count>> freq_dict;
    vector<word_count_df> doc_freq_dict;
    vector<sentence_score> sentence_rank;
    freq_dict.resize(sentence_count);
    int cur_sentence = 0;
    while (getline(input, temp))
    {
        string cur_word;
        word_count cur_word_freq;
        word_count_df cur_word_df;
        int sentence_word_count = 0;
        // TF
        for (int i = 0; i < temp.length(); i++)
        {
            if (temp.at(i) == ',' || temp.at(i) == ';')
            {
                continue;
            }
            else if (temp.at(i) == ' ' || temp.at(i) == '$')
            {
                sentence_word_count++;
                if (freq_dict.at(cur_sentence).size() == 0)
                {
                    cur_word_freq.word = cur_word;
                    cur_word_freq.count = 1;
                    freq_dict.at(cur_sentence).push_back(cur_word_freq);
                    cur_word.clear();
                }
                else
                {
                    int j;
                    for (j = 0; j < freq_dict.at(cur_sentence).size(); j++)
                    {
                        if (cur_word == freq_dict.at(cur_sentence).at(j).word)
                        {
                            freq_dict.at(cur_sentence).at(j).count++;
                            cur_word.clear();
                            break;
                        }
                    }
                    if (j == freq_dict.at(cur_sentence).size())
                    {
                        cur_word_freq.word = cur_word;
                        cur_word_freq.count = 1;
                        freq_dict.at(cur_sentence).push_back(cur_word_freq);
                        cur_word.clear();
                    }
                }
            }
            else
            {
                cur_word.push_back(temp.at(i));
            }
        }
        for (int i = 0; i < freq_dict.at(cur_sentence).size(); i++)
        {
            freq_dict.at(cur_sentence).at(i).TF = (double)freq_dict.at(cur_sentence).at(i).count / sentence_word_count;
        }
        // IDF
        for (int i = 0; i < temp.length(); i++)
        {
            if (temp.at(i) == ',' || temp.at(i) == ';')
            {
                continue;
            }
            else if (temp.at(i) == ' ' || temp.at(i) == '$')
            {
                if (doc_freq_dict.size() == 0)
                {
                    cur_word_df.word = cur_word;
                    cur_word_df.DF = 1;
                    cur_word_df.alreadyVisited = true;
                    doc_freq_dict.push_back(cur_word_df);
                    cur_word.clear();
                }
                else
                {
                    int j;
                    for (j = 0; j < doc_freq_dict.size(); j++)
                    {
                        if (cur_word == doc_freq_dict.at(j).word)
                        {
                            if (!doc_freq_dict.at(j).alreadyVisited)
                            {
                                cur_word.clear();
                                doc_freq_dict.at(j).alreadyVisited = true;
                                doc_freq_dict.at(j).DF++;
                                break;
                            }
                            else
                            {
                                cur_word.clear();
                                break;
                            }
                        }
                    }
                    if (j == doc_freq_dict.size())
                    {
                        cur_word_df.word = cur_word;
                        cur_word_df.DF = 1;
                        cur_word_df.alreadyVisited = true;
                        doc_freq_dict.push_back(cur_word_df);
                        cur_word.clear();
                    }
                }
            }
            else
            {
                cur_word.push_back(temp.at(i));
            }
        }
        for (int i = 0; i < doc_freq_dict.size(); i++)
        {
            doc_freq_dict.at(i).alreadyVisited = false;
            // Calculate IDF
            doc_freq_dict.at(i).IDF = log((double)sentence_count / doc_freq_dict.at(i).DF);
        }
        cur_sentence++;
    }
    // Calculate TF-IDF
    for (int i = 0; i < freq_dict.size(); i++)
    {
        double sum = 0;
        for (int j = 0; j < freq_dict.at(i).size(); j++)
        {
            double idf = 0;
            for (int k = 0; k < doc_freq_dict.size(); k++)
            {
                if (freq_dict.at(i).at(j).word == doc_freq_dict.at(k).word)
                {
                    idf = doc_freq_dict.at(k).IDF;
                    break;
                }
            }
            freq_dict.at(i).at(j).tf_idf = freq_dict.at(i).at(j).TF * idf;
            sum += freq_dict.at(i).at(j).tf_idf;
        }
        sentence_score current_sentence;
        current_sentence.sentence = i + 1;
        current_sentence.tf_idf = sum;
        sentence_rank.push_back(current_sentence);
    }
    fstream output;
    output.open("term_frequency.txt", ios::trunc | ios::out);
    for (int i = 0; i < freq_dict.size(); i++)
    {
        output << "\n\nSentence " << i + 1 << ":\n"
               << endl;
        for (int j = 0; j < freq_dict.at(i).size(); j++)
        {
            output << freq_dict.at(i).at(j).word << " " << freq_dict.at(i).at(j).count << " " << freq_dict.at(i).at(j).TF << endl;
        }
    }
    fstream output2;
    output2.open("document_frequency.txt", ios::out | ios::trunc);
    for (int i = 0; i < doc_freq_dict.size(); i++)
    {
        output2 << doc_freq_dict.at(i).word << " " << doc_freq_dict.at(i).DF << " " << doc_freq_dict.at(i).IDF << endl;
    }
    fstream output3;
    output3.open("sentence_rank.txt", ios::out | ios::trunc);
    for (int i = 0; i < sentence_rank.size(); i++)
    {
        output3 << sentence_rank.at(i).sentence << " " << sentence_rank.at(i).tf_idf << endl;
    }

    input.close();
    output.close();
    output2.close();
    output3.close();
}
