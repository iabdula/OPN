
using namespace std;

void loadTheory(vector<vector<string>>& pages) {
    ifstream file("teory.txt");
    string line;
    vector<string> currentPage;

    if (!file.is_open()) {
        cerr << "�� ������� ������� ����!" << endl;
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

// ������� ��� ����������� ������
void showTheory(const vector<vector<string>>& pages, int pageIndex) {
    system("cls");
    cout << "�������� " << (pageIndex + 1) << " �� " << pages.size() << ":\n\n";
    for (const auto& l : pages[pageIndex]) {
        cout << l << endl;
    }

    cout << "\n--- ����� �������� ---\n";
    cout << "������� ������� ������ ��� ���������, ����� � ��� ����������, G ��� g ��� ������ ��������. ����� ������ � �����.\n";
}

// ������� ��� ������ ��������
int selectPage(int totalPages) {
    int page;
    cout << "\n������� � �������� (1 - " << totalPages << "):\n";
    cin >> page;
    if (page < 1 || page > totalPages) {
        cout << "�������� ����� ��������. ������� �� ������.\n";
        return 0;
    }
    return page - 1;
}