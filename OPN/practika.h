    #pragma once
    #include <iostream>
    #include <vector>
    #include <windows.h>
    #include <conio.h>
    using namespace std;

    void printLineWithHighlight(const string& line) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12); // 12 — ярко-красный
        cout << line;
        SetConsoleTextAttribute(hConsole, 7);  // Сброс на обычный белый
    }

    vector<pair<string, string>> steps = {
     { "int OPN(string expr) {", "Объявляется функция OPN, принимающая строку выражения." },
     { "    vector<int> stack;", "Создаётся стек для хранения чисел." },
     { "    stringstream ss(expr);", "Создаётся поток для построчного считывания выражения." },
     { "    string token;", "Создаётся переменная для хранения текущего токена." },
     { "    while (ss >> token) {", "Цикл: пока есть токены в выражении, читаем их по одному." },
     { "        if (token == \"+\" || token == \"-\" || token == \"*\" || token == \"/\") {", "Если токен — оператор (+, -, *, /)." },
     { "            int b = stack.back(); stack.pop_back();", "Берём последний элемент стека (b) и удаляем его." },
     { "            int a = stack.back(); stack.pop_back();", "Берём следующий элемент стека (a) и удаляем его." },
     { "            if (token == \"+\") stack.push_back(a + b);", "Если токен '+', складываем числа и кладём в стек." },
     { "            if (token == \"-\") stack.push_back(a - b);", "Если '-', вычитаем b из a и кладём в стек." },
     { "            if (token == \"*\") stack.push_back(a * b);", "Если '*', умножаем a на b и кладём в стек." },
     { "            if (token == \"/\") stack.push_back(a / b);", "Если '/', делим a на b и кладём в стек." },
     { "        }", "Конец блока оператора." },
     { "        else {", "Если токен — это число, а не оператор." },
     { "            stack.push_back(stoi(token));", "Преобразуем строку в число и кладём в стек." },
     { "        }", "Конец блока числа." },
     { "    }", "Конец цикла обработки всех токенов." },
     { "    return stack.back();", "Возвращаем результат (последнее число в стеке)." },
     { "}", "Конец функции." }
    };

    // Функция для отображения одного шага
    void showPractikaStep(int index) {
        system("cls");
        cout << "Шаг " << (index + 1) << " из " << steps.size() << ":\n\n";
        printLineWithHighlight(steps[index].first);  // Подсвечиваем код
        cout << endl;
        cout << steps[index].second << endl;  // Пояснение без подсветки
    }
