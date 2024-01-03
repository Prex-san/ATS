#include <fstream>
#include <iostream>
#include <vector>

int tokenizer(std::fstream &);
void processing();
struct sentence_score
{
    double tf_idf;
    int sentence = 0;
};
void tf_idf(int sentence_count);
void summarizer();
