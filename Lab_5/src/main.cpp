#include <iostream>
#include <vector>
#include <stdexcept>

/*14. Разработать программу, с помощью которой можно определить наибольший допустимый размер очереди с
 вещественным информационным полем. Найдите этот размер (число элементов в очереди).*/

template <typename T>
class Queue {
public:
    void push(const T& value) {
        if (data.size() >= capacity) {
            throw std::length_error("The queue is full!");
        }
        data.push_back(value);
    }

    T pop() {
        if (data.empty()) {
            throw std::out_of_range("The queue is empty!");
        }
        T value = data.front();
        data.erase(data.begin());
        return value;
    }

    T peek() const {
        if (data.empty()) {
            throw std::out_of_range("The queue is empty!");
        }
        return data.front();
    }

    size_t size() const {
        return data.size();
    }

private:
    std::vector<T> data;
    size_t capacity = 100000;
};

int main() {
    Queue<double> queue;
    unsigned long long count = 0;

    try {
        while (true) {
            queue.push(0); //добавляем элементы с произвольным значением
            count++;

            std::cout << "Attempt №" << count << std::endl;
        }
    } catch (const std::length_error&) {
        std::cout << "Exception: queue overflow!\n";
    }

    std::cout << "Number of elements in queue: " << queue.size() << std::endl;
    std::cout << "Attempts to add: " << count << std::endl;

    return 0;
}