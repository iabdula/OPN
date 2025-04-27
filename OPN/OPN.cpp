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



//int OPN(string expr) {
//    vector<int> stack;
//    stringstream ss(expr);
//    string token;
//
//    while (ss >> token) {
//        if (token == "+" || token == "-" || token == "*" || token == "/") {
//            int b = stack.back(); stack.pop_back();
//            int a = stack.back(); stack.pop_back();
//            if (token == "+") stack.push_back(a + b);
//            if (token == "-") stack.push_back(a - b);
//            if (token == "*") stack.push_back(a * b);
//            if (token == "/") stack.push_back(a / b);
//        }
//        else {
//            stack.push_back(stoi(token));  // добавляем число в стек
//        }
//    }
//    return stack.back(); // результат в последнем элементе стека
//}
//
//int search(int totalPages) {// это для того чтоб искать страницу с помощью g G
//    int number;
//    cout << "\nВведите номер страницы (1 - " << totalPages << "): ";
//    while (!(cin >> number) || number < 1 || number > totalPages) {
//        cin.clear();
//        cin.ignore(1000, '\n');
//        cout << "Некорректный ввод. Повторите: ";
//    }
//    return number - 1; // Потому что индексация с нуля
//}
//void Test() {
//
//    SetConsoleOutputCP(1251);
//    SetConsoleCP(1251);
//
//    vector<string> expressions = { "3 4 +", "5 1 2 + 4 * + 3 -", "7 2 3 * -" };
//    int score = 0;
//
//    for (int i = 0; i < expressions.size(); i++) {
//        system("cls");
//        cout << "Введите результат выражения: " << expressions[i] << endl;
//        int userAnswer;
//        cin >> userAnswer;
//        int correctAnswer = OPN(expressions[i]);
//
//        if (userAnswer == correctAnswer) {
//            cout << "Верно!" << endl;
//            score++;
//        }
//        else {
//            cout << "Неверно! Правильный ответ: " << correctAnswer << endl;
//        }
//        cout << "Нажмите любую клавишу для продолжения...\n";
//        _getch();
//    }
//
//    cout << "\nВы набрали " << score << " из " << expressions.size() << endl;
//    cout << "Конец теста.Примите поздравления от Абдулы и Али" << endl;
//    _getch();
//}




int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    vector<vector<string>> pages;
    loadTheory(pages);

    int pageIndex = 0;
    bool inTheory = true;

    while (inTheory) {
        showTheory(pages, pageIndex);

        int key = _getch();
        if (key == 224) { // специальная клавиша
            int arrow = _getch();
            if (arrow == 77) { // стрелка вправо
                if (pageIndex < pages.size() - 1) {
                    pageIndex++;
                }
                else {
                    // Теория закончилась — переход к практике
                    system("cls");
                    cout << "Теория окончена. Переход к практике..." << endl;
                    _getch(); // Ожидание нажатия любой клавиши
                    inTheory = false;
                }
            }
            else if (arrow == 75 && pageIndex > 0) { // стрелка влево
                pageIndex--;
            }
        }
        else if (key == 'g' || key == 'G') {
            pageIndex = selectPage(pages.size());
        }
        else {
            // Любая другая клавиша — выход
            inTheory = false;
        }
    }

    // ПРАКТИКА
    int index = 0;
    bool running = true;

    while (running) {
        showPractikaStep(index);

        cout << "\nНажмите стрелку влево для возврата назад. Любая другая клавиша — продолжить дальше.\n";

        int key = _getch();
        if (key == 224) {
            int arrow = _getch();
            if (arrow == 75 && index > 0) { // стрелка влево
                index--;
            }
            else if (arrow == 77) { // стрелка вправо
                if (index < steps.size() - 1) index++;
                else running = false;
            }
        }
        else {
            index++;
            if (index >= steps.size()) {
                running = false;
            }
        }
    }

    cout << "\nПрактика завершена!" << endl;
    return 0;
}
