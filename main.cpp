#include <bits/stdc++.h>
using namespace std;

template <typename T>
class LinkedList
{
public:

    class Node
    {   
        int row;
        int collumn;
        int value;
        Node* next;
        Node* prev;

    public:
        Node(int row, int collumn, int value, Node* next = nullptr, Node* prev = nullptr)
        {
            this->row = row;
            this->collumn = collumn;
            this->value = value;
            this->next = next;
            this->prev = prev;
        }

        void setNext(Node* next) {this->next = next;}
        void setPrev(Node* prev) {this->prev = prev;}
        void setRow(int row) {this->row = row;}
        void setCollumn(int collumn) {this->collumn = collumn;}
        void setValue(int value) {this->value = value;}
        Node* getNext() {return this->next;}
        Node* getPrev() {return this->prev;}
        int getRow() {return this->row;}
        int getCollumn() {return this->collumn;}
        int getValue() {return this->value;}
    };
    
    Node* header;
    Node* tailer;
    int size;

    LinkedList()
    {
        header = new Node(-1, -1, 100);
        tailer = new Node(-1, -1, 100);
        header->setNext(tailer);
        tailer->setPrev(header);
        size = 0;
    }

    void setSize(int size) {this->size = size;}
    void increamentSize() {this->size++;}
    void decreamentSize() {this->size--;}
    Node* getHeader() {return this->header;}
    Node* getTailer() {return this->tailer;}
    int getSize() {return this->size;}

    void remove(Node* node)
    {
        node->getPrev()->setNext(node->getNext());
        node->getNext()->setPrev(node->getPrev());
        delete node;
        decreamentSize();
    }
    void add(Node* newNode, Node* prev, Node* next)
    {
        newNode->setNext(next);
        newNode->setPrev(prev);
        prev->setNext(newNode);
        next->setPrev(newNode);
        increamentSize();
    }

    void addToRow(Node* newNode, int j)
    {
        Node* t = this->getHeader()->getNext();

        while (t != this->getTailer())
        {
            if(t->getCollumn() < j) t = t->getNext();
            else break;
        }

        add(newNode, t->getPrev(), t);
    }

    void addToCollumn(Node* newNode, int i)
    {
        Node* t = this->getHeader()->getNext();

        while (t != this->getTailer())
        {
            if(t->getRow() < i) t = t->getNext();
            else break;
        }

        add(newNode, t->getPrev(), t);
    }

};


int main()
{
    
    return 0;
}
