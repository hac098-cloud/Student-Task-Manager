#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

class Task {
public:
    string title;
    string deadline;
    int priority;
    bool completed;

    Task() {
        title = "";
        deadline = "";
        priority = 0;
        completed = false;
    }

    Task(string t, string d, int p, bool c = false) {
        title = t;
        deadline = d;
        priority = p;
        completed = c;
    }
};

class TaskManager {
private:
    vector<Task> tasks;
    const string filename = "tasks.txt";

public:
    void loadFromFile() {
        ifstream inFile(filename);
        if (!inFile) {
            return;
        }

        tasks.clear();
        string title, deadline;
        int priority;
        bool completed;

        while (getline(inFile, title)) {
            getline(inFile, deadline);
            inFile >> priority;
            inFile >> completed;
            inFile.ignore(numeric_limits<streamsize>::max(), '\n');

            tasks.push_back(Task(title, deadline, priority, completed));
        }

        inFile.close();
    }

    void saveToFile() {
        ofstream outFile(filename);

        for (const Task& task : tasks) {
            outFile << task.title << endl;
            outFile << task.deadline << endl;
            outFile << task.priority << endl;
            outFile << task.completed << endl;
        }

        outFile.close();
    }

    void addTask() {
        string title, deadline;
        int priority;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter task title: ";
        getline(cin, title);

        cout << "Enter deadline (example: 2026-04-10): ";
        getline(cin, deadline);

        cout << "Enter priority (1 = High, 2 = Medium, 3 = Low): ";
        cin >> priority;

        while (priority < 1 || priority > 3) {
            cout << "Invalid priority. Please enter 1, 2, or 3: ";
            cin >> priority;
        }

        tasks.push_back(Task(title, deadline, priority, false));
        cout << "Task added successfully.\n";
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "\nNo tasks available.\n";
            return;
        }

        cout << "\n====== Task List ======\n";
        for (size_t i = 0; i < tasks.size(); i++) {
            cout << "Task #" << i + 1 << endl;
            cout << "Title     : " << tasks[i].title << endl;
            cout << "Deadline  : " << tasks[i].deadline << endl;
            cout << "Priority  : " << priorityToString(tasks[i].priority) << endl;
            cout << "Status    : " << (tasks[i].completed ? "Completed" : "Pending") << endl;
            cout << "--------------------------\n";
        }
    }

    void deleteTask() {
        if (tasks.empty()) {
            cout << "\nNo tasks to delete.\n";
            return;
        }

        viewTasks();
        int choice;
        cout << "Enter task number to delete: ";
        cin >> choice;

        if (choice < 1 || choice > (int)tasks.size()) {
            cout << "Invalid task number.\n";
            return;
        }

        tasks.erase(tasks.begin() + choice - 1);
        cout << "Task deleted successfully.\n";
    }

    void markTaskCompleted() {
        if (tasks.empty()) {
            cout << "\nNo tasks available.\n";
            return;
        }

        viewTasks();
        int choice;
        cout << "Enter task number to mark as completed: ";
        cin >> choice;

        if (choice < 1 || choice > (int)tasks.size()) {
            cout << "Invalid task number.\n";
            return;
        }

        tasks[choice - 1].completed = true;
        cout << "Task marked as completed.\n";
    }

    void sortByPriority() {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.priority < b.priority;
        });

        cout << "Tasks sorted by priority.\n";
    }

    void sortByDeadline() {
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.deadline < b.deadline;
        });

        cout << "Tasks sorted by deadline.\n";
    }

    string priorityToString(int priority) {
        if (priority == 1) return "High";
        if (priority == 2) return "Medium";
        return "Low";
    }

    void menu() {
        int choice;

        do {
            cout << "\n====== Student Task Manager ======\n";
            cout << "1. Add Task\n";
            cout << "2. View Tasks\n";
            cout << "3. Delete Task\n";
            cout << "4. Mark Task as Completed\n";
            cout << "5. Sort Tasks by Priority\n";
            cout << "6. Sort Tasks by Deadline\n";
            cout << "7. Save Tasks\n";
            cout << "8. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            while (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a number: ";
                cin >> choice;
            }

            switch (choice) {
                case 1:
                    addTask();
                    break;
                case 2:
                    viewTasks();
                    break;
                case 3:
                    deleteTask();
                    break;
                case 4:
                    markTaskCompleted();
                    break;
                case 5:
                    sortByPriority();
                    break;
                case 6:
                    sortByDeadline();
                    break;
                case 7:
                    saveToFile();
                    cout << "Tasks saved successfully.\n";
                    break;
                case 8:
                    saveToFile();
                    cout << "Tasks saved. Exiting program...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }

        } while (choice != 8);
    }
};

int main() {
    TaskManager manager;
    manager.loadFromFile();
    manager.menu();

    return 0;
}