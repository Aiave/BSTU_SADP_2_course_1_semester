#include <iostream>

/*Реализовать двунаправленный (двусвязный) кольцевой список.
Должны быть следующие операции:
• добавление элемента в любое место списка;
• удаление элемента из любого места списка;
• перемещение влево-вправо по элементам списка;
• поиск элемента по значению.*/

template<typename T>
class DoublyCircularLinkedList {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(T v) : value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    size_t listLength;

public:
    DoublyCircularLinkedList() : head(nullptr), listLength(0) {}

    ~DoublyCircularLinkedList() {
        while (listLength) {
            pop_front();
        }
    }

    void push_back(T value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
        listLength++;
    }

    void push_front(T value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else {
            Node* tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
        listLength++;
    }

    void insert(size_t index, T value) {
        if (index > listLength) {
            throw std::out_of_range("Index out of range!");
        }

        if (index == 0) {
            push_front(value);
            return;
        }

        if (index == listLength) {
            push_back(value);
            return;
        }

        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        Node* newNode = new Node(value);
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        listLength++;
    }

    void pop_back() {
        if (!head) {
            throw std::runtime_error("List is empty!");
        }

        Node* tail = head->prev;
        if (head == tail) {
            delete head;
            head = nullptr;
        }
        else {
            tail->prev->next = head;
            head->prev = tail->prev;
            delete tail;
        }
        listLength--;
    }

    void pop_front() {
        if (!head) {
            throw std::runtime_error("List is empty!");
        }

        Node* oldHead = head;
        if (head == head->next) {
            head = nullptr;
        }
        else {
            head->next->prev = head->prev;
            head->prev->next = head->next;
            head = head->next;
        }
        delete oldHead;
        listLength--;
    }

    void remove(size_t index) {
        if (index >= listLength) {
            throw std::out_of_range("Index out of range!");
        }

        if (index == 0) {
            pop_front();
            return;
        }

        if (index == listLength - 1) {
            pop_back();
            return;
        }

        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        listLength--;
    }

    int find(T value) {
        Node* current = head;
        if (current) {
            for (size_t i = 0; i < listLength; i++) {
                if (current->value == value) {
                    return i;
                }
                current = current->next;
            }
        }
        return -1; //not found
    }

    T& get(int index) { //возвращает разыменованнай указатель, не копию
        if (listLength == 0) {
            throw std::runtime_error("List is empty!");
        }

        //обработка отрицательных индексов и "зацикливание" индексов
        if (index < 0) {
            index = (index % (int)listLength + listLength) % listLength;
        }
        else {
            index %= listLength;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }


    int length() {
        return listLength;
    }
};

int main() {
    DoublyCircularLinkedList<int> list;

    //добавляем элементы в список
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_front(0);
    list.push_back(4);
    list.insert(0, 15);
    list.push_front(30);

    list.get(1) = 40;

    //выводим элементы списка
    for (int i = 0; i < list.length(); i++) {
        std::cout << "Value at index " << i << ": " << list.get(i) << std::endl;
    }

    //поиск элемента в списке
    int findValue = 2;
    int index = list.find(findValue);
    if (index != -1) {
        std::cout << "Found value " << findValue << " at index " << index << std::endl;
    }
    else {
        std::cout << "Value " << findValue << " not found in the list." << std::endl;
    }

    //удаляем элемент из списка
    list.remove(0); //удаляем нулевой элемент
    std::cout << "After removing the element at index 0:" << std::endl;
    for (int i = 0; i < list.length(); i++) {
        std::cout << "Value at index " << i << ": " << list.get(i) << std::endl;
    }

    //проверяем кольцевой характер списка
    std::cout << "Value at index back  [-1]: " << list.get(-1) << std::endl; //должно быть равно последнему элементу
    std::cout << "Value at index front [+1]: " << list.get(list.length()) << std::endl; //должно быть равно первому элементу

    while (list.length()) {
        list.remove(0);
    }

    std::cout << "Size after removing: " << list.length() << std::endl; //должно быть равно первому элементу

    return 0;
}