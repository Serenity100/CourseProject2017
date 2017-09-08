#include "fileparser.h"

using namespace std;

FileParser::FileParser()
{

}

AvlTree<string>* FileParser::createDictionary(string file_name)
{
    string word;
    AvlTree<string>* dictTree = new AvlTree<string>;

    // Открываем файл для чтения
    ifstream in_file;
    in_file.open(file_name, ios::in);

    if (in_file.fail()) {
        cerr << "Couldn't open the file";
        exit(1);
    }

    // Добавляем по слову в словарь
    while(!in_file.eof())
    {
        in_file >> word;

        dictTree->addNode(word);
    }

    in_file.close();

    return dictTree;
}

list<string> FileParser::findWords(string line)
{
    string current_word;
    list<string> word_list;
    int counter = 1;

    for (char letter: line)
    {
        if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) {
            current_word += letter;

            // Когда конец строки
            if (counter == line.size())
                word_list.push_back(current_word);
        }
        else if (!current_word.empty())
            // Добавляем слово в список и очищаем переменную с текущим словом
            word_list.push_back(current_word), current_word.clear();

        ++counter;
    }

    return word_list;
}

list<string> FileParser::findMisspelledWords(string file_name, AvlTree<string> *dict)
{
    list<string> misspelledWords;
    list<string> lineWords;
    string line;

    // Открываем текст для чтения
    ifstream in_file;
    in_file.open(file_name, ios::in);

    if (in_file.fail()) {
        cerr << "Couldn't open the file";
        exit(1);
    }

    while(!in_file.eof())
    {
        in_file >> line;
        lineWords = findWords(line);

        // Ищем каждое слово в словаре
        for (auto each_word : lineWords) {

            if (!dict->search(each_word))
                misspelledWords.push_back(each_word);
        }
    }

    in_file.close();
    return misspelledWords;
}
