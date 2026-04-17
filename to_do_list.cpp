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
    vector<int> nums = {1, 2, 3, 4, 5};
    vector<string> menu = {"Show tasks", "Add task", "Delete task", "Done tasks", "Exit"};

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
vector<string> loadTasks() {
    vector<string> tasks;
    ifstream file("tasks.txt");
    string line;

    while(getline(file, line)) {
        tasks.push_back(line);
    }
    return tasks;
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
void Tasks(vector<string>& tasks) {
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    for(size_t i = 0; i < tasks.size(); ++i) {
        cout << " " << i + 1 << ") " << tasks[i] << endl;
    }
    cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    this_thread::sleep_for(chrono::seconds(3));
}

int main() {
    cout << "================" << endl;
    cout << "   TO DO LIST" << endl;
    cout << "================" << endl;

    while(true) {
        Menu();
        vector<string> tasks = loadTasks();

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
            else if(iinput == 5) {
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
