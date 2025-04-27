#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h> // для SetConsoleOutputCP

using namespace std;

struct Test {
    string question;         // Вопрос
    vector<string> answers;  // Варианты ответов
    char correctAnswer;      // Верный вариант (a, b, c, d)
};

// Загружает тесты из teory.txt после практики
void loadTests(const string& filename, vector<Test>& tests) {
    ifstream file(filename);
    string line;
    Test tempTest;

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла с тестами!" << endl;
        return;
    }

    bool startTests = false;

    while (getline(file, line)) {
        if (line == "#TEST") {
            startTests = true;
            tempTest = Test(); // новый тест
            continue;
        }

        if (startTests) {
            if (line.find("?") != string::npos) {
                tempTest.question = line;
            }
            else if (line.find("a)") != string::npos ||
                line.find("b)") != string::npos ||
                line.find("c)") != string::npos ||
                line.find("d)") != string::npos) {
                tempTest.answers.push_back(line);
            }
            else if (line.find("Правильный ответ:") != string::npos) {
                string answer = line.substr(line.find(":") + 1);
                tempTest.correctAnswer = answer[0];
                tests.push_back(tempTest); // добавляем тест в список
            }
        }
    }

    file.close();
}

// Проходит тестирование
void runTests(const vector<Test>& tests) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int correctCount = 0;

    for (const auto& test : tests) {
        system("cls");
        cout << test.question << "\n\n";

        for (const auto& answer : test.answers) {
            cout << answer << endl;
        }

        cout << "\nВведите ваш ответ (a, b, c, d): ";
        char userAnswer;
        cin >> userAnswer;

        if (tolower(userAnswer) == tolower(test.correctAnswer)) {
            cout << "Верно!\n";
            correctCount++;
        }
        else {
            cout << "Неверно! Правильный ответ: " << test.correctAnswer << "\n";
        }

        cout << "\nНажмите любую клавишу для продолжения...\n";
        _getch();
    }

    system("cls");
    cout << "\nТесты завершены. Ваш результат: " << correctCount << " из " << tests.size() << " правильных ответов.\n";
    cout << "Нажмите любую клавишу для выхода...\n";
    _getch();
}
