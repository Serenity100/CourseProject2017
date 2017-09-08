#ifndef FILEPARSER_H
#define FILEPARSER_H
#include "avltree.h"
#include <fstream>
#include <list>

class FileParser
{
public:
    FileParser();

    // Создание словаря - AVL-дерева
    AvlTree<std::string>* createDictionary(std::string filename);

    // Найти слова в строке
    std::list<std::string> findWords(std::string line);

    // Найти ошибки в тексте. Результат: список ошибочных слов
    std::list<std::string> findMisspelledWords(std::string file_name, AvlTree<std::string> *dict);
};

#endif // FILEPARSER_H
