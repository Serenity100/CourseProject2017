#ifndef TREENODE_H
#define TREENODE_H


template <typename T>
class AvlTree;


template <typename T>
class TreeNode
{
    friend class AvlTree<T>;
    T value;          // Значение узла
protected:
    TreeNode* left;   // Левый сын
    TreeNode* right;  // Правый сын
public:
    // Инициализирующий конструктор с параметром по умолчанию
    TreeNode(T new_value = 0) : left(nullptr), right(nullptr), value(new_value){}
};
#endif // TREENODE_H
