#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");
    ifstream file("teory.txt");
    string line;

    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return 1;
    }

    while (getline(file, line)) {
        if (line == "#PAGE_END") {
            cout << "\n--- Конец страницы ---\nНажмите стрелку вправо, чтобы продолжить..." << endl;

            int key = _getch();
            if (key == 224) { // спец. код клавиши
                int arrow = _getch();
                if (arrow == 77) { // 77 — стрелка вправо
                    cout << "\nПереход к следующей странице...\n" << endl;
                    system("cls");
                    continue;
                }
                else {
                    cout << "\nНажата не та стрелка. Завершаем.\n";
                    break;
                }
            }
            else {
                cout << "\nНажата не стрелка. Завершаем.\n";
                break;
            }
        }

        cout << line << endl;
    }

    file.close();
    return 0;
}
