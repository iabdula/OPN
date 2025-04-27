#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h> // ��� SetConsoleOutputCP

using namespace std;

struct Test {
    string question;         // ������
    vector<string> answers;  // �������� �������
    char correctAnswer;      // ������ ������� (a, b, c, d)
};

// ��������� ����� �� teory.txt ����� ��������
void loadTests(const string& filename, vector<Test>& tests) {
    ifstream file(filename);
    string line;
    Test tempTest;

    if (!file.is_open()) {
        cerr << "������ �������� ����� � �������!" << endl;
        return;
    }

    bool startTests = false;

    while (getline(file, line)) {
        if (line == "#TEST") {
            startTests = true;
            tempTest = Test(); // ����� ����
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
            else if (line.find("���������� �����:") != string::npos) {
                string answer = line.substr(line.find(":") + 1);
                tempTest.correctAnswer = answer[0];
                tests.push_back(tempTest); // ��������� ���� � ������
            }
        }
    }

    file.close();
}

// �������� ������������
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

        cout << "\n������� ��� ����� (a, b, c, d): ";
        char userAnswer;
        cin >> userAnswer;

        if (tolower(userAnswer) == tolower(test.correctAnswer)) {
            cout << "�����!\n";
            correctCount++;
        }
        else {
            cout << "�������! ���������� �����: " << test.correctAnswer << "\n";
        }

        cout << "\n������� ����� ������� ��� �����������...\n";
        _getch();
    }

    system("cls");
    cout << "\n����� ���������. ��� ���������: " << correctCount << " �� " << tests.size() << " ���������� �������.\n";
    cout << "������� ����� ������� ��� ������...\n";
    _getch();
}
