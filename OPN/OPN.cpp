#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;
int GetPageNumber(int totalPages) {
    int number;
    cout << "\nВведите номер страницы (1 - " << totalPages << "): ";
    while (!(cin >> number) || number < 1 || number > totalPages) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Некорректный ввод. Повторите: ";
    }
    return number - 1; // Потому что индексация с нуля
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
                    cout << "\nЭто последняя страница.\n";
                    _getch();
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
            int newIndex = GetPageNumber(pages.size()); // Запрашиваем номер страницы
            pageIndex = newIndex; // Переходим на указанную страницу
        }
        else {
            cout << "\nНажата не стрелка. Завершаем.\n";
            break;
        }
    }

    system("pause > NULL");
    return 0;
}
