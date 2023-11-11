#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/*Текстовый файл содержит информацию об оценках студентов за сессию:
 1) номер п-п;
 2) ФИО;
 3) номер зачётки;
 4) 5 оценок по предметам.
    Задание:
• считать файл и вывести на экран в виде таблицы;
• отсортироввать таблицу по ФИО и вывести;
• добавить сортировку по оценкам;
• поиск по фамилии и вывод строки или строк в виде таблицы.
    Файл не изменяется, сортировка происходит в консоли.

    Дополнительное задание: вывести студентов с наибольшим количеством пятёрок.*/

const int subject_count = 5;
const char subjects[5][100] = {
  "Math",
  "History",
  "English",
  "Music",
  "Art"
};
const char prefix[] = "  ";

struct student {
    int id;
    std::string fio;
    int student_book_id;
    int marks[subject_count];
};

std::vector<student> read_students() {
    std::vector<student> students;              //vector < тип данных > <имя вектора>;
    std::fstream source_file("students.txt");//для считывания данных из файла и для записи в файл

    //если файл не открыт
    if (!source_file.is_open())
        return students;

    //достигнут ли конец файла
    while (!source_file.eof()) {
        student student;
        source_file >> student.id >> student.fio >> student.student_book_id;
        for (int i = 0; i < subject_count; i++) {
            source_file >> student.marks[i];
        }
        students.push_back(student);
    }

    return students;
}

//фильтр по имени
std::vector<student> filter_by_name(std::vector<student> source, std::string filter) {
    std::vector<student> result;
    for (int i = 0; i < source.size(); ++i) {
        if (source[i].fio.find(filter) != std::string::npos)
            result.push_back(source[i]);
    }
    return result;
}

//сортировка по имени
std::vector<student> sort_by_name(std::vector<student> source, bool asc) {
    std::vector<student> result(source);
    for (int i = 0; i < result.size() - 1; i++) {
        for (int j = 0; j < result.size() - i - 1; j++) {
            const bool ascending = result[j].fio > result[j + 1].fio;//больше ли первое, идущее за ним второго
            if (ascending && asc || !ascending && !asc) {
                //отправляем большое число в конец, если условие 1, или маленькое, если 2
                const auto temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }
    return result;
}

//сортировка по предмету
std::vector<student> sort_by_subject(std::vector<student> source, int subject_index,
    bool asc) {
    if (subject_index < 0 || subject_index >= subject_count)
        return source;

    std::vector<student> result(source);
    for (int i = 0; i < result.size() - 1; i++) {
        for (int j = 0; j < result.size() - i - 1; j++) {
            const bool ascending =
                result[j].marks[subject_index] > result[j + 1].marks[subject_index];
            if (ascending && asc || !ascending && !asc) {
                const auto temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }
    return result;
}

//фильтр по количеству пятёрок
std::vector<student> filter_by_number_of_fives(std::vector<student> students) {
    int max_fives = 0;
    //проходимся по студентам
    for (int i = 0; i < students.size(); i++) {
        int sum_fives = 0;
        //считаем, сколько пятёрок
        for (int j = 0; j < subject_count; j++) {
            if (students[i].marks[j] == 5)
            {
                sum_fives++;
            }
        }
        //находим наибольшее количество пятёрок
        if (sum_fives > max_fives)
            max_fives = sum_fives;
    }

    //создаём новый вектор
    std::vector<student> result;
    //проходимся по студентам
    for (int i = 0; i < students.size(); i++) {
        int sum_fives = 0;
        //считаем количество пятёрок
        for (int j = 0; j < subject_count; j++) {
            if (students[i].marks[j] == 5)
            {
                sum_fives++;
            }
        }
        //если количество пятёрок равно максимальному - добавляем в конец вектора
        if (sum_fives == max_fives) {
            result.push_back(students[i]);
        }
    }

    return result;
}

enum class commands { none, filter, filter_fives, sort_fio, sort_mark, exit, };

enum class sort_type { none, fio, mark };
enum class filter_type { none, fio, fives };

void draw_ui(std::vector<student> students, std::string filter_query, filter_type filter_type, sort_type sort_type,
    bool ascending, int subject) {
    const int id_width = 5;
    const int fio_width = 20;
    const int student_number_width = 20;
    const int mark = 8;

    std::cout.width(5);
    std::cout << std::left << "id";
    std::cout.width(fio_width);
    std::cout << std::left << " fio";
    std::cout.width(student_number_width);
    std::cout << std::left << " student number";
    for (int i = 0; i < subject_count; i++) {
        std::cout.width(mark);
        std::cout << std::left << " " + std::string(subjects[i]);
    }
    std::cout << std::endl;

    std::cout.width(id_width + fio_width + student_number_width + mark * subject_count);
    std::cout.fill('-');
    std::cout << "" << std::endl;
    std::cout.fill(' ');

    for (int i = 0; i < students.size(); ++i) {
        student student = students[i];

        std::cout.width(id_width);
        std::cout << std::left << student.id;
        std::cout.width(fio_width);
        std::cout << std::left << " " + student.fio;
        std::cout.width(student_number_width);
        std::cout << std::left << " " + std::to_string(student.student_book_id);
        for (int i = 0; i < subject_count; i++) {
            std::cout.width(mark);
            std::cout << std::left << " " + std::to_string(student.marks[i]);
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl;

    std::cout << "Select command:" << std::endl;

    std::cout << prefix;
    if (filter_type != filter_type::fio)
        std::cout << (int)commands::filter << ". Filter by fio" << std::endl;
    else
        std::cout << (int)commands::filter << ". Clear filter by fio - \""
        << filter_query << "\"" << std::endl;

    std::cout << prefix;
    if (filter_type != filter_type::fives)
        std::cout << (int)commands::filter_fives << ". Filter by number of fives" << std::endl;
    else
        std::cout << (int)commands::filter_fives << ". Clear filter by number of fives" << std::endl;

    std::cout << prefix;
    if (sort_type != sort_type::fio)
        std::cout << (int)commands::sort_fio << ". Sort by fio" << std::endl;
    else
        std::cout << (int)commands::sort_fio << ". Clear sorting by fio ("
        << (ascending ? "ascending" : "descending") << ")" << std::endl;

    std::cout << prefix;
    if (sort_type != sort_type::mark)
        std::cout << (int)commands::sort_mark << ". Sort by mark" << std::endl;
    else
        std::cout << (int)commands::sort_mark << ". Clear sorting by " << subjects[subject] << " ("
        << (ascending ? "ascending" : "descending") << ")" << std::endl;

    std::cout << prefix << (int)commands::exit << ". Exit" << std::endl;

    std::cout << std::endl << "~/";
}

int main() {
    bool application_running = true; //приложение запущено

    std::string filter_query;
    sort_type sort_type = sort_type::none; //тип сортировки отсутствует
    filter_type filter_type = filter_type::none; //тип сортировки отсутствует
    int subject = -1; //предмету присваиваем -1
    bool ascending = true; //по возрастанию

    const auto source_students = read_students();

    while (application_running) {
        std::vector<student> students(source_students);

        switch (filter_type)
        {
        case filter_type::fio:
            students = filter_by_name(source_students, filter_query);
            break;
        case filter_type::fives:
            students = filter_by_number_of_fives(students);
            break;
        }

        switch (sort_type) {
        case sort_type::fio:
            students = sort_by_name(students, ascending);
            break;
        case sort_type::mark:
            students = sort_by_subject(students, subject, ascending);
            break;
        }

        draw_ui(students, filter_query, filter_type, sort_type, ascending, subject);

        std::string query;
        std::cin >> query;

        commands command = (commands)atoi(query.c_str());
        switch (command) {
        case commands::filter: {
            system("clear");
            if (filter_type != filter_type::fio) {
                std::cout << "Enter filter value: ";
                std::cin >> filter_query;
                system("clear");

                filter_type = filter_type::fio;
            }
            else {
                filter_type = filter_type::none;
            }
            break;
        }
        case commands::sort_fio: {
            system("clear");

            if (sort_type != sort_type::fio) {
                std::cout << "Sort by fio ascending (y/n): ";

                std::string ascending_command;
                std::cin >> ascending_command;

                sort_type = sort_type::fio;
                ascending = ascending_command == "y" || ascending_command == "yes";
                system("clear");
            }
            else {
                sort_type = sort_type::none;
            }
            break;
        }
        case commands::sort_mark: {
            system("clear");
            if (sort_type != sort_type::mark) {
                std::cout << "Subjects: " << std::endl;
                for (int i = 0; i < subject_count; ++i) {
                    std::cout << prefix << i + 1 << ". " << subjects[i] << std::endl;
                }
                std::cout << "Choose a subject: ";
                std::cin >> subject;
                subject--;

                if (subject < 0 || subject >= subject_count) {
                    system("clear");
                    std::cout << "Unexpected subject. Try another one please!" << std::endl;
                    break;
                }

                std::cout << "Sort by mark ascending (y/n): ";

                std::string ascending_command;
                std::cin >> ascending_command;

                sort_type = sort_type::mark;
                ascending = ascending_command == "y" || ascending_command == "yes";
                system("clear");
            }
            else {
                sort_type = sort_type::none;
            }
            break;
        }
        case commands::exit:
            system("clear");
            application_running = false;
            std::cout << "Good bye!" << std::endl;
            break;
        case commands::filter_fives:
            system("clear");
            if (filter_type != filter_type::fives) {
                filter_type = filter_type::fives;
            }
            else {
                filter_type = filter_type::none;
            }
            break;
        default:
            system("clear");
            std::cout << "Unexpected command. Try another one please!" << std::endl;
            break;
        }
    }
}