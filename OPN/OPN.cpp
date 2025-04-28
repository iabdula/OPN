#include <iostream>// ����
#include <fstream>//�������� � ������� ifstream
#include <conio.h>//��� ��������� ������������ (_getch)
#include <string>//��� ������ � ���������� �������� (��������� ������ string)
#include <vector>//��� �������� ����� �� ��������� 
#include <windows.h> // ��� ������� ������� ��������
#include <sstream> //��� ���
#include "teory.h"
#include "practika.h"
#include "test.h"



using namespace std;


int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    vector<vector<string>> pages;
    loadTheory(pages);

    int pageIndex = 0;
    bool inTheory = true;

    while (inTheory) {
        showTheory(pages, pageIndex);

        int key = _getch();
        if (key == 224) { // ����������� �������
            int arrow = _getch();
            if (arrow == 77) { // ������� ������
                if (pageIndex < pages.size() - 1) {
                    pageIndex++;
                }
                else {
                    // ������ ����������� � ������� � ��������
                    system("cls");
                    cout << "������ ��������.������� � ��������..." << endl;
                    _getch(); // �������� ������� ����� �������
                    inTheory = false;

                    
                }
            }
            else if (arrow == 75 && pageIndex > 0) { // ������� �����
                pageIndex--;
            }
        }
        else if (key == 'g' || key == 'G') {
            pageIndex = selectPage(pages.size());
        }
        else {
            // ����� ������ ������� � �����
            inTheory = false;
        }
    }

    // ��������
    int index = 0;
    bool running = true;

    while (running) {
        showPractikaStep(index);

        cout << "\n������� ������� ����� ��� �������� �����. ����� ������ ������� � ���������� ������.\n";

        int key = _getch();
        if (key == 224) {
            int arrow = _getch();
            if (arrow == 75 && index > 0) { // ������� �����
                index--;
            }
            else if (arrow == 77) { // ������� ������
                if (index < steps.size() - 1) index++;
                else running = false;
            }
        }
        else {
            index++;
            if (index >= steps.size()) {
                running = false;
            }
        }
    }

    system("cls");
    cout << "\n�������� ���������! ��������� � ������..." << endl;
    cout << "������� ����� ������� ��� �����������" << endl;
    _getch();

    // --- ����� ---
    vector<Test> tests;
    loadTheory(pages);
    loadTests("tests.txt", tests);
    if (!tests.empty()) {
        runTests(tests);
    }
    else {
        cout << "\n����� �� �������!" << endl;
        _getch();
    }
    return 0;
}
