


void loadTheory(std::vector<std::vector<std::string>>& pages) {
    std::ifstream file("teory.txt");
    std::string line;
    std::vector<std::string> currentPage;

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return;
    }

    while (std::getline(file, line)) {
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
void showTheory(const std::vector<std::vector<std::string>>& pages, int pageIndex) {
    system("cls");
    std::cout << "Страница " << (pageIndex + 1) << " из " << pages.size() << ":\n\n";
    for (const auto& l : pages[pageIndex]) {
        std::cout << l << std::endl;
    }

    std::cout << "\n--- Конец страницы ---\n";
    std::cout << "Нажмите стрелку вправо для следующей, влево — для предыдущей, G или g для выбора страницы. Любая другая — выход.\n";
}

// Функция для выбора страницы
int selectPage(int totalPages) {
    int page;
    std::cout << "\nПереход к странице (1 - " << totalPages << "):\n";
    std::cin >> page;
    if (page < 1 || page > totalPages) {
        std::cout << "Неверный номер страницы. Переход на первую.\n";
        return 0;
    }
    return page - 1;
}