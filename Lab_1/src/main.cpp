#include <iostream>
#include <vector>
#include <string>
#include <locale>

/*16. Придумать несколько алгоритмов и сравнить их порядок сложности в лучшем, среднем и худшем случаях
 для решения следующей задачи.
    Дана таблица клиентов фирмы. В каждой строке таблицы указаны ФИО и тип клиента (целое число от 1 до 5).
Необходимо переставить записи так, чтобы все клиенты были сгруппированы по типу клиента (причем группы шли
в порядке возрастания номера).*/

struct Client {
    std::string name;
    int type;
};

//функция сортировки пузырьком
void bubble_sort(std::vector<Client>& clients) {
    int n = clients.size();  //определяем размер вектора

    //основной цикл, который проходит через каждый элемент
    for (int i = 0; i < n - 1; i++) {

        //внутренний цикл, который проходит через элементы от начала до "n-i-1".
        //после каждого прохода наибольший элемент перемещается к концу.
        for (int j = 0; j < n - i - 1; j++) {

            //если текущий элемент больше следующего, меняем их местами
            if (clients[j].type > clients[j + 1].type) {
                std::swap(clients[j], clients[j + 1]);
            }
        }
    }
}

//функция сортировки выбором
void selection_sort(std::vector<Client>& clients) {
    int n = clients.size();  //определяем размер вектора

    //основной цикл, который проходит через каждый элемент
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;  //начинаем с того, что текущий элемент является наименьшим

        //внутренний цикл, который проходит через оставшиеся элементы, чтобы найти минимальный элемент
        for (int j = i + 1; j < n; j++) {

            //если находим новый минимальный элемент, обновляем min_index
            if (clients[j].type < clients[min_index].type) {
                min_index = j;
            }
        }

        //меняем местами текущий элемент с найденным минимальным элементом
        std::swap(clients[i], clients[min_index]);
    }
}

//функция сортировки подсчетом
void counting_sort(std::vector<Client>& clients) {
    int n = clients.size();
    std::vector<Client> output(n);  //массив для хранения отсортированных элементов

    int count[6] = { 0 };  //инициализируем массив подсчета, где индексы соответствуют типам клиентов (1-5)

    //подсчитываем количество каждого типа клиента в исходном массиве
    for (int i = 0; i < n; i++) {
        count[clients[i].type]++;
    }

    //преобразуем count так, чтобы позиция каждого элемента в массиве output стала ясной
    //теперь count[i] содержит количество элементов, которые меньше или равны i
    for (int i = 1; i <= 5; i++) {
        count[i] += count[i - 1];
    }

    //размещаем элементы в массиве output
    //перебираем элементы исходного массива справа налево, чтобы сортировка была устойчивой
    for (int i = n - 1; i >= 0; i--) {
        output[count[clients[i].type] - 1] = clients[i];  //помещаем элемент на правильную позицию
        count[clients[i].type]--;  //уменьшаем количество доступных позиций для данного значения
    }

    //копируем отсортированные элементы обратно в исходный массив
    for (int i = 0; i < n; i++) {
        clients[i] = output[i];
    }
}

void print_clients(const std::vector<Client>& clients) {
    for (const Client& client : clients) {
        std::cout << client.name << " " << client.type << std::endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));  //инициализируем генератор случайных чисел

    //создаем тестовые данные
    std::vector<Client> clients = {
        {"Иванов Иван Иванович", rand() % 5 + 1},
        {"Петров Петр Петрович", rand() % 5 + 1},
        {"Сидоров Иван Васильевич", rand() % 5 + 1},
        {"Кривин Емельян Игнатьевич", rand() % 5 + 1},
        {"Простаков Петр Сергеевич", rand() % 5 + 1}
    };

    std::cout << "Исходные данные:" << std::endl;
    print_clients(clients);
    std::cout << "------------------------------------" << std::endl;

    std::vector<Client> clients_copy;

    std::cout << "Bubble Sort:" << std::endl;
    clients_copy = clients;  //создаем копию исходных данных
    bubble_sort(clients_copy);
    print_clients(clients_copy);
    std::cout << "------------------------------------" << std::endl;

    std::cout << "Selection Sort:" << std::endl;
    clients_copy = clients;  //создаем копию исходных данных
    selection_sort(clients_copy);
    print_clients(clients_copy);
    std::cout << "------------------------------------" << std::endl;

    std::cout << "Counting Sort:" << std::endl;
    clients_copy = clients;  //создаем копию исходных данных
    counting_sort(clients_copy);
    print_clients(clients_copy);

    return 0;
}