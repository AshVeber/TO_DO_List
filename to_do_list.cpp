#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Task {
    std::string text;
    bool done;
};
bool isNumber(const std::string& s) {
    if(s.empty()) {
        return 0;
    }
    for(char const &c : s) {
        if(!(isdigit(c))) {
            return 0;
        }
    }
    return 1;
}
void Menu() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<std::string> menu = {"Show tasks", "Add task", "Delete task", "Done task", "Exit"};
    std::cout << "----------------" << std::endl;
    for(size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << ". " << menu[i] << std::endl;
    }
}
void Tasks(const std::vector<Task>& tasks) {
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
    for(size_t i = 0; i < tasks.size(); ++i) {
        if(tasks[i].done) {
            std::cout << i + 1 << ". [x] " << tasks[i].text << std::endl;
        } else {
            std::cout << i + 1 << ". [ ] " << tasks[i].text << std::endl;
        }
    }
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
}
void saveTask(std::vector<Task>& tasks) {
    std::ofstream file("tasks.txt");
    for(const Task& t : tasks) {
        file << t.text << "|" << t.done << std::endl;
    }
}
void doneTask(std::vector<Task>& tasks){
    while(true) {
        Tasks(tasks);
        std::cout << "Which task is done? (press 'x' to exit)\n>> ";
        std::string input;
        std::getline(std::cin, input);
        char ch = input[0];
        if(ch == 'x'|| ch == 'X') {
            break;
        }else {
            if(input.empty()) {
                std::cout << "You did not write anything" << std::endl;
                continue;
            }else {
                if(isNumber(input)) {
                    int iinput = stoi(input);
                    int index = iinput - 1;
                    if(index >= 0 && index < tasks.size()) {
                        if(tasks[index].done) {
                            std::cout << "Your tasks are done!" << std::endl;
                            break;
                        } else {
                            tasks[index].done = true;
                            saveTask(tasks);
                            std::cout << "Cool!" << std::endl;
                            break;
                        }
                    }
                    else {
                        std::cout << "Enter the valid number." << std::endl;
                        continue;
                    }
                }
                else {
                    std::cout << "That's not a number." << std::endl;
                    continue;
                }
            }
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
    std::string input;
    while(true) {
        std::cout << "----------------\nAdd task. (press 'x' to exit)\n>> ";
        getline(std::cin, input);
        char ch = input[0];
        if(ch == 'x' || ch == 'X') {
            break;
        }else {
            if(input.empty()) {
                std::cout << "You did not write the task." << std::endl;
                continue;
            }else 
            if(isNumber(input)) {
                std::cout << "That's not a task." << std::endl;
                continue;
            }else {
                Task t;
                t.text = input;
                t.done = false;
                tasks.push_back(t);
                saveTask(tasks);
                break;
            }
        }

    }
}
void deleteTask(std::vector<Task>& tasks) {
    std::string input;
    if(tasks.empty()) {
        std::cout << "You do not have tasks." << std::endl;
    } else {
        while(true) {
            Tasks(tasks);
            std::cout << "Which task do ya wanna delete? (Press 'x' to exit)\n>> " << std::endl;
            char ch = input[0];
            std::getline(std::cin, input);
            if(ch == 'x' || ch == 'X') {
                break;
            }else {
                if(input.empty()) {
                    std::cout << "You did not write the task." << std::endl;
                    continue;
                }else {
                    if(isNumber(input)) {
                        int iinput = stoi(input);
                        int index = iinput - 1;
                        if(index >= 0 && index < tasks.size()) {
                            tasks.erase(tasks.begin() + index);
                            saveTask(tasks);
                            std::cout << "Edited!" << std::endl;
                            break;
                        }
                        else {
                            std::cout << "Enter the valid number." << std::endl;
                            continue;
                        } 
                    }
                    else {
                        std::cout << "That's not a number." << std::endl;
                        continue;
                    }
                }
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
        std::getline(std::cin, input);
        if(input.empty()) {
            std::cout << "You did not write the task." << std::endl;
            continue;
        }else {
            if(isNumber(input)) {
                int iinput = stoi(input);
                if(iinput == 1) {
                    if(tasks.empty()) {
                        std::cout << "You do not have tasks." << std::endl;
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
                    std::cout << "Enter the valid number." << std::endl;
                    continue;
                }
            }
            else {
                std::cout << "That's not a number." << std::endl;
                continue;
            }
        }
    }
    return 0;
}
