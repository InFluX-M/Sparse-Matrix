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
        Node* nextRow;
        Node* nextCollumn;

    public:
        Node(int row, int collumn, int value, Node* nextRow = nullptr, Node* nextCollumn = nullptr)
        {
            this->row = row;
            this->collumn = collumn;
            this->value = value;
            this->nextRow = nextRow;
            this->nextCollumn = nextCollumn;
        }

        void setNextRow(Node* nextRow) {this->nextRow = nextRow;}
        void setNextCollumn(Node* nextCollumn) {this->nextCollumn = nextCollumn;}
        void setRow(int row) {this->row = row;}
        void setCollumn(int collumn) {this->collumn = collumn;}
        void setValue(int value) {this->value = value;}
        Node* getNextRow() {return nextRow;}
        Node* getNextCollumn() {return nextCollumn;}
        int getRow() {return this->row;}
        int getCollumn() {return this->collumn;}
        int getValue() {return this->value;}
    };
    
    Node* header;
    Node* tailer;
    int size;

    LinkedList()
    {
        header = new Node(100, 100, 100);
        tailer = new Node(100, 100, 100);
        if(statue)
        {
            header->setNextCollumn(tailer);
        }
        else
        {
            header->setNextRow(tailer);
        }
        size = 0;
    }

    void setSize(int size) {this->size = size;}
    void increamentSize() {this->size++;}
    void decreamentSize() {this->size--;}
    Node* getHeader() {return this->header;}
    Node* getTailer() {return this->tailer;}
    int getSize() {return this->size;}

    void removeInRow(Node* prev, Node* node)
    {
        prev->nextCollumn(node->nextCollumn);
        delete node;
        decreamentSize();
    }
    void removeInCollumn(Node* prev, Node* node)
    {
        prev->nextRow(node->nextRow);
        delete node;
        decreamentSize();
    }

    void addToRow(Node* newNode, int j)
    {
        Node* t = this->getHeader()->getNextCollumn();
        Node* prev = this->getHeader();

        while (t != this->getTailer())
        {
            if(t->getCollumn() < j)
            {
                t = t->getNextCollumn();
                prev = prev->getNextCollumn();
            } 
            else break;
        }

        newNode->setNextCollumn(t);
        prev->setNextCollumn(newNode);
        increamentSize();
    }

    void addToCollumn(Node* newNode, int i)
    {
        Node* t = this->getHeader()->getNextRow();
        Node* prev = this->getHeader();
        while (t != this->getTailer())
        {
            if(t->getRow() < i)
            {
                t = t->getNextRow();
                prev = prev->getNextRow();
            } 
            else
            {
                break;
            }
        }

        newNode->setNextRow(t);
        prev->setNextRow(newNode);
        increamentSize();
    }

};


void read(LinkedList<int> Row[], LinkedList<int> Collumn[], string pathCSV)
{
    ifstream fin;
    string line;
    int i=0;
    fin.open(pathCSV);
    while(i<10)
    {
        fin>>line;
        stringstream s(line);
        string T;
        int j=0;

        while(j<5 && getline(s, T, ','))
        {
            int num = stoi(T);
            if(num != 0)
            {   
                LinkedList<int>::Node* newNode = new LinkedList<int>::Node(i, j, num);
                Row[i].addToRow(newNode, j);
                Collumn[j].addToCollumn(newNode, i);
            }
            j++;
        }
        i++;
    }
}

int main()
{
    
}
