
using namespace std;

void loadTheory(vector<vector<string>>& pages) {
    ifstream file("teory.txt");
    string line;
    vector<string> currentPage;

    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return;
    }

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
}

// Функция для отображения теории
void showTheory(const vector<vector<string>>& pages, int pageIndex) {
    system("cls");
    cout << "Страница " << (pageIndex + 1) << " из " << pages.size() << ":\n\n";
    for (const auto& l : pages[pageIndex]) {
        cout << l << endl;
    }

    cout << "\n--- Конец страницы ---\n";
    cout << "Нажмите стрелку вправо для следующей, влево — для предыдущей, G или g для выбора страницы. Любая другая — выход.\n";
}

// Функция для выбора страницы
int selectPage(int totalPages) {
    int page;
    cout << "\nПереход к странице (1 - " << totalPages << "):\n";
    cin >> page;
    if (page < 1 || page > totalPages) {
        cout << "Неверный номер страницы. Переход на первую.\n";
        return 0;
    }
    return page - 1;
}