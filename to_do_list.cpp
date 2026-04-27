#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <limits>

struct Task {
    std::string text;
    bool done;
};
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
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<std::string> menu = {"Show tasks", "Add task", "Delete task", "Done tasks", "Exit"};

    std::cout << "----------------" << std::endl;
    for(size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << ". " << menu[i] << std::endl;
    }
}
void Tasks(const std::vector<Task>& tasks) {
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
    for(size_t i = 0; i < tasks.size(); ++i) {
        if(tasks[i].done) {
            std::cout << "[x] ";
        } else {
            std::cout << "[ ] ";
        }
        std::cout << tasks[i].text << std::endl;
    }
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void saveTask(std::vector<Task>& tasks) {
    std::ofstream file("tasks.txt");
    for(const Task& t : tasks) {
        file << t.text << "|" << t.done << std::endl;
    }
}
void doneTask(std::vector<Task>& tasks){
    Tasks(tasks);
    std::cout << "Which task is done?" << std::endl;
    while(true) {
        std::cout << ">> ";
        std::string input;
        std::cin >> input;
        if(isNumber(input)) {
            int donetask = stoi(input);
            int index = donetask - 1;
            if(index >= 0 && index < tasks.size()) {
                if(tasks[index].done) {
                    std::cout << "Your tasks are done!" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                } else {
                    tasks[index].done = true;
                    saveTask(tasks);
                    std::cout << "Cool!" << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }
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
std::vector<Task> loadTasks() {
    std::vector<Task> tasks;
    std::ifstream file("tasks.txt");
    std::string line;

    while(getline(file, line)) {
        Task t;
        size_t pos = line.find('|');
        if(pos != std::string::npos) {
            t.text = line.substr(0, pos);
            std::string donePart = line.substr(pos + 1);
            if(donePart == "1") {
                t.done = true;
            } else {
                t.done = false;
            }
        } else {
            t.text = line;
            t.done = false;
        }
        tasks.push_back(t);
    }
    return tasks;
}
void addTs(std::vector<Task>& tasks) {
    std::string task;
    std::cout << "----------------\nAdd task\n>> ";
    getline(std::cin, task);
    Task t;
    t.text = task;
    t.done = false;
    tasks.push_back(t);
    saveTask(tasks);
}
void deleteTask(std::vector<Task>& tasks) {
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

int main() {
    std::cout << "================" << std::endl;
    std::cout << "   TO DO LIST" << std::endl;
    std::cout << "================" << std::endl;

    
    std::vector<Task> tasks = loadTasks();

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
                doneTask(tasks);
            }
            else if(iinput == 5) {
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
