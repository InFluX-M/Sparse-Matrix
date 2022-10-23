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

    class SparseMatrix
    {
        int maxSize;
        int **compactMatrix;

    public:

        int** getCompactMatrix() {return compactMatrix;}

        SparseMatrix(Matrix<int> *matrix)
        {
            maxSize = matrix->getNCol() * matrix->getNRow() + 1;
            compactMatrix = new int *[maxSize];
            compactMatrix[0] = new int[5];

            compactMatrix[0][0] = matrix->getNRow();
            compactMatrix[0][1] = matrix->getNCol();
            compactMatrix[0][2] = matrix->getSize();
            compactMatrix[0][3] = -1;
            compactMatrix[0][4] = -1;
        }

        int access(int i, int j, int l, int r)
        {
            if (l > r) return -1;

            int mid = (l + r) / 2;

            if (compactMatrix[mid][0] == i)
            {
                if (compactMatrix[mid][1] == j) return mid;
                else if (compactMatrix[mid][1] > j) return access(i, j, l, mid - 1);
                else if (compactMatrix[mid][2] < j) return access(i, j, mid + 1, j);    
            }
            else if (compactMatrix[mid][0] > i) return access(i, j, l, mid - 1);
            
            return access(i, j, mid + 1, r);
        }

        bool insert(int i, int j, int value, int accessRow, int accessCol)
        {
            if(i<0 || i>=compactMatrix[0][0] || j<0 || j>=compactMatrix[0][1]) return false;

            compactMatrix[0][2]++;
            compactMatrix[compactMatrix[0][2]] = new int[5];
            int r = compactMatrix[0][2];

            while (r > 1 && compactMatrix[r-1][0] > i || (compactMatrix[r-1][0]==i && compactMatrix[r-1][1] > j))
            {
                if(i == compactMatrix[r-1][0]) compactMatrix[r-1][3]++;
                else if(j == compactMatrix[r-1][1]) compactMatrix[r-1][4]++;

                compactMatrix[r][0] = compactMatrix[r-1][0];
                compactMatrix[r][1] = compactMatrix[r-1][1];
                compactMatrix[r][2] = compactMatrix[r-1][2];
                compactMatrix[r][3] = compactMatrix[r-1][3];
                compactMatrix[r][4] = compactMatrix[r-1][4];

                r--;
            }

            compactMatrix[r][0] = i;
            compactMatrix[r][1] = j;
            compactMatrix[r][2] = value;
            compactMatrix[r][3] = accessRow;
            compactMatrix[r][4] = accessCol;

            return true;
        }

        bool remove(int i, int j)
        {
            int r = access(i, j, 1, compactMatrix[0][2] + 1);
            if (r == -1) return false;

            while (r != compactMatrix[0][2])
            {
                if(i == compactMatrix[r+1][0]) compactMatrix[r+1][3]--;
                else if(j == compactMatrix[r+1][1]) compactMatrix[r+1][4]--;

                compactMatrix[r][0] = compactMatrix[r + 1][0];
                compactMatrix[r][1] = compactMatrix[r + 1][1];
                compactMatrix[r][2] = compactMatrix[r + 1][2];
                compactMatrix[r][3] = compactMatrix[r + 1][3];
                compactMatrix[r][4] = compactMatrix[r + 1][4];

                r++;
            }

            compactMatrix[0][2]--;
            return true;
        }

        bool update(int i, int j, int value)
        {
            int r = access(i, j, 1, compactMatrix[0][2] + 1);
            if (r == -1)return false;

            compactMatrix[r][2] = value;
            return true;
        }

        void print()
        {
            cout << "Based Sparse Matrix Array: "
                 << "\n";
            cout << "----------------------------------------\n";
            cout << "nRow: " << compactMatrix[0][0] << ", nCol: " << compactMatrix[0][1] << ", nElement: " << compactMatrix[0][2] << "\n";

            for (int i = 1; i < compactMatrix[0][2] + 1; i++)
            {
                cout << "[" << compactMatrix[i][0] << ", ";
                cout << compactMatrix[i][1] << ": ";
                cout << compactMatrix[i][2] << ", ";
                cout << compactMatrix[i][3] << ": ";
                cout << compactMatrix[i][4] << "]\n";
            }
            cout << "----------------------------------------\n";
        }

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
            size = 0;

            if (statue) header->setNextCollumn(tailer);
            else header->setNextRow(tailer);
        }

        void setSize(int size) { this->size = size; }
        void increamentSize() { this->size++; }
        void decreamentSize() { this->size--; }
        Node *getHeader() { return this->header; }
        Node *getTailer() { return this->tailer; }
        int getSize() { return this->size; }

        void removeInRow(Node *prev, Node *node)
        {
            prev->setNextCollumn(node->getNextCollumn());
            decreamentSize();
        }

        void removeInCollumn(Node *prev, Node *node)
        {
            prev->setNextRow(node->getNextRow());
            delete node;
            decreamentSize();
        }

        int addToRow(Node *newNode, int j)
        {
            Node *t = this->getHeader()->getNextCollumn();
            Node *prev = this->getHeader();

            int accessRow = 1;

            while (t != this->getTailer())
            {
                if (t->getCollumn() < j)
                {
                    t = t->getNextCollumn();
                    prev = prev->getNextCollumn();
                    accessRow++;
                }
                else break;
            }

            newNode->setNextCollumn(t);
            prev->setNextCollumn(newNode);
            increamentSize();

            return accessRow;
        }

        int addToCollumn(Node *newNode, int i)
        {
            Node *t = this->getHeader()->getNextRow();
            Node *prev = this->getHeader();

            int accessCollumn = 1;

            while (t != this->getTailer())
            {
                if (t->getRow() < i)
                {
                    t = t->getNextRow();
                    prev = prev->getNextRow();
                    accessCollumn++;
                }
                else break;
            }

            newNode->setNextRow(t);
            prev->setNextRow(newNode);
            increamentSize();

            return accessCollumn;
        }
    };

    int size;
    int nRow;
    int nCollumn;
    LinkedList *Row;
    LinkedList *Collumn;
    SparseMatrix *sparseMatrix;

    Node *accessPrevNodeInRow(int i, int j)
    {
        Node *t = Row[i].getHeader();

        while (t->getNextCollumn() != Row[i].getTailer())
        {
            if (t->getNextCollumn()->getCollumn() == j) return t;
            t = t->getNextCollumn();
        }

        return nullptr;
    }

    Node *accessPrevNodeInCollumn(int i, int j)
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
        this->sparseMatrix = new SparseMatrix(this);
    }

    LinkedList getRow(int i) { return Row[i]; };
    LinkedList getCol(int j) { return Collumn[j]; };
    SparseMatrix *getSparseMatrix() { return sparseMatrix; };
    int getNRow() { return nRow; }
    int getNCol() { return nCollumn; }
    void setSize(int size) { this->size = size; }
    void incrementSize() { this->size++; }
    void decrementSize() { this->size--; }
    void setSparseMatrix() { this->sparseMatrix = new SparseMatrix(this); }
    int getSize() { return size; }

    Node *accessNode(int i, int j)
    {
        int r = sparseMatrix->access(i, j, 1, sparseMatrix->getCompactMatrix()[0][2] + 1);
        if (r == -1) return nullptr;

        if(sparseMatrix->getCompactMatrix()[r][3] < sparseMatrix->getCompactMatrix()[r][4])
        {          
            Node *t = Row[i].getHeader()->getNextCollumn();
            while (t != Row[i].getTailer())
            {
                if (t->getCollumn() == j) return t;
                t = t->getNextCollumn();
            }
            return nullptr;
        }
        else
        {
            Node *t = Collumn[j].getHeader()->getNextRow();
            while (t != Collumn[j].getTailer())
            {
                if (t->getRow() == i) return t;
                t = t->getNextRow();
            }
            return nullptr;
        }
    }

    bool insertNode(int i, int j, T value)
    {
        if (i > nRow || j > nCollumn) return false;

        Node *newNode = new Node(i, j, value);
        int accessRow = this->Row[i].addToRow(newNode, j);
        int accesscollumn = this->Collumn[j].addToCollumn(newNode, i);
        size++;

        return sparseMatrix->insert(i, j, value, accessRow, accesscollumn);
    }

    bool deleteNode(int i, int j)
    {
        Node *node1 = accessPrevNodeInRow(i, j);
        if (node1 == nullptr) return false;
        this->Row[i].removeInRow(node1, node1->getNextCollumn());
        Node *node2 = accessPrevNodeInCollumn(i, j);
        if (node2 == nullptr) return false;
        this->Collumn[j].removeInCollumn(node2, node2->getNextRow());
        size--;

        return sparseMatrix->remove(i, j);
    }

    bool updateNode(int i, int j, int value)
    {
        Node *node = accessNode(i, j);
        if (node == nullptr) return false;
        node->setValue(value);

        return sparseMatrix->update(i, j, value);
    }

    bool search(int value)
    {
        for (int i = 0; i < this->nRow; i++)
        {
            Node *t = Row[i].getHeader()->getNextCollumn();
            while (t != Row[i].getTailer())
            {
                if (t->getValue() == value) return true;
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

void readCSV(Matrix<int> *matrix, string pathCSV)
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
            if (num != 0) matrix->insertNode(i, j, num);
            j++;
        }
        i++;
    }
}

void write(Matrix<int> *matrix)
{
    fstream fout;
    fout.open("SM("+to_string(matrix->getNRow())+","+to_string(matrix->getNCol())+").csv", ios::out | ios::trunc);

    for (int i = 0; i < matrix->getNRow(); i++)
    {
        for (int j = 0; j < matrix->getNCol(); j++)
        {
            Matrix<int>::Node *t = matrix->accessNode(i, j);
            if (t != nullptr) fout << t->getValue();
            else fout << 0;
            
            if (j == matrix->getNCol() - 1) fout << "\n";
            else fout << ",";
        }
    }
}

void panel(Matrix<int> *matrix)
{
    cout << "1- Insert Node\n"
         << "2- Delete Node\n"
         << "3- Search Value\n"
         << "4- Update Node\n"
         << "5- Print(Based Row)\n"
         << "6- Print(Based Collumn)\n"
         << "7- Sparse Matrix Array\n"
         << "8- Write CSV\n\n";

    cout << "statement: ";
    int op;
    cin >> op;

    int i, j, v;

    switch (op)
    {
    case 1:
        cout << "Row: ";
        cin >> i;
        cout << "Collumn: ";
        cin >> j;
        cout << "Value: ";
        cin >> v;

        if (matrix->insertNode(i, j, v)) cout << "DONE!\n";
        else cout << "FAIL!\n";
        break;

    case 2:
        cout << "Row: ";
        cin >> i;
        cout << "Collumn: ";
        cin >> j;

        if (matrix->deleteNode(i, j)) cout << "DONE!\n";
        else cout << "FAIL!\n";
        break;

    case 3:
        cout << "Value: ";
        cin >> v;

        if (matrix->search(v)) cout << "Find!\n";
        else cout << "Not Find!\n";
        break;

    case 4:
        cout << "Row: ";
        cin >> i;
        cout << "Collumn: ";
        cin >> j;
        cout << "Value: ";
        cin >> v;

        if (matrix->updateNode(i, j, v)) cout << "DONE!\n";
        else cout << "FAIL!\n";
        break;

    case 5:
        matrix->printBasedRow();
        break;

    case 6:
        matrix->printBasedCollumn();
        break;

    case 7:
        matrix->getSparseMatrix()->print();
        break;

    case 8:
        write(matrix);
        break;

    default:
        break;
    }

    cout << "\n";
    panel(matrix);
}

void mainPanel()
{
    cout << "CSV File Name: ";
    string path;
    cin >> path;

    cout << "Number of Rows: ";
    int nRow;
    cin >> nRow;

    cout << "Number of Collumns: ";
    int nCol;
    cin >> nCol;

    Matrix<int> *matrix = new Matrix<int>(nRow, nCol);
    readCSV(matrix, path);

    panel(matrix);
}

int main()
{
    mainPanel();
    return 0;
}