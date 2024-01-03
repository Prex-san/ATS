#include "ats.h"

using namespace std;
int main()
{
    fstream document;
    FILE *ner;

    document.open("text.txt", ios::in);
    int sentence_count = tokenizer(document);
    // processing();
    tf_idf(sentence_count);
    document.close();
    summarizer();
}