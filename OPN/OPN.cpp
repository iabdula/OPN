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

//практика
//void praktika() {
//
//    SetConsoleOutputCP(1251);
//    SetConsoleCP(1251);
//
//    system("cls");
//    cout << "Практика по обратной польской нотации\n\n";
//
//    // Первая практика
//    cout << "Пример 1\n";
//    string exp1 = "8 5 - 2 3 + *";
//    cout << "ОПН: " << exp1 << "\n";
//    cout << "Что означает: (8 − 5) × (2 + 3)\n\n";
//
//    cout << "Решение:\n";
//    cout << "1. 8 − 5 = 3\n";
//    cout << "2. 2 + 3 = 5\n";
//    cout << "3. 3 × 5 = 15\n";
//    cout << "Ответ: 15\n";
//
//    cout << "\nНажмите любую клавишу для следующего примера...\n";
//    _getch();
//
//    system("cls");
//
//    // Вторая практика
//    cout << "Пример 2\n";
//    string exp2 = "10 2 8 * + 3 -";
//    cout << "ОПН: " << exp2 << "\n";
//    cout << "Что означает: 10 + (2 × 8) − 3\n\n";
//
//    cout << "Решение:\n";
//    cout << "1. 2 × 8 = 16\n";
//    cout << "2. 10 + 16 = 26\n";
//    cout << "3. 26 − 3 = 23\n";
//    cout << "Ответ: 23\n";
//
//    cout << "\nПрактика завершена. Нажмите любую клавишу...\n";
//    _getch();
//
//    system("cls");
//
//    // Третья практика
//    cout << " Пример 3\n";
//    string exp3 = "4 2 5 * + 1 3 2 * + /";
//    cout << "ОПН: " << exp3 << "\n";
//    cout << "Что означает: (4 + (2 × 5)) / (1 + (3 × 2))\n\n";
//
//    cout << "Решение:\n";
//    cout << "1. 2 × 5 = 10\n";
//    cout << "2. 4 + 10 = 14\n";
//    cout << "3. 3 × 2 = 6\n";
//    cout << "4. 1 + 6 = 7\n";
//    cout << "5. 14 / 7 = 2\n";
//    cout << "Ответ: 2\n";
//
//    cout << "\nПрактика завершена.поздравляем\n";
//    _getch();
//
//}

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

    std::vector<std::vector<std::string>> pages;
    int pageIndex = 0;

    // Загружаем теорию в память
    loadTheory(pages);  // Функция для загрузки страниц теории

    while (true) {
        // Отображаем текущую страницу теории
        showTheory(pages, pageIndex);

        int key = _getch();  // Считываем ввод

        if (key == 224) {  // Если нажата стрелка
            int arrow = _getch();
            if (arrow == 77) {  // вправо
                if (pageIndex < pages.size() - 1) {
                    pageIndex++;
                }
                else {
                    std::cout << "\nВы просмотрели все страницы. Перейдём к практике!\n";
                    //praktika();  // Переход к практике
                    system("cls");
                    Test();  // Переход к тесту
                    break;
                }
            }
            else if (arrow == 75) {  // влево
                if (pageIndex > 0) {
                    pageIndex--;
                }
            }
        }
        else if (key == 'g' || key == 'G') {  // Переход к странице
            pageIndex = selectPage(pages.size());
        }
        else {  // Выход из программы
            std::cout << "\nЗавершаем программу.\n";
            break;
        }
    }

    system("pause > NULL");
    return 0;
}