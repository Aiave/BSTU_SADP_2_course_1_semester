#include <iostream>
#include <vector>

/*16. Сохраните список в массиве А, чьи записи содержат два поля: data – для элементов и поле position – для
позиций (целых чисел) элементов. Целочисленная переменная last (последний) используется для указания того, что
список содержится в записях от А[1] до A[last] массива А. Тип LIST определен следующим образом:
type
LIST = record
last: integer;
elements: array[1... maxlength] of record
    data: elementtype;
    position: integer;
end
end;
    Напишите процедуру DELETE(p, L) для удаления элемента в позиции р. Включите в процедуру все необходимые
проверки на «внештатные» ситуации.*/

//структура из задания, которая хранит значение и позицию элемента
template<typename T>
struct Element {
    T data;
    int position;
};

//сам класс - список
template<typename T>
class CustomList {
public:
    //проходимся по массиву, если там есть элемент (elenment != nullptr), то удаляем его
    ~CustomList() {
        for (int i = 0; i < elements.size(); ++i) {
            if (elements[i] != nullptr) {
                delete elements[i];
                elements[i] = nullptr;
            }
        }
    }

    //добавить элемент в конец
    void push_back(T value) {
        //создает елемент с data = value, и position = elements.size()
        //"(int) elements.size()" нужен потому что elements.size() не является типом int, оно size_t, (вроде unsigned int)
        auto element = new Element<T>{ value, (int)elements.size() };

        //если у нас в массиве уже есть удаленный элемент (то есть дырка по типу [1, 2, NULL, 3, 4]), то новое значение запишется туда
        for (int i = 0; i < elements.size(); ++i) {
            if (elements[i] == nullptr) {
                elements[i] = element;
                return;
            }
        }

        //если в массиве дырок нет, то записываем в конец
        elements.push_back(element);
    }

    //std::optional<T> значит, что может вернуться либо T, либо nullptr
    //функция для получения элемента на позиции position (const нужно, чтобы можно было использовать в print)
    std::optional<T> get(int position) const {
        //пробегаемся по всем элементам массива, если там не nullptr и позиция та, которая нам нужна, возвращаем значение data
        for (int i = 0; i < elements.size(); ++i) {
            if (elements[i] != nullptr && elements[i]->position == position) {
                return elements[i]->data;
            }
        }

        //если не нашли нужного элемента, возвращаем nullptr (для типа std::optional нужно вернуть std::nullopt, потому что они так придумали :>)
        return std::nullopt;
    }

    //функция, чтобы изменить элемент на позиции position на значение value
    void set(int position, T value) {
        //пробегаемся по всем элементам массива, если там не nullptr и позиция та, которая нам нужна, меняем значение data на value
        for (int i = 0; i < elements.size(); ++i) {
            if (elements[i] != nullptr && elements[i]->position == position) {
                elements[i]->data = value;
                return;
            }
        }

        //если такой позиции нет, то выкидывает исключение о выходе за границы массива
        throw std::out_of_range("Position not found!");
    }

    void remove(int position) {
        //пробегаемся по всем элементам массива, если там не nullptr и позиция та, которая нам нужна удаляем этот элемент
        for (int i = 0; i < elements.size(); ++i) {
            if (elements[i] != nullptr && elements[i]->position == position) {
                delete elements[i];
                elements[i] = nullptr;
                return;
            }
        }

        //если такой позиции нет, то выкидывает исключение о выходе за границы массива
        throw std::out_of_range("Position not found!");
    }

    //возвращает размер массива (const нужно, чтобы можно было использовать в print)
    int size() const {
        return elements.size();
    }

private:
    std::vector<Element<T>*> elements;
};

//функция для вывода всего массива (const CustomList<T>& значит, что мы принимаем ССЫЛКУ, то есть не копию объекта, но при этом обязуемся не менять его значений)
template<typename T>
void print(const CustomList<T>& list) {
    for (int i = 0; i < list.size(); i++) {
        //получаем значение i элемента. Помним, что мы получили не int, а std::optional<int>
        //это значит, что у нас есть ряд функция для нашего data
        // - has_value() - вернет true/false в зависимости от того, лежит ли там nullptr или нет
        // - value() - вернет значение (если вызвать value(), когда там лежит nullptr, то всё упадет)
        // - value_or(example) - вернет значение, или (если там nullptr), вернет example. К примеру .value_or(-1), вернет либо значение, что там лежит, либо -1, если там nullptr.

        auto data = list.get(i);
        std::cout
                << "Element at position " << i << ": "
                //тернатрка: нужно, чтобы в случае nullptr вывести красивую фразу "nullptr", а не мусор какой нибудь
                //также здесь используется std::to_string, это просто значит преврати мне мое значение (которое int) в строку (std::string)
                << (data.has_value() ? std::to_string(data.value()) : "nullptr")
                << std::endl;
    }
}

int main() {
    //создаем массив и записываем туда три значения: 10, 20, 30
    CustomList<int> myList;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    //выводим массив
    print(myList);

    //меняем значение 1 элемента на 999
    std::cout << "\nSet element 1 to 999\n" << std::endl;
    myList.set(1, 999);

    //выводим массив
    print(myList);

    //удаляем 1 элемент массива
    std::cout << "\nRemove element 1\n" << std::endl;
    myList.remove(1);

    //выводим массив
    print(myList);

    return 0;
}