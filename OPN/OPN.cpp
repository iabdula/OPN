#include <iostream>// база
#include <fstream>//работать с файлами ifstream
#include <conio.h>//для стрелочек переключения (_getch)
#include <string>//для работы с текстовыми строками (поддержка класса string)
#include <vector>//для хранения строк по страницам 
#include <windows.h> // чоб сделать консоль красивой
#include <sstream> //для ОПН

using namespace std;

//практика
void ПоказатьПрактику() {
    system("cls");
    cout << "Практика по обратной польской нотации\n\n";

    // Первая практика
    cout << "Пример 1\n";
    string выражение1 = "8 5 - 2 3 + *";
    cout << "ОПН: " << выражение1 << "\n";
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
    string выражение2 = "10 2 8 * + 3 -";
    cout << "ОПН: " << выражение2 << "\n";
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
    string выражение3 = "4 2 5 * + 1 3 2 * + /";
    cout << "ОПН: " << выражение3 << "\n";
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

int EvaluateRPN(string expr) {
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

int GetPageNumber(int totalPages) {// это для того чтоб искать страницу с помощью g G
    int number;
    cout << "\nВведите номер страницы (1 - " << totalPages << "): ";
    while (!(cin >> number) || number < 1 || number > totalPages) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Некорректный ввод. Повторите: ";
    }
    return number - 1; // Потому что индексация с нуля
}
//относится к #include <windows.h>
int GetConsoleHeight() {//Без этой функции текст всегда будет начинаться с самого верха а с ней  аккуратно по центру
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int rows = 25; // дефолт как будто
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return rows;
}
void RunRPNTest() {
    vector<string> expressions = { "3 4 +", "5 1 2 + 4 * + 3 -", "7 2 3 * -" };
    int score = 0;

    for (int i = 0; i < expressions.size(); i++) {
        system("cls");
        cout << "Введите результат выражения: " << expressions[i] << endl;
        int userAnswer;
        cin >> userAnswer;
        int correctAnswer = EvaluateRPN(expressions[i]);

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
    setlocale(LC_ALL, "Ru");
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
        int consoleHeight = GetConsoleHeight();
        int contentHeight = pages[pageIndex].size() + 5; // +5  для заголовка и опускания
        int topPadding = (consoleHeight - contentHeight) / 2;

        cout << string(topPadding, '\n'); // ставим вертикально

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
                    system("cls");
                    cout << "\nВы просмотрели все страницы. Перейдём к практике!\n";
                    _getch();
                    ПоказатьПрактику();    
                    cout << "\nЭто была практика по ОПН. Нажмите любую клавишу, чтобы продолжить...";
                    _getch();                                       
                    RunRPNTest(); cout << "\nВы просмотрели все страницы. Перейдём к тесту!\n";
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
            int newIndex = GetPageNumber(pages.size()); //  номер страницы
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
