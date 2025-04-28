#include <iostream>// база
#include <fstream>//работать с файлами ifstream
#include <conio.h>//для стрелочек переключения (_getch)
#include <string>//для работы с текстовыми строками (поддержка класса string)
#include <vector>//для хранения строк по страницам 
#include <windows.h> // чоб сделать консоль красивой
#include <sstream> //для ОПН
#include "teory.h"
#include "practika.h"
#include "test.h"



using namespace std;


int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
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
                    cout << "Теория окончена.Переход к практике..." << endl;
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

    system("cls");
    cout << "\nПрактика завершена! Переходим к тестам..." << endl;
    cout << "Нажмите любую клавишу для продолжения" << endl;
    _getch();

    // --- ТЕСТЫ ---
    vector<Test> tests;
    loadTheory(pages);
    loadTests("tests.txt", tests);
    if (!tests.empty()) {
        runTests(tests);
    }
    else {
        cout << "\nТесты не найдены!" << endl;
        _getch();
    }
    return 0;
}
