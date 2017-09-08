#include "avltree.h"

template <typename T>
void AvlTree<T>::destroyRecursively(TreeNode<T>* node) {
    if (node == root && node == nullptr)
    {
        delete node;
        return;
    }

    if (!isLeaf(node))
    {
        // Вызываем деструкторы для потомков
        if (node->left != nullptr)
            destroyRecursively(node->left);

        if (node->right != nullptr)
            destroyRecursively(node->right);
    }
    delete node;
}

template <typename T>
void AvlTree<T>::writeTab(int d)
{
    if (d == 0)
        return;

    std::cout << "\t";
    writeTab(d - 1);
}

template <typename T>
void AvlTree<T>::map(TreeNode<T>* node, int d)
{
    if (node == nullptr)
        return;

    map(node->right, d + 1);
    writeTab(d);
    std::cout << node->value << std::endl;
    map(node->left, d + 1);
}

// Рекурсивная функция вставки нового узла
// Возвращает новый корень поддерева
template <typename T>
TreeNode<T>* AvlTree<T>::insertNode(TreeNode<T>* node, T key)
{
    TreeNode<T> *temp = new TreeNode<T>(key);
    // Обычная вставка как в бинарном дереве
    if (node == NULL)
        return temp;


    if (key < node->value)
        node->left  = insertNode(node->left, key);
    else if (key > node->value)
        node->right = insertNode(node->right, key);
    else // В бинарном дереве должны быть уникальные значения
        return node;

    // Определяем, стало ли дерево несбалансированным
    int balance = getBalance(node);

    // Если да, то будут 4 случая

    // Левое левое
    if (balance > 1 && key < node->left->value)
        return rightRotate(node);

    // Правое правое
    if (balance < -1 && key > node->right->value)
        return leftRotate(node);

    // Левое правое
    if (balance > 1 && key > node->left->value)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Правое левое
    if (balance < -1 && key < node->right->value)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* Возвращаем неизмененный указатель на node */
    return node;
}

// Правая ротация поддерева с корнем y
template <typename T>
TreeNode<T>* AvlTree<T>::rightRotate(TreeNode<T>* y)
{
    TreeNode<T> *x  = y->left;
    TreeNode<T> *T2 = x->right;

    // Ротация
    x->right = y;
    y->left = T2;

    // Возвращаем новый корень
    return x;
}

// Левая ротация поддерева с корнем x
template <typename T>
TreeNode<T>* AvlTree<T>::leftRotate(TreeNode<T>* x)
{
    TreeNode<T> *y = x->right;
    TreeNode<T> *T2 = y->left;

    // Ротация
    y->left = x;
    x->right = T2;

    // Возвращаем новый корень
    return y;
}

template <typename T>
void AvlTree<T>::printPreorder(TreeNode<T>* node) {
    if (node != nullptr)
    {
        std::cout << node->value << ", ";
        printPreorder(node->left);
        printPreorder(node->right);
    }
}

template <typename T>
bool AvlTree<T>::search(T key)
{
    if (!empty()) {
        TreeNode<T> *iter = root;

        while (iter != nullptr) {
            if (key == iter->value)
                return true;
            else
                if (key < iter->value)
                    iter = iter->left;
                else
                    iter = iter->right;
        }
    }

    return false;
}

template <typename T>
TreeNode<T>* AvlTree<T>::minValueNode(TreeNode<T>* node)
{
    TreeNode<T>* current = node;

    /* Ищем самый левый лист */
    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Рекурсивная функция удаления из поддерева корня-аргумента
// Возвращает корень измененного дерева
template <typename T>
TreeNode<T>* AvlTree<T>::deleteNode(TreeNode<T> *root, T key)
{
    // Обычное удаление как в бинарном дереве
    if (root == nullptr)
        return root;

    if (key < root->value)
        root->left = deleteNode(root->left, key);

    else if(key > root->value)
        root->right = deleteNode(root->right, key);

    // Найден удаляемый узел
    else
    {
        // Узел с одним потомков или вообще без них
        if( (root->left == nullptr) || (root->right == nullptr) )
        {
            TreeNode<T> *temp = root->left ? root->left : root->right;

            // Нет потомков
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else // Один потомок
             *root = *temp; // Copy the contents of
                            // the non-empty child
            delete temp;
        }
        else
        {
            // Узел с двумя потомками: Получаем прямого
            // потомка (наименьший в правом поддереве)
            TreeNode<T> *temp = minValueNode(root->right);

            // Копируем значение прямого наследника в корень
            root->value = temp->value;

            // Удаляем прямого наследника
            root->right = deleteNode(root->right, temp->value);
        }
    }

    // Если у дерева был только один узел
    if (root == NULL)
      return root;


    int balance = getBalance(root);

    // Балансируем как при операции вставки (смотрите выше)

    // Левый левый
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Левый правый
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Правый правый
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Правый левый
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


template class AvlTree<int>;
template class AvlTree<float>;
template class AvlTree<std::string>;





