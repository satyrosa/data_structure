#include <QDebug>
//
template <typename T>
class BinaryTree{
    class TNode{
    public:
        T _data;
        TNode* _right;
        TNode* _left;

        TNode(T val) : _data(val), _right(nullptr), _left(nullptr){}
    };

    TNode* root;
//Внутренний метод вставки.
    bool insert(T const val, TNode* const n)
    {
        if(!n)
        {
            qDebug() << "BinaryTree.private_insert:: current pointer is null";
            return false;
        }
        if(val >= n->_data)
            if(n->_right)
                insert(val, n->_right);
            else{
                n->_right = new TNode(val);

            }
        else
            if(n->_left)
                insert(val, n->_left);
            else{
                n->_left = new TNode(val);

            }

        return true;

    }
//Внутренний метод печати дерева. Рекурсивно печатаем по одному узлу обходом вглубь
    void print_node(TNode* const n) const
    {
        qDebug() << n->_data;
        if(n->_left)
            print_node(n->_left);
        if(n->_right)
            print_node(n->_right);
    }
//Внутренний метод поиска элемента
    TNode* find(int const val, TNode* curr)
    {
        if(curr->_data == val)
            return curr;
        if(val < curr->_data && curr->_left)
            return find(val, curr->_left);
        if(val > curr->_data && curr->_right)
            return find(val, curr->_right);
        return nullptr;
    }
//Проверка, есть ли у узла потомки
    bool is_leaf(TNode* const n) const{
        if(!n->_left && !n->_right)
            return true;
        return false;
    }
//Метод поиска родителя узла. Делаем вид, что ищем узел, но возвращаем предыдущий от него
    TNode* find_parent(TNode* const n, TNode* const curr) const
    {
        if(curr->_left == n || curr->_right == n)
            return curr;
        if(n->_data > curr->_data)
            return find_parent(n, curr->_right);
        if(n->_data < curr->_data)
            return find_parent(n, curr->_left);

    }
//Поиск минимума в дереве или поддереве
    TNode* find_min(TNode* curr)
    {
        while(curr->_left)
        {
            curr = curr->_left;
        }

        return curr;
    }

public:

    BinaryTree() : root(nullptr){}
//Проверка на непустоту
    bool is_empty() const
    {
        if(root == nullptr)
            return true;
        return false;
    }
//Метод печати
    void print_tree() const
    {
        print_node(root);
    }
//Метод поиска узла
    TNode* find(T const val) const
    {
        TNode* curr = root;

        find(val, root);
        if(!curr)
        {
            qDebug() << "BinaryTree.find :: Element not found";
            return nullptr;
        }
        return curr;
    }
//Метод вставки
    bool insert(T const val){
        if(is_empty())
        {
            root = new TNode(val);

            return true;
        }
        insert(val, root);

        return true;
    }
//Метод удаления
    bool remove(T const val)
    {
        TNode* to_del = find(val, root);
//Проверка на существование удаляемого узла
        if(!to_del)
        {
            qDebug() << "BinaryTree.remove::ELement not found";
            return false;
        }
//Случай, когда удаляется лист дерева
        if(is_leaf(to_del))
        {
            TNode* parent = find_parent(to_del, root);
            if(to_del->_data >= parent->_data)
                parent->_right = nullptr;
            else
                parent->_left = nullptr;
            delete to_del;


            return true;
        }
//Случай, когда у удаляемого узла только левый лист в потомках
        if(is_leaf(to_del->_left) && !to_del->_right)
        {
            to_del->_data = to_del->_left->_data;
            delete to_del->_left;
            to_del->_left = nullptr;

            return true;
        }
//или правый
        if(is_leaf(to_del->_right) && !to_del->_left)
        {
            to_del->_data = to_del->_right->_data;
            delete to_del->_right;
            to_del->_right = nullptr;

            return true;
        }
//Случай, если у узла есть только правая ветка
        if(!to_del->_right)
        {
            TNode* parent = find_parent(to_del, root);

            parent->_left = to_del->_left;
            delete to_del;

            return true;
        }
//или левая
        if(!to_del->_left)
        {
            TNode* parent = find_parent(to_del, root);

            parent->_right = to_del->_right;
            delete to_del;

            return true;
        }
//Случай, когда узел является родителем полноценного поддерева
        if(to_del->_left && to_del->_right){
            TNode* min_elem = find_min(to_del->_right);
            TNode* parent = find_parent(min_elem, root);

            to_del->_data = min_elem->_data;

            if(min_elem->_data >= parent->_data)
                parent->_right = nullptr;
            else
                parent->_left = nullptr;
            delete min_elem;

            return true;

        }
    }

};
