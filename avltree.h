#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <treenode.h>
#include <string>

// Класс-шаблон AVL дерева
template <typename T>
class AvlTree
{
protected:
    TreeNode<T>* root;                      // Указатель на корень

    // ВЫВОД ДЕРЕВА В КОНСОЛЬ
    void writeTab(int);                     // Сделать необходимую табуляцию
    void map(TreeNode<T>*, int);            // Напечатать дерево

    // ВСПОМОГАТЕЛЬНЫЕ
    bool isLeaf(TreeNode<T>* node) {        // Является ли листом
        if((node->left == nullptr) && (node->right == nullptr))
            return true;
        return false;
    }
    int max(int first, int second) {        // Максимальное из двух чисел
        return (first > second)? first : second;
    }
    int computeHeight(TreeNode<T>* node) {  // Вернуть высоту поддерева узла-аргумента
        if (node == nullptr)
            return -1;

        return 1 + max(computeHeight(node->left), computeHeight(node->right));
    }
    int getBalance(TreeNode<T> *node)       // Разница между высотами сыновей
    {
        if (node == nullptr)
            return 0;
        return computeHeight(node->left) - computeHeight(node->right);
    }

    // УДАЛЕНИЕ
    TreeNode<T>* minValueNode(TreeNode<T>* node);      // Наименьший узел в заданном поддереве
    TreeNode<T>* deleteNode(TreeNode<T> *root, T key); // Рекурсивное удаление узла в поддереве

    // ВСТАВКА УЗЛА + РОТАЦИИ
    TreeNode<T>* insertNode (TreeNode<T>* node, T key);
    TreeNode<T>* rightRotate(TreeNode<T>* y);
    TreeNode<T>* leftRotate (TreeNode<T>* x);

    // РЕКУРСИВНОЕ УДАЛЕНИЕ ПОДДЕРЕВА
    void destroyRecursively(TreeNode<T>*);

public:
    AvlTree() : root(nullptr) {}                          // Конструктор
    ~AvlTree() { destroyRecursively(root); }              // Деструктор

    TreeNode<T>* getRoot() { return root; }               // Вернуть корень
    void addNode(T val) { root = insertNode(root, val); } // Новый узел
    void deleteNodeFromTree(T key) {                      // Удалить узел из дерева
        root = deleteNode(root, key);
    }
    int height() { return computeHeight(root); }          // Вернуть высоту дерева
    void print() { map(root, 0); }                        // Напечатать дерево растущим вправо
    void printPreorder(TreeNode<T>* node);                // Напечатать узлы прямым обходом
    bool search(T key);                                   // Поиск ключа в дереве
    bool empty() {                                        // Пусто ли дерево
        return (root == nullptr)? true : false;
    }
};

#endif // AVLTREE_H
