#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#undef max
#undef min

class Menu {
private:
    enum EStates {
        EForceExit = -1,
        EInvalidInput = -2
    };

    struct Task {
        std::string Name = "";
        std::function<void()> Func;
    };

    std::vector<Task> Tasks;
    std::string ResetPrompt = "Do you want to try again? (y/n)";
    std::string SelectPrompt = "Enter Number Of Task :";
    bool bForceExit = false;

    bool ExecuteTask(int _index);

public:
    Menu(const std::vector<Task>& _TaskList) : Tasks(_TaskList) {};

    void SetResetPrompt(std::string _prompt);
    void SetSelectPrompt(std::string _prompt);

    void ShowTasks();
    void SelectTask();
    void StartUp(bool _inf = true, bool _resetprompt = true);
};

void Menu::SetResetPrompt(std::string _prompt) {
    ResetPrompt = _prompt;
}

void Menu::SetSelectPrompt(std::string _prompt) {
    SelectPrompt = _prompt;
}

void Menu::ShowTasks() {
    for (int i = 0; i < Tasks.size(); i++) {
        std::cout << i + 1 << " - "
                  << (Tasks.at(i).Name.empty() ? "Task" + std::to_string(i + 1) : Tasks.at(i).Name)
                  << '\n';
    }
    std::cout << "\n0 - Exit\n";
}

bool Menu::ExecuteTask(int _index) {
    if (_index == EStates::EForceExit) {
        bForceExit = true;
        return true;
    }
    if (_index < Tasks.size() && _index >= 0) {
        Tasks.at(_index).Func();
        return true;
    }
    else {
        std::cerr << "Invalid Input. Please Try Again!\n";
        return false;
    }
}

void Menu::SelectTask() {
    int n;
    do {
        std::cin >> n;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            n = EStates::EInvalidInput;
        }
    } while (!ExecuteTask(n - 1));
}

void Menu::StartUp(bool _inf, bool _resetprompt) {
    char Input = ' ';

    std::cout << "Enter Number Of Task :" << '\n';
    ShowTasks();
    SelectTask();

    while (_inf && !bForceExit) {
        if (_resetprompt) {
            std::cin.clear();
            std::cout << ResetPrompt << '\n';
            std::cin >> Input;
            if (Input == 'n') {
                _inf = false;
            }
        }
        if (Input == 'y' || !_resetprompt) {
            std::cout << "Enter Number Of Task : \n";
            ShowTasks();
            SelectTask();
        }
    }
}
