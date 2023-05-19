// CourseWork.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <io.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

template< typename Type > Type* resize(Type* arr, size_t oldsize, size_t newSize);

class Node {
public:
    int key;
    int height;
    int balance;
    Node* parent;
    Node* left;
    Node* right;
    Node(int key) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        height = 1;
        balance = 0;
        level = 0;
        this->key = key;
    }
    Node() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        balance = 0;
        height = 1;
        level = 0;
        key = 0;
    }
    int* outputNode(int *coordinates, size_t &coordinatesLength, int outputType) {
        // 0 - key
        // 1 - height
        // 2 - balance
        int value;
        if (outputType == 0)
            value = key;
        else if (outputType == 1)
            value = height;
        else
            value = balance;
        Node *node = this;
        int addition = calcFullAddition(outputType);
        size_t newCoordinatesMaxSize = 100;
        int* newCoordinates = new int[newCoordinatesMaxSize];
        int counter = 0;
        bool flag = 1;
        int parh = 0;
        if (parent)
            parh = parent->height;
        for (int i = 0; i < level * 4 + addition; i++) {
            flag = 1;
            for (int j = 0; j < coordinatesLength; j++) {
                if (i == coordinates[j]) {
                    cout << '|';
                    newCoordinates[counter] = i;
                    counter++;
                    if (counter % 100 == 0) {
                        newCoordinates = resize(newCoordinates, newCoordinatesMaxSize, newCoordinatesMaxSize + 100);
                        newCoordinatesMaxSize += 100;
                    }
                    flag = 0;
                    break;
                }
            }
            if (flag)
                cout << ' ';
        }
        if (coordinatesLength)
            delete[] coordinates;
        if (this){
            if (isRight() == 1) {
                cout << ".-->";
                newCoordinates[counter] = level * 4 + addition;
                counter++;
                if (counter % 100 == 0) {
                    newCoordinates = resize(newCoordinates, newCoordinatesMaxSize, newCoordinatesMaxSize + 100);
                    newCoordinatesMaxSize += 100;
                }
            }
            else if (isRight() == 0)
                cout << "`-->";
            else
                cout << "--->";
            cout << value;
            newCoordinates[counter] = (level + 1) * 4 + addition + calcElemAddition(this, outputType);
            counter++;
            if (counter % 100 == 0) {
                newCoordinates = resize(newCoordinates, newCoordinatesMaxSize, newCoordinatesMaxSize + 100);
                newCoordinatesMaxSize += 100;
            }
        }
        newCoordinates = resize(newCoordinates, newCoordinatesMaxSize, counter);
        coordinates = newCoordinates;
        coordinatesLength = counter;
        return coordinates;
    }
    int* outputNode(int* coordinates, size_t& coordinatesLength, int outputType, ofstream &file) {
        // 0 - key
        // 1 - height
        // 2 - balance
        int value;
        if (outputType == 0)
            value = key;
        else if (outputType == 1)
            value = height;
        else
            value = balance;
        Node* node = this;
        int addition = calcFullAddition(outputType);
        size_t newCoordinatesMaxSize = 100;
        int* newCoordinates = new int[newCoordinatesMaxSize];
        int counter = 0;
        bool flag = 1;
        int parh = 0;
        if (parent)
            parh = parent->height;
        for (int i = 0; i < level * 4 + addition; i++) {
            flag = 1;
            for (int j = 0; j < coordinatesLength; j++) {
                if (i == coordinates[j]) {
                    file << '|';
                    newCoordinates[counter] = i;
                    counter++;
                    if (counter % 100 == 0) {
                        newCoordinates = resize(newCoordinates, newCoordinatesMaxSize, newCoordinatesMaxSize + 100);
                        newCoordinatesMaxSize += 100;
                    }
                    flag = 0;
                    break;
                }
            }
            if (flag)
                file << ' ';
        }
        if (coordinatesLength)
            delete[] coordinates;
        if (this) {
            if (isRight() == 1) {
                file << ".-->";
                newCoordinates[counter] = level * 4 + addition;
                counter++;
                if (counter % 100 == 0) {
                    newCoordinates = resize(newCoordinates, newCoordinatesMaxSize, newCoordinatesMaxSize + 100);
                    newCoordinatesMaxSize += 100;
                }
            }
            else if (isRight() == 0)
                file << "`-->";
            else
                file << "--->";
            file << value;
            newCoordinates[counter] = (level + 1) * 4 + addition + calcElemAddition(this, outputType);
            counter++;
            if (counter % 100 == 0) {
                newCoordinates = resize(newCoordinates, newCoordinatesMaxSize, newCoordinatesMaxSize + 100);
                newCoordinatesMaxSize += 100;
            }
        }
        newCoordinates = resize(newCoordinates, newCoordinatesMaxSize, counter);
        coordinates = newCoordinates;
        coordinatesLength = counter;
        return coordinates;
    }
    void setLevel(unsigned level) {
        this->level = level;
    }
    unsigned getLevel(){
        return level;
    }
private:
    unsigned level;
    int isRight() {
        if (!parent)
            return -1;
        if (this->parent->right == this)
            return 1;
        return 0;
    }
    int calcFullAddition(int outputType) {
        Node *currNode = this;
        int fullAddition = 0;
        while (currNode->parent){
            fullAddition += calcElemAddition(currNode->parent, outputType);
            currNode = currNode->parent;
        }
        return fullAddition;
    }
    int calcElemAddition(Node *node, int outputType) {
        int key = 0;
        if (outputType == 0)
            key = node->key;
        else if (outputType == 1)
            key = node->height;
        else
            key = node->balance;
        int addition = 0;
        if (key < 0)
            addition++;
        int division = 10;
        while (abs(key) / division > 0){
            addition++;
            division *= 10;
        }
        return addition;
    }
};

class AVL {
public:
    int height;
    AVL(vector <int> v) {
        length = 0;
        height = 0;
        for (int i = 0; i < v.size(); i++) {
            insert(v[i]);
        }
        fixAll();
        Node* balanceNode = isBalanceNeeded(head);
        while (balanceNode) {
            balance(balanceNode);
            balanceNode = isBalanceNeeded(head);
        }
    }
    AVL(vector <int> v, ofstream &file) {
        length = 0;
        height = 0;
        for (int i = 0; i < v.size(); i++) {
            insert(v[i], file);
        }
        fixAll();        
    }
    ~AVL() {
        destroy(head);
    }
    void output(int outputType) {
        Node** arr = new Node*[length];
        int* coordinates = nullptr;
        size_t coordinatesLength = 0;
        int i = 0;
        inOrderTravers(head, arr, i);
        for (int i = 0; i < length; i++) {
            coordinates = arr[i]->outputNode(coordinates, coordinatesLength, outputType);
            cout << '\n';
        }
        delete[] coordinates;
    }
    void output(int outputType, ofstream &file) {
        Node** arr = new Node * [length];
        int* coordinates = nullptr;
        size_t coordinatesLength = 0;
        int i = 0;
        inOrderTravers(head, arr, i);
        for (int i = 0; i < length; i++) {
            coordinates = arr[i]->outputNode(coordinates, coordinatesLength, outputType, file);
            file << '\n';
        }
        file << '\n';
        delete[] arr;
        delete[] coordinates;
    }
    void insert(int key) {
        Node* parent = search(head, key);
        if (isInAVL(key)) {
            cout << "Ключ \"" << key << "\" уже содержится в дереве!\n";
            return;
        }
        Node* newNode = new Node{ key };
        if (parent) {
            newNode->parent = parent;
            if (key < parent->key)
                parent->left = newNode;
            else
                parent->right = newNode;
        }
        length++;
        if (!head)
            head = newNode;
        fixAll();
        Node* balanceNode = isBalanceNeeded(head);
        balance(balanceNode);
    }
    void insert(int key, ofstream &file) {
        Node* parent = search(head, key);
        if (isInAVL(key)) {
            cout << "Ключ уже содержится в дереве!\n";
            return;
        }
        Node* newNode = new Node{ key };
        if (parent) {
            newNode->parent = parent;
            if (key < parent->key)
                parent->left = newNode;
            else
                parent->right = newNode;
        }
        length++;
        if (!head)
            head = newNode;
        fixAll();
        Node* balanceNode = isBalanceNeeded(head);
        if (balanceNode)
            output(0, file);
        balance(balanceNode);
        output(0, file);
    }
    void pop(int key) {
        if (!isInAVL(key)) {
            cout << "Ключа нет в дереве!\n";
            return;
        }
        Node* node = search(head, key);
        if (!node->left and !node->right) {
            if (node->parent) {
                if (node->parent->left == node)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
            }
            else {
                head = nullptr;
            }
            delete node;
        }
        else if (node->left and !node->right) {
            if (node->parent) {
                if (node->parent->left == node)
                    node->parent->left = node->left;
                else
                    node->parent->right = node->left;
            }
            else {
                head = node->left;
            }
            node->left->parent = node->parent;
            delete node;
        }
        else if (node->right and !node->left) {
            if (node->parent) {
                if (node->parent->left == node)
                    node->parent->left = node->right;
                else
                    node->parent->right = node->right;
            }
            else {
                head = node->right;
            }
            node->right->parent = node->parent;
            delete node;
        }
        else {
            Node* change = getMaxAVL(node->left);
            if (change != node->left){
                change->parent->right = change->left;
                if (change->left) {
                    change->left->parent = change->parent;
                }
            }
            change->parent = node->parent;
            if (node == head)
                head = change;
            if (node->parent) {
                if (node->parent->left == node)
                    node->parent->left = change;
                else
                    node->parent->right = change;
            }
            change->right = node->right;
            change->right->parent = change;
            if (node->left != change) {
                change->left = node->left;
                change->left->parent = change;
            }
            delete node;
        }
        length--;
        fixAll();
        Node* balanceNode = isBalanceNeeded(head);
        while (balanceNode) {
            balance(balanceNode);
            balanceNode = isBalanceNeeded(head);
        }
    }
    void pop(int key, ofstream &file) {
        if (!isInAVL(key)) {
            cout << "Ключа нет в дереве!\n";
            return;
        }
        Node* node = search(head, key);
        if (!node->left and !node->right) {
            if (node->parent) {
                if (node->parent->left == node)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
            }
            else {
                head = nullptr;
            }
            delete node;
        }
        else if (node->left and !node->right) {
            if (node->parent) {
                if (node->parent->left == node)
                    node->parent->left = node->left;
                else
                    node->parent->right = node->left;
            }
            else {
                head = node->left;
            }
            node->left->parent = node->parent;
            delete node;
        }
        else if (node->right and !node->left) {
            if (node->parent) {
                if (node->parent->left == node)
                    node->parent->left = node->right;
                else
                    node->parent->right = node->right;
            }
            else {
                head = node->right;
            }
            node->right->parent = node->parent;
            delete node;
        }
        else {
            Node* change = getMaxAVL(node->left);
            if (change != node->left) {
                change->parent->right = change->left;
                if (change->left) {
                    change->left->parent = change->parent;
                }
            }
            change->parent = node->parent;
            if (node == head)
                head = change;
            if (node->parent) {
                if (node->parent->left == node)
                    node->parent->left = change;
                else
                    node->parent->right = change;
            }
            change->right = node->right;
            change->right->parent = change;
            if (node->left != change) {
                change->left = node->left;
                change->left->parent = change;
            }
            delete node;
        }
        length--;
        fixAll();
        Node* balanceNode = isBalanceNeeded(head);
        while (balanceNode) {
            balance(balanceNode);
            balanceNode = isBalanceNeeded(head);
            output(0, file);
        }
        output(0, file);
    }
    bool isInAVL(int key) {
        if (head)
            return isInAVL(head, key);
        else
            return 0;
    }
    void getAll(vector <int> v) {
        if (head)
            getAll(head, v);
    }
private:
    int length;
    Node* head;
    void inOrderTravers(Node* root, Node **arr, int &i) {
        if (root) {
            inOrderTravers(root->right, arr, i);
            arr[i] = root;
            i++;
            inOrderTravers(root->left, arr, i);
        }
    }
    void fixBalanceValues(Node *node) {
        int left = 0, right = 0;
        if (node->left)
            left = node->left->height;
        if (node->right)
            right = node->right->height;
        node->balance = abs(right - left);
        if (node->left)
            fixBalanceValues(node->left);
        if (node->right)
            fixBalanceValues(node->right);
    }
    int fixHeightValues(Node* node) {
        node->height = 1;
        if (node->left and node->right)
            node->height = max(fixHeightValues(node->right), fixHeightValues(node->left)) + 1;
        else if (node->right)
            node->height = fixHeightValues(node->right) + 1;
        else if (node->left)
            node->height = fixHeightValues(node->left) + 1;
        return node->height;
    }
    void fixLvl(Node* node, unsigned level) {
        node->setLevel(level);
        if (node->left)
            fixLvl(node->left, level + 1);
        if (node->right)
            fixLvl(node->right, level + 1);
    }
    void fixAll() {
        if (length == 0)
            return;
        height = fixHeightValues(head);
        fixBalanceValues(head);
        fixLvl(head, 0);
    }
    Node* isBalanceNeeded(Node* node) {
        if (node) {
            Node* adress = nullptr;
            Node* tempAdress = nullptr;
            int leftBalance = 0, rightBalance = 0;
            if (node->right)
                rightBalance = node->right->balance;
            if (node->left)
                leftBalance = node->left->balance;
            if (node->balance == 2 and leftBalance < 2 and rightBalance < 2)
                adress = node;
            if (node->right) {
                tempAdress = isBalanceNeeded(node->right);
                if (tempAdress and (!adress or tempAdress->getLevel() > adress->getLevel()))
                    adress = tempAdress;
            }
            if (node->left) {
                tempAdress = isBalanceNeeded(node->left);
                if (tempAdress and (!adress or tempAdress->getLevel() > adress->getLevel()))
                    adress = tempAdress;
            }
            return adress;
        }
        return nullptr;
    }
    void rotateRight(Node *a) {
        Node* b = a->left;
        a->left = b->right; 
        if (a->left)
            a->left->parent = a;
        b->right = a;
        b->parent = a->parent;
        a->parent = b;
        if (b->parent) {
            if (b->parent->left == a)
                b->parent->left = b;
            else
                b->parent->right = b;
        }
        else {
            head = b;
        }
    }
    void rotateLeft(Node* a) {
        Node* b = a->right;
        a->right = b->left;
        if (a->right)
            a->right->parent = a;
        b->left = a;
        b->parent = a->parent;
        a->parent = b;
        if (b->parent) {
            if (b->parent->left == a)
                b->parent->left = b;
            else
                b->parent->right = b;
        }
        else {
            head = b;
        }
    }
    void rotateLeftRight(Node* node) {
        rotateLeft(node->left);
        rotateRight(node);
    }
    void rotateRightLeft(Node* node) {
        rotateRight(node->right);
        rotateLeft(node);
    }
    bool isInAVL(Node* node, int key) {
        if (key < node->key){
            if (node->left)
                return isInAVL(node->left, key);
            else
                return 0;
        }
        else if (key > node->key){
            if (node->right)
                return isInAVL(node->right, key);
            else
                return 0;
        }
        else
            return 1;
    }
    void destroy(Node* node) {
        if (node != nullptr) {
            destroy(node->right);
            destroy(node->left);
            delete node;
        }
    }
    Node* getMaxAVL(Node* root) {
        while (root->right) {
            root = root->right;
        }
        return root;
    }
    void balance(Node *spinNode) {
        if (spinNode) {
            int leftHeight = 0;
            int rightHeight = 0;
            if (spinNode->left)
                leftHeight = spinNode->left->height;
            if (spinNode->right)
                rightHeight = spinNode->right->height;
            if (leftHeight - rightHeight == 2) {
                if ((spinNode->left->right and spinNode->left->left and spinNode->left->right->height <= spinNode->left->left->height) or (!spinNode->left->right) or (!spinNode->left->left and !spinNode->left->right))
                    rotateRight(spinNode);
                else
                    rotateLeftRight(spinNode);
            }
            else {
                if ((spinNode->right->right and spinNode->right->left and spinNode->right->left->height <= spinNode->right->right->height) or (!spinNode->right->left) or (!spinNode->right->left and !spinNode->right->right))
                    rotateLeft(spinNode);
                else
                    rotateRightLeft(spinNode);
            }
        }
        fixAll();
    }
    Node* search(Node* node, int key) {
        if (!head)
            return nullptr;
        if (key < node->key) {
            if (node->left)
                search(node->left, key);
            else
                return node;
        }
        else if (key > node->key) {
            if (node->right)
                search(node->right, key);
            else
                return node;
        }
        else
            return node;
    }
    void getAll(Node* node, vector <int> v) {
        v.push_back(node->key);
        if (node->right)
            getAll(node->right, v);
        if (node->left)
            getAll(node->left, v);
    }
};

void setTextColor(int textColorIndex) { // Смена цвета текста
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (0 << 4) + textColorIndex);
}

void creationOutput(int current) {
    setTextColor(15);
    cout << "\tКак заполнить узлы?\n";
    setTextColor(6 - (current == 1 ? 5 : 0));
    cout << "[1] ";
    setTextColor(15);
    cout << "Заполнить случайными числами." << '\n';
    setTextColor(6 - (current == 2 ? 5 : 0));
    cout << "[2] ";
    setTextColor(15);
    cout << "Заполнить вручную." << '\n';
    setTextColor(4 - (current == 3 ? 3 : 0));
    cout << "[ESC] ";
    setTextColor(15);
    cout << "Выход из программы." << '\n';
}

void actionOutput(int current) {
    setTextColor(15);
    cout << "\tВыберите дейтсвие\n";
    setTextColor(6 - (current == 1 ? 5 : 0));
    cout << "[1] ";
    setTextColor(15);
    cout << "Вывод списка." << '\n';
    setTextColor(6 - (current == 2 ? 5 : 0));
    cout << "[2] ";
    setTextColor(15);
    cout << "Добавить элемент." << '\n';
    setTextColor(6 - (current == 3 ? 5 : 0));
    cout << "[3] ";
    setTextColor(15);
    cout << "Удалить элемент." << '\n';
    setTextColor(6 - (current == 4 ? 5 : 0));
    cout << "[4] ";
    setTextColor(15);
    cout << "Проверить дерево на наличие элемента." << '\n';
    setTextColor(6 - (current == 5 ? 5 : 0));
    cout << "[5] ";
    setTextColor(15);
    cout << "Изменить элемент." << '\n';
    setTextColor(6 - (current == 6 ? 5 : 0));
    cout << "[6] ";
    setTextColor(15);
    cout << "Сгенерировать задания." << '\n';
    setTextColor(4 - (current == 7 ? 3 : 0));
    cout << "[ESC] ";
    setTextColor(15);
    cout << "Выход из программы." << '\n';
}

int output(void outputType(int), unsigned max) {
    int currentNum = 1;
    unsigned button;
    outputType(currentNum);
    while (TRUE) {
        button = _getch();
        button = (button == 224) ? _getch() : button;
        if (button == 80 || button == 77) {           // Управление стрелками движения вниз
            system("cls");
            currentNum += 1;
            currentNum = currentNum == max + 1 ? 1 : currentNum;
            outputType(currentNum);
        }
        else if (button == 72 || button == 75) {      // Управление стрелками движения вверх
            system("cls");
            currentNum -= 1;
            currentNum = currentNum == 0 ? max : currentNum;
            outputType(currentNum);

        }
        else if (button >= 49 && button <= 48 + max) {      // Управление цифрами
            system("cls");
            currentNum = button - 48;
            outputType(currentNum);
            system("cls");
            return currentNum;
        }
        else if (button == 13) {   // Нажат enter
            if (currentNum != max)   // Нажат не enter+[esc]
            {
                system("cls");
                return currentNum;
            }
            else                   // Нажат enter+[esc]
            {
                system("cls");
                exit(0);
            }
        }
        else if (button == 27)  // Нажат esc
        {
            system("cls");
            exit(0);
        }
    }
}

template<typename Type> Type* resize(Type* arr, size_t oldSize, size_t newSize) {
    Type* temp = new Type[min(oldSize, newSize)];
    for (int i = 0; i < min(oldSize, newSize); i++)
        temp[i] = arr[i];
    delete[] arr;
    arr = new Type[newSize];
    for (int i = 0; i < min(oldSize, newSize); i++)
        arr[i] = temp[i];
    delete[] temp;
    return arr;
}

int* tokenizer(string expression, unsigned& counter) {
    size_t arrSize = 100;
    int* exprArr = new int[arrSize];
    string temp = "";
    for (int i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i]) or expression[i] == '-')
            temp += expression[i];
        else {
            if (temp != "") {
                exprArr[counter] = stoi(temp);
                counter++;
                if (counter == arrSize) {
                    exprArr = resize(exprArr, arrSize, arrSize + 100);
                    arrSize += 100;
                }
                temp = "";
            }
        }
    }
    if (temp != "") {
        exprArr[counter] = stoi(temp);
        counter++;
        temp = "";
    }
    exprArr = resize(exprArr, arrSize, counter);
    return exprArr;
}

unsigned maxOfOutput(void outputType(int)) {
    if (outputType == creationOutput)
        return 3;
    if (outputType == actionOutput)
        return 7;
}

int main()
{
    setlocale(LC_ALL, "");
    int currentNum;
    const int size = 199;
    int* arr = new int[size];
    unsigned length = 0;
    if (_access("input.txt", 0) == -1) {
        currentNum = output(creationOutput, maxOfOutput(creationOutput));
        switch (currentNum) {
        case 1:
        {
            srand(time(0));
            cout << "Введите кол-во элементов дерева от (0 до 199): ";
            cin >> length;
            if (length < 0 or length > 199) {
                cout << "Неверное значение!\n";
                return 0;
            }
            vector <int> numbers;
            for (int i = 0; i < size; i++)
                numbers.push_back(i - 99);
            for (int i = 0; i < length; i++) {
                int index = rand() % (numbers.size());
                arr[i] = numbers[index];
                numbers.erase(numbers.cbegin() + index);
            }
            break;
        }
        case 2:
        {
            string expression = "";
            char c = cin.get();
            while (c != '\n') {
                expression += c;
                c = cin.get();
            }
            arr = tokenizer(expression, length);
            break;
        }
        }
    }
    else {
        string expression;
        ifstream input;
        input.open("input.txt");
        getline(input, expression);
        input.close();
        arr = tokenizer(expression, length);
    }
    vector<int> v;
    for (int i = 0; i < length; i++) {
        v.push_back(arr[i]);
    }
    delete[] arr;
    chrono::high_resolution_clock::time_point m_start, m_end;
    m_start = chrono::high_resolution_clock::now();
    ofstream file;
    file.open("output_ans.txt");
    AVL AVLTree(v, file);
    file.close();
    m_end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::microseconds>(m_end - m_start);
    cout << "Затраченное время: " << elapsed.count() << "мкс.\n";
    system("pause");
    system("cls");
    while (TRUE){
        currentNum = output(actionOutput, maxOfOutput(actionOutput));
        switch (currentNum) {
        case 1:
        {
            AVLTree.output(0);
            break;
        }
        case 2:
        {
            int key;
            cout << "Введите значение ключа: ";
            cin >> key;
            chrono::high_resolution_clock::time_point m_start, m_end;
            m_start = chrono::high_resolution_clock::now();
            AVLTree.insert(key);
            m_end = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(m_end - m_start);
            AVLTree.output(0);
            cout << "Затраченное время: " << elapsed.count() << "мкс.\n";
            break;
        }
        case 3:
        {
            int key;
            cout << "Введите значение ключа: ";
            cin >> key;
            chrono::high_resolution_clock::time_point m_start, m_end;
            m_start = chrono::high_resolution_clock::now();
            AVLTree.pop(key);
            m_end = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(m_end - m_start);
            AVLTree.output(0);
            cout << "Затраченное время: " << elapsed.count() << "мкс.\n";
            break;
        }
        case 4:
        {
            int key;
            cout << "Введите значение ключа: ";
            cin >> key;
            chrono::high_resolution_clock::time_point m_start, m_end;
            m_start = chrono::high_resolution_clock::now();
            bool flag = AVLTree.isInAVL(key);
            m_end = chrono::high_resolution_clock::now();
            if (AVLTree.isInAVL(key))
                cout << "Элемент есть в дереве.\n";
            else
                cout << "Элемента нет в дереве.\n";
            auto elapsed = chrono::duration_cast<chrono::microseconds>(m_end - m_start);
            cout << "Затраченное время: " << elapsed.count() << "мкс.\n";
            break;
        }
        case 5:
        {
            int key1, key2;
            cout << "Введите значение ключа, который нужно изменить: ";
            cin >> key1;
            if (!AVLTree.isInAVL(key1)) {
                cout << "Неверное значение ключа!\n";
                break;
            }
            cout << "Введите новое значение ключа: ";
            cin >> key2;
            if (AVLTree.isInAVL(key2)) {
                cout << "Неверное значение ключа!\n";
                break;
            }
            AVLTree.pop(key1);
            AVLTree.insert(key2);
            break;
        }
        case 6:
        {
            int n;
            cout << "Введите количество заданий (от 1 до 199): ";
            cin >> n;
            if (n < 1 or n > 199) {
                cout << "Неверное значение!\n";
                break;
            }
            ofstream tasks;
            ofstream output_key;
            ofstream output_ans;
            tasks.open("output_task.txt");
            output_key.open("output_key.txt");
            output_ans.open("output_ans.txt");
            for (int i = 0; i < n; i++) {
                int action = rand() % 3; // 0 - create; 1 - pop; 2 - insert;
                switch (action) {
                    case 0:
                    {
                        int length = rand() % 10 + 1;
                        vector <int> numbers;
                        vector <int> v;
                        tasks << i + 1 << ". Создать АВЛ-дерево из " << length << " элементов: ";
                        for (int i = 0; i < 199; i++)
                            numbers.push_back(i - 99);
                        for (int i = 0; i < length; i++) {
                            int index = rand() % (numbers.size());
                            v.push_back(numbers[index]);
                            tasks << numbers[index] << ' ';
                            numbers.erase(numbers.cbegin() + index);
                        }
                        tasks << '\n';
                        output_ans << "\t\t#" << i + 1 << "\n\n";
                        output_key << "\t\t#" << i + 1 << "\n\n";
                        AVL newAVL{ v, output_ans };
                        newAVL.output(0, output_key);
                        break;
                    }
                    case 1:
                    {
                        int length = rand() % 10 + 5;
                        vector <int> numbers;
                        vector <int> v;
                        for (int i = 0; i < 199; i++)
                            numbers.push_back(i - 99);
                        for (int i = 0; i < length; i++) {
                            int index = rand() % (numbers.size());
                            v.push_back(numbers[index]);
                            numbers.erase(numbers.cbegin() + index);
                        }
                        AVL newAVL{v};
                        output_ans << "\t\t#" << i + 1 << "\n\n";
                        output_key << "\t\t#" << i + 1 << "\n\n";
                        newAVL.output(0, output_ans);
                        newAVL.output(0, output_key);
                        int key = v[rand() % v.size()];
                        tasks << i + 1 << ". Удалить элемент с key=" << key << " из дерева.\n";
                        newAVL.pop(key, output_ans);
                        newAVL.output(0, output_key);
                        break;
                    }
                    case 2:
                    {
                        int length = rand() % 10 + 5;
                        vector <int> numbers;
                        vector <int> v;
                        for (int i = 0; i < 199; i++)
                            numbers.push_back(i - 99);
                        for (int i = 0; i < length; i++) {
                            int index = rand() % (numbers.size());
                            v.push_back(numbers[index]);
                            numbers.erase(numbers.cbegin() + index);
                        }
                        AVL newAVL{ v };
                        output_ans << "\t\t#" << i + 1 << "\n\n";
                        output_key << "\t\t#" << i + 1 << "\n\n";
                        newAVL.output(0, output_ans);
                        newAVL.output(0, output_key);
                        int key = numbers[rand() % numbers.size()];
                        tasks << i + 1 << ". Добавить элемент с key=" << key << " в дерево.\n";
                        newAVL.insert(key, output_ans);
                        newAVL.output(0, output_key);
                        break;
                    }
                }
            }
            tasks.close();
            output_ans.close();
            output_key.close();
            cout << "Задания и ответы к ним успешно добавлены в файлы!\n";
            break;
        }
        }
        system("pause");
        system("cls");
    }
}
