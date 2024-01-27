#ifndef MYLIST_H
#define MYLIST_H

#include <QDebug>

template <typename T>
class MyList{

    class Node{
    public:
        T _data;
        Node* _next;
        Node(){
            _data = 0;
            _next = nullptr;
        }
        Node(T data) : _data(data), _next(nullptr) {};
    };

    Node* first;
    Node* last;
    int len;

public:

    MyList() : first(nullptr), last(nullptr), len(0) {}

    int get_len() const { return len; }

    bool is_empty() const
    {
        if (first == nullptr)
            return true;
        else return false;
    }

    bool push_back(T data){
        Node *n = new Node(data);
        if (this->is_empty()){
            first = n;
            last = n;
            ++len;
            return true;
        }
        else{
            last->_next = n;
            last = n;
            ++len;
            return true;
        }
        return false;
    }

    bool pop_back()
    {
        if(this->is_empty())
        {
            qDebug() << "Mylist.pop_back::List is empty\n";
            return false;
        }
        if(last == first)
        {
            delete first;
            last = nullptr;
            first = nullptr;
            --len;
            return true;
        }
        else{
            Node *curr = first;
            while(curr->_next != last)
            {
                curr = curr->_next;
            }
            last = curr;
            delete curr->_next;
            --len;
            return true;
        }
    }

    void print_list() const
    {
        Node* curr = first;
        if(is_empty())
        {
            qDebug() << "Mylist.printlist::List is empty!\n";
            return;
        }
        while(curr != nullptr)
        {
            qDebug() << curr->_data;
            curr = curr->_next;
        }
        qDebug() <<"\n";
    }

    Node* find(const T val) const
    {
        Node* curr = first;

        if (!this->is_empty())
        {
            while(curr!=last && curr->_data != val)
            {
                curr = curr->_next;
            }
            if(curr->_data == val)
                return curr;
        }
        qDebug() << "Mylist.find::List is empty or not found";
        return nullptr;
    }

    bool pop_front()
    {
        Node *curr = first;
        if(is_empty()) return false;
        if (!curr->_next)
        {
            delete first;
            first = nullptr;
            last = nullptr;
        }
        else{
            curr = curr->_next;
            delete first;
            first = curr;
        }
        --len;
        return true;
    }

    void push_front(const T val)
    {
        Node* n = new Node(val);
        if(is_empty())
        {
            first = n;
            last = n;
        }
        else{
            n->_next = first;
            first = n;
        }
        ++len;

    }

    Node* operator[] (const int indx) const
    {
        Node* curr = first;
        int i = 0;
        if(indx >= len or indx < 0)
        {
            qDebug() << "Mylist.operator[]::Out of range";
            return nullptr;
        }
        while(i < indx)
        {
            curr= curr->_next;
            ++i;
        }
        return curr;
    }

    void print_node(const Node* n) const
    {
        qDebug() << n->_data;
    }

    void delete_list()
    {
        while(pop_front());
        len = 0;
    }

    bool insert_into(const int indx, const T val)
    {

        if(is_empty())
        {
            push_front(val);
            return true;
        }
        if(indx > len)
        {
            qDebug() << "Mylist.insert_into::Out of range";
            return false;
        }
        if(indx == len)
        {
            push_back(val);
            return true;
        }
        if(indx == 0)
        {
            push_front(val);
            return true;
        }
        Node* shift = first;
        Node* curr = first;
        int count = 0;
        while(count != indx)
        {
            shift = shift->_next;
            ++count;
        }
        while(curr->_next != shift)
        {
            curr = curr->_next;
        }

        curr->_next = new Node(val);
        curr = curr->_next;
        curr->_next = shift;
        ++len;

        return true;
    }

    bool remove(T val){
        Node* removed = this->find(val);
        Node* curr = first;

        if(!removed){
            return false;
        }

        while(curr->_next != removed)
        {
            curr = curr->_next;
        }
        curr->next = removed->_next;
        delete removed;
        --len;
        return true;
    }

    ~MyList()
    {
        delete_list();
    }

};

#endif // MYLIST_H
