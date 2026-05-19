#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct Subtask {
    std::string text;
    bool done;
};
struct Task {
    std::string text;
    bool done;
    std::vector<Subtask> subtasks;
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
        std::string mark = tasks[i].done ? "[x]" : "[ ]";
        std::cout << i+1 << ". " << mark << " " << tasks[i].text << std::endl;
        for(size_t j = 0; j < tasks[i].subtasks.size(); ++j) {
            std::string submark = tasks[i].subtasks[j].done ? "[x]" : "[ ]";
            std::cout << "   " << j+1 << " - " << tasks[i].subtasks[j].text << " " << submark << std::endl;
        }
    }
    std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
}
void saveTask(std::vector<Task>& tasks) {
    std::ofstream file("tasks.txt");
    for(const Task& t : tasks) {
        file << t.text << "|" << t.done;
        if(!t.subtasks.empty()) {
            file << "|";
            for(size_t i = 0; i < t.subtasks.size(); ++i) {
                file << t.subtasks[i].text << ":" << t.subtasks[i].done;
                if(i+1 < t.subtasks.size()) file << ",";
            }
        }
        file << "\n";
    }
}
void doneTask(std::vector<Task>& tasks){
    while(true) {
        Tasks(tasks);
        std::cout << "Which task is done? (press 'x' to exit)\n>> ";
        std::string input;
        std::getline(std::cin, input);
        if(input == "x" || input == "X") break;
        if(input.empty()) {
            std::cout << "You did not write anything" << std::endl;
            continue;
        }
        if(!isNumber(input)) {
            std::cout << "That's not a number." << std::endl;
            continue;
        }            
        int index = stoi(input) - 1;
        if(index < 0 || index >= tasks.size()) {
            std::cout << "Enter the valid number." << std::endl;
            continue;
        }      
        if(!tasks[index].subtasks.empty()) {
            std::cout << "What is done?\n a) task\n b) subtask\n>> ";
            std::string choice;
            getline(std::cin, choice);
            if(choice == "a" || choice == "A") {
                if(!tasks[index].done) {
                    tasks[index].done = true;
                    for(size_t i = 0; i < tasks[index].subtasks.size(); ++i) {
                        tasks[index].subtasks[i].done = true;
                    }
                    saveTask(tasks);
                    std::cout << "Done!" << std::endl;                   
                }else {
                    std::cout << "Your tasks are done!" << std::endl;
                }
               
            }else if(choice == "b" || choice == "B") {
                for(size_t i = 0; i < tasks[index].subtasks.size(); ++i) {
                    std::string submark = tasks[index].subtasks[i].done ? "[x]" : "[ ]";
                    std::cout << i+1 << ". " << tasks[index].subtasks[i].text << " " << submark << std::endl;
                }
                std::cout << "Which subtask is done?\n>> ";
                std::string subinput;
                getline(std::cin, subinput);
                if(!isNumber(subinput)) {
                    std::cout << "That's not a number" << std::endl;
                    continue;
                }
                int subindex = stoi(subinput) - 1;
                if(subindex < 0 || subindex >= (int)tasks[index].subtasks.size()) {
                    std::cout << "Enter the valid number." << std::endl;
                    continue;
                }
                tasks[index].subtasks[subindex].done = true;
                saveTask(tasks);
                std::cout << "Subtask is done." << std::endl;
            }
        }
        tasks[index].done = true;
        saveTask(tasks);
        std::cout << "Done!" << std::endl; 
    }
}
std::vector<Task> loadTasks() {
    std::vector<Task> tasks;
    std::ifstream file("tasks.txt");
    std::string line;

    while(getline(file, line)) {
        Task t;
        size_t pos1 = line.find('|');
        if(pos1 == std::string::npos) {
            t.text = line;
            t.done = false;
            tasks.push_back(t);
            continue;
        }
        t.text = line.substr(0, pos1);
        size_t pos2 = line.find('|', pos1 + 1);
        std::string donePart = line.substr(pos1 + 1, pos2 - pos1 - 1);
        t.done = (donePart == "1");
        if(pos2 != std::string::npos) {
            std::string subtasksPart = line.substr(pos2 + 1);
            std::stringstream ss(subtasksPart);
            std::string sub;
            while(getline(ss, sub, ',')) {
                if(!sub.empty()) {
                    Subtask st;                  
                    size_t sep = sub.find(':');
                    st.text = sub.substr(0, sep);
                    st.done = (sub.substr(sep + 1) == "1");
                    t.subtasks.push_back(st);
                }
            }
        }
        tasks.push_back(t);
    }
    return tasks;
}
void taskfolder(std::vector<Task>& tasks) {
    Task t;
    t.done = false;
    std::cout << "Folder name: ";
    getline(std::cin, t.text);
    if(t.text.empty()) {
        std::cout << "The folder can not be empty." << std::endl;
        return;
    }
    while(true) {    
        std::string sub;
        std::cout << "Subtasks (press 'x' to exit.)\n>> ";
        getline(std::cin, sub);
        if(sub == "x" || sub == "X") break;
        if(sub.empty()) {
            std::cout << "Enter the subtask." << std::endl;
            continue;
        }
        Subtask st;
        st.text = sub;
        st.done = false;
        t.subtasks.push_back(st);
    }
    tasks.push_back(t);
    saveTask(tasks);
    std::cout << "Added!" << std::endl;
}
void addTs(std::vector<Task>& tasks) {
    std::string input;
    while(true) {
        std::cout << "----------------\nAdd:\n a) task\n b) folder\n(press 'x' to exit)\n>> ";
        getline(std::cin, input);
        if(input.empty()) {
            std::cout << "You did not write the task." << std::endl;
            continue;
        }else 
        if(isNumber(input)) {
            std::cout << "That's not a task." << std::endl;
            continue;
        }else
        if(input == "a" || input == "A") {
            Task t;
            t.done = false;
            while(true) {
            std::cout << "Task name (press 'x' to exit.)\n>> ";
            getline(std::cin, t.text);
            if(t.text == "x" || t.text == "X") break;
            if(t.text.empty()){
                std::cout << "Enter the task." << std::endl;
                continue;
            }
            tasks.push_back(t);
            saveTask(tasks);               
            }

        }else
        if(input == "b" || input == "B") {
            taskfolder(tasks);
        }else
        if(input == "x" || input == "X") break;
    }
}
void deleteTask(std::vector<Task>& tasks) {
    std::string input;
    if(tasks.empty()) {
        std::cout << "You do not have tasks." << std::endl;
    }
    while(true) {
        Tasks(tasks);
        std::cout << "Which task to delete? (Press 'x' to exit)\n>> ";
        std::string input;
        getline(std::cin, input);
        if(input == "x" || input == "X") break;
        if(input.empty()) {
            std::cout << "You did not write the task." << std::endl;
            continue;
        }
        if(!isNumber(input)) {
            std::cout << "That's not a number." << std::endl;
            continue;
        }
        int index = stoi(input) - 1;
        if(index < 0 || index >= (int)tasks.size()) {
            std::cout << "Enter the valid number." << std::endl;
            continue;
        }
        if(!tasks[index].subtasks.empty()) {
            std::cout << "Delete:\n a) whole task\n b) subtask\n>> ";
            std::string choice;
            getline(std::cin, choice);
            if(choice == "b" || choice == "B") {
                for(size_t i = 0; i < tasks[index].subtasks.size(); ++i) {
                    std::cout << i+1 << ". " << tasks[index].subtasks[i].text << std::endl;
                }
                std::cout << "Which subtask to delete?\n>> ";
                std::string subinput;
                getline(std::cin, subinput);
                if(!isNumber(subinput)) {
                    std::cout << "That's not a number." << std::endl;
                    continue;
                }
                int subindex = stoi(subinput) - 1;
                if(subindex < 0 || subindex >= (int)tasks[index].subtasks.size()) {
                    std::cout << "Enter the valid number." << std::endl;
                    continue;
                }
                tasks[index].subtasks.erase(tasks[index].subtasks.begin() + subindex);
                saveTask(tasks);
                std::cout << "Subtask deleted." << std::endl;
                break;
            }
        }
        tasks.erase(tasks.begin() + index);
        saveTask(tasks);
        std::cout << "Task deleted." << std::endl;
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
