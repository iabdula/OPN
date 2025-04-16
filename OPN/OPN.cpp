#include <iostream>// база
#include <fstream>//работать с файлами ifstream
#include <conio.h>//для стрелочек переключения (_getch)
#include <string>//для работы с текстовыми строками (поддержка класса string)
#include <vector>//для хранения строк по страницам 
#include <windows.h> // чоб сделать консоль красивой
#include <sstream> //для ОПН

using namespace std;

//практика
void praktika() {
    system("cls");
    cout << "Практика по обратной польской нотации\n\n";

    // Первая практика
    cout << "Пример 1\n";
    string exp1 = "8 5 - 2 3 + *";
    cout << "ОПН: " << exp1 << "\n";
    cout << "Что означает: (8 − 5) × (2 + 3)\n\n";

    cout << "Решение:\n";
    cout << "1. 8 − 5 = 3\n";
    cout << "2. 2 + 3 = 5\n";
    cout << "3. 3 × 5 = 15\n";
    cout << "Ответ: 15\n";

    cout << "\nНажмите любую клавишу для следующего примера...\n";
    _getch();

    system("cls");

    // Вторая практика
    cout << "Пример 2\n";
    string exp2 = "10 2 8 * + 3 -";
    cout << "ОПН: " << exp2 << "\n";
    cout << "Что означает: 10 + (2 × 8) − 3\n\n";

    cout << "Решение:\n";
    cout << "1. 2 × 8 = 16\n";
    cout << "2. 10 + 16 = 26\n";
    cout << "3. 26 − 3 = 23\n";
    cout << "Ответ: 23\n";

    cout << "\nПрактика завершена. Нажмите любую клавишу...\n";
    _getch();

    system("cls");

    // Третья практика
    cout << " Пример 3\n";
    string exp3 = "4 2 5 * + 1 3 2 * + /";
    cout << "ОПН: " << exp3 << "\n";
    cout << "Что означает: (4 + (2 × 5)) / (1 + (3 × 2))\n\n";

    cout << "Решение:\n";
    cout << "1. 2 × 5 = 10\n";
    cout << "2. 4 + 10 = 14\n";
    cout << "3. 3 × 2 = 6\n";
    cout << "4. 1 + 6 = 7\n";
    cout << "5. 14 / 7 = 2\n";
    cout << "Ответ: 2\n";

    cout << "\nПрактика завершена.поздравляем\n";
    _getch();

}

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
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    //setlocale(LC_ALL, "Ru");
    ifstream file("teory.txt");
    string line;

    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return 0;
    }

    vector<vector<string>> pages;
    vector<string> currentPage;

    while (getline(file, line)) {
        if (line == "#PAGE_END") {
            pages.push_back(currentPage);
            currentPage.clear();
        }
        else {
            currentPage.push_back(line);
        }
    }

    file.close();



    int pageIndex = 0;
    while (pageIndex < pages.size()) {
        system("cls");

        cout << "Страница " << (pageIndex + 1) << " из " << pages.size() << ":\n\n";
        for (const string& l : pages[pageIndex]) {
            cout << l << endl;
        }

        cout << "\n--- Конец страницы ---\n";
        cout << "Нажмите стрелку вправо для следующей, влево — для предыдущей, G или g для выбора страницы. Любая другая — выход.\n";

        int key = _getch();
        if (key == 224) {
            int arrow = _getch();
            if (arrow == 77) { // вправо
                if (pageIndex < pages.size() - 1) {
                    pageIndex++;
                }
                else {
                    cout << "\nВы просмотрели все страницы. Перейдём к практике!\n";
                    _getch();
                    praktika();
                    system("cls");
                    cout << "\nЭто была практика по ОПН. Нажмите любую клавишу, чтобы продолжить...";
                    _getch();
                    cout << "\nТеперь попробуем пройти небольшой тест!\n";
                    _getch();
                    Test();
                    break;
                }
            }
            else if (arrow == 75) { // влево
                if (pageIndex > 0) {
                    pageIndex--;
                }
                else {
                    cout << "\nЭто первая страница.\n";
                    _getch();
                }
            }
            else {
                cout << "\nНажата не та стрелка. Завершаем.\n";
                break;
            }
        }
        else if (key == 'g' || key == 'G') {
            cout << "\nПереход к странице:\n";
            int newIndex = search(pages.size()); //  номер страницы
            pageIndex = newIndex; // Переход на указанную страницу
        }
        else {
            cout << "\nНажата не стрелка. Завершаем.\n";
            break;
        }
    }

    system("pause > NULL");
    return 0;
}

