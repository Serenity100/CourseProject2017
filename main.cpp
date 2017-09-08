#include <iostream>
#include "avltree.h"
#include "fileparser.h"

using namespace std;

void fileTestMenu();
void testAvlTree();

int main()
{
    char choice;
    cout << "1. Test program\n"
         << "2. Test AvlTree class\n" << endl;
    cout << "choice: ";cin >> choice;

    switch (choice)
    {
    case '1':
        fileTestMenu();
        break;
    case '2':
        testAvlTree();
        break;
    default:
        cout << "Incorrect input...\n";
        break;
    }

    return 0;
}

void fileTestMenu()
{
    string dict_file_name, text_file_name;
    AvlTree<string> *dict;
    list<string> misspelled_words;
    FileParser pars;

    cout << "Input dictionary name: ";
    cin.ignore();
    getline(cin, dict_file_name);

    dict = pars.createDictionary(dict_file_name + ".txt"); // Составили словарь

    cout << "Input text name: ";
    getline(cin, text_file_name);

    misspelled_words = pars.findMisspelledWords(text_file_name + ".txt", dict); // Нашли несовпадающие слова

    if (misspelled_words.empty())
        cout << "\nNo misspelled words...\n";
    else {
        cout << "Misspelled words: ";

        for (auto each: misspelled_words)
            cout << each << " ";
    }

    cout << endl;

    //dict->print();
}

void testAvlTree()
{
    AvlTree<int> test_tree;
    char choice;
    int node;

    do
    {
        cout << "1. Insert node\n"
             << "2. Search node\n"
             << "3. Delete node\n"
             << "4. Print tree\n"
             << "5. Exit\n" << endl;
        cout << "choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            cout << "\nnode: "; cin >> node;
            test_tree.addNode(node);
            break;
        case '2':
            cout << "\nnode: "; cin >> node;
            if (test_tree.search(node))
                cout << "yes" << endl;
            else
                cout << "no" << endl;
            break;
        case '3':
            cout << "\nnode: "; cin >> node;
            test_tree.deleteNodeFromTree(node);
            break;
        case '4':
            cout << endl;
            test_tree.print();
            break;
        case '5':
            break;
        default:
            cout << "Incorrect input...\n";
            break;
        }

        cout << endl;

    } while (choice != '5');
}
