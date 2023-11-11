#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/*12.Имеется текстовый файл, состоящий из нескольких разделов и подразделов. Разделы нумеруются одной цифрой
(например: 1), подразделы несколькими цифрами, разделенными точкой. Сформировать выходной файл, в котором
сначала будет идти оглавление текста (без номеров страниц, только заголовки), а затем сам текст. Других цифр,
кроме номеров разделов, в тексте нет. Подзаголовки в оглавлении должны быть сдвинуты с помощью пробелов вправо.*/

//считает, сколько раз символ character встретился в строке line
int count(std::string line, char c) {
    int count = 0;

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == c)
            count++;
    }

    return count;
}

//проверка, является ли символ цифрой
bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

//проверка, является ли строка заголовком
int heading_level(std::string line) {
    int start = line.find_first_not_of(" \t"); //пропускаем пробелы и табуляцию (найти индекс первого символа, который не " " и не "\t")
    if (start == std::string::npos || !is_digit(line[start])) //если такого символа нет, или он не строка, то это не заголовок
        return 0;

    int end = line.find(' ', start); //найти индекс пробела, между числом и строкой
    std::string number = line.substr(start, end - start); //обрезать строку от start до end. То есть в number будет лежать, к примеру, "123.45."

    return count(number, '.'); //вернуть количество точек
}

int main() {
    std::ifstream infile("input.txt");
    std::ofstream outfile("output.txt");

    if (!infile.is_open() || !outfile.is_open()) {
        return 1;
    }

    std::string line;
    std::vector<std::string> allLines;

    while (getline(infile, line)) {
        allLines.push_back(line);
    }

    for (int i = 0; i < allLines.size(); i++) {
        std::string line = allLines[i];
        int level = heading_level(line);
        switch (level) {
        case 1:
            outfile << " " << line.substr(line.find_first_not_of(" \t")) << std::endl;
            break;
        case 2:
            outfile << "    " << line.substr(line.find_first_not_of(" \t")) << std::endl;
            break;
        case 3:
            outfile << "         " << line.substr(line.find_first_not_of(" \t")) << std::endl;
            break;
        }
    }

    outfile << std::endl << "---------------------" << std::endl << std::endl;

    for (int i = 0; i < allLines.size(); i++) {
        outfile << allLines[i] << std::endl;
    }

    infile.close();
    outfile.close();

    return 0;
}