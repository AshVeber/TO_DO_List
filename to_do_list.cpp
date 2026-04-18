#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

bool isNumber(const string& s) {
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
void Menu() {
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    vector<string> menu = {"Show tasks", "Add task", "Delete task", "Done tasks", "Show done tasks", "Exit"};

    cout << "----------------" << endl;
    for(size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i] << ". " << menu[i] << endl;
    }
}
void saveTask(vector<string>& tasks) {
    ofstream file("tasks.txt");
    for(string ts : tasks) {
        file << ts << endl;
    }
}
void savedoneTask(vector<string>& donetasks) {
    ofstream file("donetasks.txt");
    for(string dts : donetasks) {
        file << dts << endl;
    }
}
vector<string> loadTasks() {
    vector<string> tasks;
    ifstream file("tasks.txt");
    string line;

    while(getline(file, line)) {
        tasks.push_back(line);
    }
    return tasks;
}
vector<string> loaddoneTasks() {
    vector<string> donetasks;
    ifstream file("donetasks.txt");
    string line0;

    while(getline(file, line0)) {
        donetasks.push_back(line0);
    }
    return donetasks;
}
void addfirstTs(vector<string>& tasks) {
    cout << "You do not have tasks." << endl;
    cout << "Add tasks" << endl;
    string newTask;
    cout << ">> ";
    getline(cin, newTask);
    tasks.push_back(newTask);
    saveTask(tasks);
}
void addTs(vector<string>& tasks) {
    string task;
    cout << ">> ";
    getline(cin, task);
    tasks.push_back(task);
    saveTask(tasks);
}
void deleteTask(vector<string>& tasks) {
    cout << "Which task do ya wanna delete?" << endl;
    while(true) {
        cout << ">> ";
        string dt;
        cin >> dt;
        if(isNumber(dt)) {
            int ddt = stoi(dt);
            int index = ddt - 1;
            if(index >= 0 && index < tasks.size()) {
                tasks.erase(tasks.begin() + index);
                saveTask(tasks);
                cout << "Edited!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                break;
            }
            else {
                cout << "Incorrect input." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                continue;
            }
            
        }
        else {
            cout << "Incorrect input." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            continue;
        }
    }
}
void Tasks(const vector<string>& tasks) {
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    for(size_t i = 0; i < tasks.size(); ++i) {
        cout << " " << i + 1 << ") " << tasks[i] << endl;
    }
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    this_thread::sleep_for(chrono::seconds(3));
}
void doneTask(vector<string>& donetasks, vector<string>& tasks){
    if(tasks.empty()) {
        cout << "You do not have tasks" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
    else {
        Tasks(tasks);
        cout << "Which task is done?" << endl;
        while(true) {
            cout << ">> ";
            string donet;
            cin >> donet;
            if(isNumber(donet)) {
                int donetask = stoi(donet);
                int index0 = donetask - 1;
                if(index0 >= 0 && index0 < tasks.size()) {
                    donetasks.push_back(tasks[index0]);
                    tasks.erase(tasks.begin() + index0);
                    savedoneTask(donetasks);
                    saveTask(tasks);
                    cout << "Cool!" << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    break;
                }
                else {
                    cout << "Incorrect input." << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    continue;
                }
            }
            else {
                cout << "Incorrect input." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                continue;
            }
        }
    }
    
}
void doneTasks(vector<string>& donetasks) {
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    for(size_t j = 0; j < donetasks.size(); ++j) {
        cout << " " << j + 1 << ") " << donetasks[j] << endl;
    }
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    this_thread::sleep_for(chrono::seconds(3));
}

int main() {
    cout << "================" << endl;
    cout << "   TO DO LIST" << endl;
    cout << "================" << endl;

    vector<string> donetasks = loaddoneTasks();
    vector<string> tasks = loadTasks();

    while(true) {
        Menu();
        cout << ">> ";
        string input;
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(isNumber(input)) {
            int iinput = stoi(input);

            if(iinput == 1) {
                if(tasks.empty()) {
                    addfirstTs(tasks);
                }else {
                    Tasks(tasks);
                }
            }
            else if(iinput == 2) {
                addTs(tasks);
            }
            else if(iinput == 3) {
                Tasks(tasks);
                deleteTask(tasks);    
            }
            else if(iinput == 4) {
                doneTask(donetasks, tasks);
            }
            else if(iinput == 5) {
                doneTasks(donetasks);
            }
            else if(iinput == 6) {
                cout << "----------------" << endl;
                break;
            }
            else {
                cout << "Incorrect input." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                continue;
            }
            
        }
        else {
            cout << "Incorrect input.\n" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            continue;
        }
    }
    return 0;
}
