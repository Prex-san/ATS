import spacy
import sys
nlp = spacy.load("en_core_web_sm")

textDoc = open("processedDoc.txt")
outputDoc = open("ner.txt", "w")
text = textDoc.read()
doc = nlp(text)
sys.stdout = outputDoc
for entity in doc.ents:
    print(entity.text, entity.label_)
