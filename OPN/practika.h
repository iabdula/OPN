using namespace std;

void loadPractice(string& codeBlock, vector<string>& steps) {
    ifstream file("teory.txt");
    string line;
    bool inCode = false, inPractice = false;

    while (getline(file, line)) {
        if (line == "#PRAKTIKA_BEGIN") {
            inPractice = true;
            continue;
        }
        if (line == "#PRAKTIKA_END") break;

        if (inPractice) {
            if (line == "#CODE_BEGIN") {
                inCode = true;
                continue;
            }
            if (line == "#CODE_END") {
                inCode = false;
                continue;
            }

            if (inCode) {
                codeBlock += line + "\n";
            }
            else if (line.find("#STEP") == 0) {
                steps.push_back(line.substr(6)); // всё после "#STEP "
            }
        }
    }

    file.close();
}

void praktika(int index, const vector<string>& steps) {
    system("cls");

    cout << "ПРАКТИКА: Алгоритм обратной польской нотации\n\n";
    cout << "ШАГ " << (index + 1) << " из " << steps.size() << ":\n\n";
    cout << steps[index] << "\n\n";
    cout << "Стрелка влево/вправо — листать шаги. Любая другая клавиша — выйти.\n";
}