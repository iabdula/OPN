#include <iostream>// база
#include <fstream>//работать с файлами ifstream
#include <conio.h>//для стрелочек переключения (_getch)
#include <string>//для работы с текстовыми строками (поддержка класса string)
#include <vector>//для хранения строк по страницам 
#include <windows.h> // чоб сделать консоль красивой
#include <sstream> //для ОПН
#include "teory.h"
#include "practika.h"


using namespace std;



int OPN(string expr) {
    vector<int> stack;
    stringstream ss(expr);
    string token;

    while (ss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = stack.back(); stack.pop_back();
            int a = stack.back(); stack.pop_back();
            if (token == "+") stack.push_back(a + b);
            if (token == "-") stack.push_back(a - b);
            if (token == "*") stack.push_back(a * b);
            if (token == "/") stack.push_back(a / b);
        }
        else {
            stack.push_back(stoi(token));  // добавляем число в стек
        }
    }
    return stack.back(); // результат в последнем элементе стека
}

int search(int totalPages) {// это для того чтоб искать страницу с помощью g G
    int number;
    cout << "\nВведите номер страницы (1 - " << totalPages << "): ";
    while (!(cin >> number) || number < 1 || number > totalPages) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Некорректный ввод. Повторите: ";
    }
    return number - 1; // Потому что индексация с нуля
}
void Test() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    vector<string> expressions = { "3 4 +", "5 1 2 + 4 * + 3 -", "7 2 3 * -" };
    int score = 0;

    for (int i = 0; i < expressions.size(); i++) {
        system("cls");
        cout << "Введите результат выражения: " << expressions[i] << endl;
        int userAnswer;
        cin >> userAnswer;
        int correctAnswer = OPN(expressions[i]);

        if (userAnswer == correctAnswer) {
            cout << "Верно!" << endl;
            score++;
        }
        else {
            cout << "Неверно! Правильный ответ: " << correctAnswer << endl;
        }
        cout << "Нажмите любую клавишу для продолжения...\n";
        _getch();
    }

    cout << "\nВы набрали " << score << " из " << expressions.size() << endl;
    cout << "Конец теста.Примите поздравления от Абдулы и Али" << endl;
    _getch();
}




int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    //setlocale(LC_ALL, "Ru");

    vector<vector<string>> pages;
    vector<string> steps;
    string code;

    int pageIndex = 0;
    int index = 0;


    // Загружаем теорию в память
    loadTheory(pages);
    loadPractice(code, steps);

    while (true) {
        // Отображаем текущую страницу теории
        showTheory(pages, pageIndex);
        praktika(index,steps);

        int key = _getch();  // Считываем ввод

        if (key == 224) {  // Если нажата стрелка
            int arrow = _getch();
            if (arrow == 77) {  // вправо
                if (pageIndex < pages.size() - 1) {
                    pageIndex++;
                }
                else if (index < steps.size() - 1) {
                    index++;
                }
                else {
                    break;
                }
            }
            else if (arrow == 75) {  // влево
                if (pageIndex > 0) {
                    pageIndex--;
                }
                else if (index > 0) {
                    index--;
                }
            }
        }
        else if (key == 'g' || key == 'G') {  // Переход к странице
            pageIndex = selectPage(pages.size());
        }
        else {  // Выход из программы
            cout << "\nЗавершаем программу.\n";
            break;
        }
    }

    system("pause > NULL");
    return 0;
}