#include <iostream>
#include <stdexcept>

/*1. Реализовать стек, используя массив.
Стек (в качестве элемента выступает запись с несколькими полями):
• поместить в стек;
• извлечь из стека;
• посмотреть верхнее значение без извлечения;
• очистить стек;
• переместить из одного стека в другой;
• извлечь n элементов из стека;
• размер стека.*/

template<typename T>
class Stack {
private:
    T* array;
    int capacity;
    int topIndex;

public:
    //конструктор
    Stack(int capacity) : capacity(capacity), topIndex(-1) {
        array = new T[capacity];
    }

    //конструктор копирования
    Stack(const Stack& other) : capacity(other.capacity), topIndex(other.topIndex) {
        array = new T[capacity];
        for (int i = 0; i <= topIndex; ++i) {
            array[i] = other.array[i];
        }
    }

    //конструктор перемещения
    Stack(Stack&& other) : array(other.array), capacity(other.capacity), topIndex(other.topIndex) {
        other.array = nullptr;
        other.capacity = 0;
        other.topIndex = -1;
    }

    //деструктор
    ~Stack() {
        delete[] array;
    }

    void push(T value) {
        if (topIndex + 1 >= capacity) {
            throw std::overflow_error("Stack overflow");
        }

        array[++topIndex] = value;
    }

    T& pop() {
        if (topIndex < 0) {
            throw std::underflow_error("Stack underflow");
        }

        return array[topIndex--];
    }

    T& peek() {
        if (topIndex < 0) {
            throw std::underflow_error("Stack underflow");
        }

        return array[topIndex];
    }

    void pop(int count) {
        if (topIndex < 0 || count > topIndex + 1) {
            throw std::underflow_error("Stack underflow");
        }

        topIndex -= count;
    }

    void clear() {
        topIndex = -1;
    }

    int size() {
        return topIndex + 1;
    }
};

int main() {
    Stack<int> stack(10);

    for (int i = 0; i < 8; i++)
        stack.push(i * 10);

    std::cout << "Stack (peek): " << stack.peek() << std::endl;
    std::cout << "Stack (pop): " << stack.pop() << std::endl;
    std::cout << "Stack (peek): " << stack.peek() << std::endl;
    std::cout << "Stack (size): " << stack.size() << std::endl;

    std::cout << std::endl;
    Stack<int> copy(stack);
    std::cout << "Stack copy (peek): " << copy.peek() << std::endl;
    std::cout << "Stack copy (size): " << copy.size() << std::endl;

    std::cout << std::endl;
    Stack<int> moved = std::move(stack);
    std::cout << "Stack moved (peek): " << moved.peek() << std::endl;
    std::cout << "Stack moved (size): " << moved.size() << std::endl;
    std::cout << "Stack (size): " << stack.size() << std::endl;

    std::cout << std::endl;
    moved.pop(5);
    std::cout << "Stack moved (multiple pop)" << std::endl;
    std::cout << "Stack moved (size): " << moved.size() << std::endl;

    return 0;
}