#include <bits/stdc++.h>
using namespace std;

bool statue;

template <typename T>
class Matrix
{
public:
    class Node
    {
        int row;
        int collumn;
        T value;
        Node *nextRow;
        Node *nextCollumn;

    public:
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

private:
    class LinkedList
    {
    private:
        Node *header;
        Node *tailer;
        int size;

    public:

        LinkedList()
        {
            header = new Node(100, 100, 100);
            tailer = new Node(100, 100, 100);

            if (statue) header->setNextCollumn(tailer);
            else header->setNextRow(tailer);
            
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
                else break;
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
                else break;   
            }

            newNode->setNextRow(t);
            prev->setNextRow(newNode);
            increamentSize();
        }
    };

    int size;
    int nRow;
    int nCollumn;
    LinkedList *Row;
    LinkedList *Collumn;

    Node *accessNodeInRow(int i, int j)
    {
        Node *t = Row[i].getHeader();

        while (t->getNextCollumn() != Row[i].getTailer())
        {
            if (t->getNextCollumn()->getCollumn() == j) return t;
            t = t->getNextCollumn();
        }

        return nullptr;
    }

    Node *accessNodeInCollumn(int i, int j)
    {
        Node *t = Collumn[j].getHeader();

        while (t->getNextRow() != Collumn[j].getTailer())
        {
            if (t->getNextRow()->getRow() == i) return t;
            t = t->getNextRow();
        }

        return nullptr;
    }

public:

    Matrix(int nRow, int nCollumn)
    {
        this->nRow = nRow;
        this->nCollumn = nCollumn;
        statue = true;
        this->Row = new LinkedList[nRow];
        statue = false;
        this->Collumn = new LinkedList[nCollumn];
        size = 0;
    }

    LinkedList getRow(int i) { return Row[i]; };
    LinkedList getCol(int j) { return Collumn[j]; };
    int getNRow() { return nRow; }
    int getNCol() { return nCollumn; }
    void setSize(int size) { this->size = size; }
    void incrementSize() { this->size++; }
    void decrementSize() { this->size--; }
    int getSize() { return size; }

    bool insertNode(int i, int j, T value)
    {
        if(i>nRow || j>nCollumn) return false;
        Node *newNode = new Node(i, j, value);
        this->Row[i].addToRow(newNode, j);
        this->Collumn[j].addToCollumn(newNode, i);
        size++;
        return true;
    }

    bool deleteNode(int i, int j)
    {
        Node *node1 = accessNodeInRow(i, j);
        if(node1 == nullptr) return false;
        this->Row[i].removeInRow(node1, node1->getNextCollumn());
        Node *node2 = accessNodeInCollumn(i, j);
        if(node2 == nullptr) return false;
        this->Collumn[j].removeInCollumn(node2, node2->getNextRow());
        size--;
        return true;
    }

    bool updateNode(int i, int j, int value)
    {
        Node *node = accessNodeInRow(i, j);
        if(node == nullptr) return false;
        node = node->getNextCollumn();
        node->setValue(value);
        return true;
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

    void printBasedRow()
    {
        cout << "Based Row: "
             << "\n";
        cout << "----------------------------------------\n";
        for (int i = 0; i < nRow; i++)
        {
            cout << i << ": ";
            Node *t = Row[i].getHeader()->getNextCollumn();
            while (t != Row[i].getTailer())
            {
                cout << "[" << t->getCollumn() << ":" << t->getValue() << "]  ";
                t = t->getNextCollumn();
            }
            cout << "\n";
        }
        cout << "----------------------------------------\n";
    }

    void printBasedCollumn()
    {
        cout << "Based Collumn: "
             << "\n";
        cout << "----------------------------------------\n";
        for (int i = 0; i < nCollumn; i++)
        {
            cout << i << ": ";
            Node *t = Collumn[i].getHeader()->getNextRow();
            while (t != Collumn[i].getTailer())
            {
                cout << "[" << t->getRow() << ":" << t->getValue() << "]  ";
                t = t->getNextRow();
            }
            cout << "\n";
        }
        cout << "----------------------------------------\n";
    }
};

class SparseMatrix
{
    int **compactMatrix;

    void complete(Matrix<int> *matrix)
    {
        compactMatrix[0][0] = matrix->getNRow();
        compactMatrix[0][1] = matrix->getNCol();
        compactMatrix[0][2] = matrix->getSize();

        int r = 1;
        for (int i = 0; i < matrix->getNRow(); i++)
        {
            Matrix<int>::Node *t = matrix->getRow(i).getHeader()->getNextCollumn();
            while (t != matrix->getRow(i).getTailer())
            {
                int j = t->getCollumn();
                compactMatrix[r][0] = i;
                compactMatrix[r][1] = j;
                compactMatrix[r][2] = t->getValue();
                r++;
                t = t->getNextCollumn();
            }
        }
    }

public:
    SparseMatrix(Matrix<int> *matrix)
    {
        compactMatrix = new int *[matrix->getSize() + 1];
        for (int i = 0; i <= matrix->getSize(); i++)
        {
            compactMatrix[i] = new int[3];
        }

        complete(matrix);
    }

    void print()
    {
        cout << "Based Sparse Matrix Array: "<< "\n";
        cout << "----------------------------------------\n";
        cout << "nRow: " << compactMatrix[0][0] << ", nCol: " << compactMatrix[0][1] << ", nElement: " << compactMatrix[0][2] << "\n";

        for (int i = 1; i < compactMatrix[0][2] + 1; i++)
        {
            cout << "[" << compactMatrix[i][0] << ", ";
            cout << compactMatrix[i][1] << ": ";
            cout << compactMatrix[i][2] << "]\n";
        }
        cout << "----------------------------------------\n";
    }

};

void read(Matrix<int> *matrix, string pathCSV)
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
                matrix->incrementSize();
            }
            j++;
        }
        i++;
    }
}

int main()
{
    Matrix<int> *matrix = new Matrix<int>(10, 5);
    read(matrix, "M(10,5).csv");

    matrix->printBasedRow();
    matrix->printBasedCollumn();

    SparseMatrix *sparseMatrix = new SparseMatrix(matrix);
    sparseMatrix->print();

    return 0;
}