


void loadTheory(std::vector<std::vector<std::string>>& pages) {
    std::ifstream file("teory.txt");
    std::string line;
    std::vector<std::string> currentPage;

    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ����!" << std::endl;
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

// ������� ��� ����������� ������
void showTheory(const std::vector<std::vector<std::string>>& pages, int pageIndex) {
    system("cls");
    std::cout << "�������� " << (pageIndex + 1) << " �� " << pages.size() << ":\n\n";
    for (const auto& l : pages[pageIndex]) {
        std::cout << l << std::endl;
    }

    std::cout << "\n--- ����� �������� ---\n";
    std::cout << "������� ������� ������ ��� ���������, ����� � ��� ����������, G ��� g ��� ������ ��������. ����� ������ � �����.\n";
}

// ������� ��� ������ ��������
int selectPage(int totalPages) {
    int page;
    std::cout << "\n������� � �������� (1 - " << totalPages << "):\n";
    std::cin >> page;
    if (page < 1 || page > totalPages) {
        std::cout << "�������� ����� ��������. ������� �� ������.\n";
        return 0;
    }
    return page - 1;
}