#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <limits>

bool isNumber(const std::string& s) {
    if(s.empty()) {
        return false;
    }
    for(char const &c : s) {
        if(!(isdigit(c))) {
            return false;
        }
    }
    return true;
}
void errorMess() {
    std::cout << "Incorrect input." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
void Menu() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    std::vector<std::string> menu = {"Show tasks", "Add task", "Delete task", "Done tasks", "Show done tasks", "Exit"};

    std::cout << "----------------" << std::endl;
    for(size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << ". " << menu[i] << std::endl;
    }
}
void Tasks(const std::vector<std::string>& tasks) {
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
    for(size_t i = 0; i < tasks.size(); ++i) {
        std::cout << " " << i + 1 << ") " << tasks[i] << std::endl;
    }
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}
void saveTask(std::vector<std::string>& tasks) {
    std::ofstream file("tasks.txt");
    for(std::string ts : tasks) {
        file << ts << std::endl;
    }
}
void savedoneTask(std::vector<std::string>& donetasks) {
    std::ofstream file("donetasks.txt");
    for(std::string dts : donetasks) {
        file << dts << std::endl;
    }
}
std::vector<std::string> loadTasks() {
    std::vector<std::string> tasks;
    std::ifstream file("tasks.txt");
    std::string line;

    while(getline(file, line)) {
        tasks.push_back(line);
    }
    return tasks;
}
std::vector<std::string> loaddoneTasks() {
    std::vector<std::string> donetasks;
    std::ifstream file("donetasks.txt");
    std::string line0;

    while(getline(file, line0)) {
        donetasks.push_back(line0);
    }
    return donetasks;
}
void addTs(std::vector<std::string>& tasks) {
    std::string task;
    std::cout << ">> ";
    getline(std::cin, task);
    tasks.push_back(task);
    saveTask(tasks);
}
void deleteTask(std::vector<std::string>& tasks) {
    if(tasks.empty()) {
        std::cout << "You do not have tasks." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } else {
        Tasks(tasks);
        std::cout << "Which task do ya wanna delete?" << std::endl;
        while(true) {
            std::cout << ">> ";
            std::string dt;
            std::cin >> dt;
            if(isNumber(dt)) {
                int ddt = stoi(dt);
                int index = ddt - 1;
                if(index >= 0 && index < tasks.size()) {
                    tasks.erase(tasks.begin() + index);
                    saveTask(tasks);
                    std::cout << "Edited!" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }
                else {
                    errorMess();
                    continue;
                }
                
            }
            else {
                errorMess();
                continue;
            }
        }
    }
    
}
void doneTask(std::vector<std::string>& donetasks, std::vector<std::string>& tasks){
    if(tasks.empty()) {
        std::cout << "You do not have tasks" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    else {
        Tasks(tasks);
        std::cout << "Which task is done?" << std::endl;
        while(true) {
            std::cout << ">> ";
            std::string donet;
            std::cin >> donet;
            if(isNumber(donet)) {
                int donetask = stoi(donet);
                int index0 = donetask - 1;
                if(index0 >= 0 && index0 < tasks.size()) {
                    donetasks.push_back(tasks[index0]);
                    tasks.erase(tasks.begin() + index0);
                    savedoneTask(donetasks);
                    saveTask(tasks);
                    std::cout << "Cool!" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }
                else {
                    errorMess();
                    continue;
                }
            }
            else {
                errorMess();
                continue;
            }
        }
    }
    
}
void doneTasks(std::vector<std::string>& donetasks) {
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
    for(size_t j = 0; j < donetasks.size(); ++j) {
        std::cout << " " << j + 1 << ") " << donetasks[j] << std::endl;
    }
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main() {
    std::cout << "================" << std::endl;
    std::cout << "   TO DO LIST" << std::endl;
    std::cout << "================" << std::endl;

    std::vector<std::string> donetasks = loaddoneTasks();
    std::vector<std::string> tasks = loadTasks();

    while(true) {
        Menu();
        std::cout << ">> ";
        std::string input;
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(isNumber(input)) {
            int iinput = stoi(input);

            if(iinput == 1) {
                if(tasks.empty()) {
                    std::cout << "You do not have tasks." << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }else {
                    Tasks(tasks);
                }
            }
            else if(iinput == 2) {
                addTs(tasks);
            }
            else if(iinput == 3) {
                
                deleteTask(tasks);    
            }
            else if(iinput == 4) {
                doneTask(donetasks, tasks);
            }
            else if(iinput == 5) {
                doneTasks(donetasks);
            }
            else if(iinput == 6) {
                std::cout << "----------------" << std::endl;
                break;
            }
            else {
                errorMess();
                continue;
            }
            
        }
        else {
            errorMess();
            continue;
        }
    }
    return 0;
}
