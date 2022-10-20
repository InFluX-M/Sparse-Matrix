#include <bits/stdc++.h>
using namespace std;

bool statue;

template <typename T>
class Matrix
{
public:

    class Node
    {
    public:

        int row;
        int collumn;
        T value;
        Node *nextRow;
        Node *nextCollumn;

        Node(int row, int collumn, T value, Node *nextRow = nullptr, Node *nextCollumn = nullptr)
        {
            this->row = row;
            this->collumn = collumn;
            this->value = value;
            this->nextRow = nextRow;
            this->nextCollumn = nextCollumn;
        }

        void setNextRow(Node *nextRow) { this->nextRow = nextRow; }
        void setNextCollumn(Node *nextCollumn) { this->nextCollumn = nextCollumn; }
        void setRow(int row) { this->row = row; }
        void setCollumn(int collumn) { this->collumn = collumn; }
        void setValue(T value) { this->value = value; }
        Node *getNextRow() { return nextRow; }
        Node *getNextCollumn() { return nextCollumn; }
        int getRow() { return this->row; }
        int getCollumn() { return this->collumn; }
        T getValue() { return this->value; }
    };

    class LinkedList
    {
    public:
        Node *header;
        Node *tailer;
        int size;

        LinkedList()
        {
            header = new Node(100, 100, 100);
            tailer = new Node(100, 100, 100);
            if (statue)
            {
                header->setNextCollumn(tailer);
            }
            else
            {
                header->setNextRow(tailer);
            }
            size = 0;
        }

        void setSize(int size) { this->size = size; }
        void increamentSize() { this->size++; }
        void decreamentSize() { this->size--; }
        Node *getHeader() { return this->header; }
        Node *getTailer() { return this->tailer; }
        int getSize() { return this->size; }

        void removeInRow(Node *prev, Node *node)
        {
            prev->setNextCollumn(node->nextCollumn);
            decreamentSize();
        }

        void removeInCollumn(Node *prev, Node *node)
        {
            prev->setNextRow(node->nextRow);
            delete node;
            decreamentSize();
        }

        void addToRow(Node *newNode, int j)
        {
            Node *t = this->getHeader()->getNextCollumn();
            Node *prev = this->getHeader();

            while (t != this->getTailer())
            {
                if (t->getCollumn() < j)
                {
                    t = t->getNextCollumn();
                    prev = prev->getNextCollumn();
                }
                else
                    break;
            }

            newNode->setNextCollumn(t);
            prev->setNextCollumn(newNode);
            increamentSize();
        }

        void addToCollumn(Node *newNode, int i)
        {
            Node *t = this->getHeader()->getNextRow();
            Node *prev = this->getHeader();
            while (t != this->getTailer())
            {
                if (t->getRow() < i)
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

    int nRow;
    int nCollumn;
    LinkedList *Row;
    LinkedList *Collumn;

    Matrix(int nRow, int nCollumn)
    {
        this->nRow = nRow;
        this->nCollumn = nCollumn;
        statue = true;
        this->Row = new LinkedList[nRow];
        statue = false;
        this->Collumn = new LinkedList[nCollumn];
    }

    LinkedList getRow(int i) { return Row[i]; };
    LinkedList getCol(int j) { return Collumn[j]; };

    Node *accessNodeInRow(int i, int j)
    {
        Node *t = Row[i].getHeader();

        while (t->getNextCollumn() != Row[i].getTailer())
        {
            if (t->getNextCollumn()->getCollumn() == j)
                return t;
            t = t->getNextCollumn();
        }

        return nullptr;
    }
    Node *accessNodeInCollumn(int i, int j)
    {
        Node *t = Collumn[j].getHeader();

        while (t->getNextRow() != Collumn[j].getTailer())
        {
            if (t->getNextRow()->getRow() == i)
                return t;
            t = t->getNextRow();
        }

        return nullptr;
    }

    void insertNode(int i, int j, T value)
    {
        Node *newNode = new Node(i, j, value);
        this->Row[i].addToRow(newNode, j);
        this->Collumn[j].addToCollumn(newNode, i);
    }

    void deleteNode(int i, int j)
    {
        Node *node1 = accessNodeInRow(i, j);
        this->Row[i].removeInRow(node1, node1->getNextCollumn());
        Node *node2 = accessNodeInCollumn(i, j);
        this->Collumn[j].removeInCollumn(node2, node2->getNextRow());
    }

    void updateNode(int i, int j, int value)
    {
        Node *node = accessNodeInRow(i, j)->getNextCollumn();
        node->setValue(value);
    }

    bool search(int value)
    {
        for (int i = 0; i < this->nRow; i++)
        {
            Node *t = Row[i].getHeader()->getNextCollumn();
            while (t != Row[i].getTailer())
            {
                if (t->getValue() == value)
                    return true;
                t = t->getNextCollumn();
            }
        }

        return false;
    }

};

void read(Matrix<int>* matrix, string pathCSV)
{
    ifstream fin;
    string line;
    int i = 0;
    fin.open(pathCSV);
    while (fin >> line)
    {
        stringstream s(line);
        string T;
        int j = 0;

        while (getline(s, T, ','))
        {
            int num = stoi(T);
            if (num != 0)
            {
                Matrix<int>::Node *newNode = new Matrix<int>::Node(i, j, num);
                matrix->getRow(i).addToRow(newNode, j);
                matrix->getCol(j).addToCollumn(newNode, i);
            }
            j++;
        }
        i++;
    }
}

int main()
{
    
    return 0;
}