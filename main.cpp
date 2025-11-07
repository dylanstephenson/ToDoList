#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "ToDo.h"

using namespace std;

// Once a file is loaded in, and while tasks are being added, the todos from the list are all printed in an ordered fashion
void printToDo(const vector<ToDo> &tasks)
{
    cout << "\nCurrent Tasks:\n";
    if (tasks.empty())
    {
        cout << "No tasks available.\n";
    }
    else
    {
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            cout << i << ": "
                 << tasks[i].getDescription()
                 << " (Priority: " << tasks[i].getPriority()
                 << ", Created: " << tasks[i].getCreatedDate() << ")\n";
        }
    }
    cout << endl;
}

// This function adds a todo to the list. User is prompted to provide description of the task, and priority between 1-3, and then the index number and created date are generated automatically
void addToDo(vector<ToDo> &todos, const string &desc, int priority)
{
    todos.emplace_back(desc, priority);
}

// This function removes todo from the list by index number
void removeToDo(vector<ToDo> &todos, size_t index)
{
    if (index < todos.size())
    {
        todos.erase(todos.begin() + index);
        cout << "To Do task " << index << " removed.\n";
    }
    else
    {
        cout << "Invalid index.\n";
    }
}

// Load tasks from file
void loadFromFile(const string &filename, vector<ToDo> &todos)
{
    ifstream infile(filename);
    if (!infile)
        return; // File doesn't exist

    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string desc, created;
        int priority;

        if (getline(ss, desc, '|') &&
            ss >> priority &&
            ss.ignore(1) &&
            getline(ss, created))
        {
            ToDo task(desc, priority);
            // Override created_date to match file
            // Assuming ToDo has a setter or a constructor modification
            // For simplicity, we can temporarily make created_date public or add a setter
            // Or we could modify the constructor to accept created_date as optional
            // Here, let's assume a setter exists:
            task.setCreatedDate(created);
            todos.push_back(task);
        }
    }
}

// Save tasks to file
void saveToFile(const string &filename, const vector<ToDo> &todos)
{
    ofstream outfile(filename);
    for (const auto &task : todos)
    {
        outfile << task.getDescription() << "|"
                << task.getPriority() << "|"
                << task.getCreatedDate() << "\n";
    }
}

int main()
{
    vector<ToDo> toDoList;
    string filename;
    string startChoice;

    // Ask the user whether to start a new file or load existing
    while (true)
    {
        cout << "Do you want to [L]oad an existing file or start a [N]ew file? ";
        getline(cin, startChoice);

        if (startChoice == "L" || startChoice == "l")
        {
            cout << "Enter the filename to load: ";
            getline(cin, filename);

            ifstream infile(filename);
            if (infile) // file exists
            {
                loadFromFile(filename, toDoList);
                cout << "Tasks loaded from " << filename << ".\n";
                break;
            }
            else
            {
                cout << "File does not exist. Please enter a valid filename.\n";
            }
        }
        else if (startChoice == "N" || startChoice == "n")
        {
            cout << "Enter a new filename to save tasks: ";
            getline(cin, filename);
            cout << "Starting a new task list.\n";
            break; // new file, list is empty
        }
        else
        {
            cout << "Invalid choice. Enter L to load or N to start new.\n";
        }
    }

    string choice;
    while (true)
    {
        printToDo(toDoList);

        cout << "Options: [A]dd task, [D]elete task, [E]xit and save: ";
        getline(cin, choice);

        if (choice == "A" || choice == "a")
        {
            string desc;
            int priority;

            cout << "Enter task description: ";
            getline(cin, desc);

            // Priority validation
            while (true)
            {
                cout << "Enter task priority (1 lowest, 3 highest): ";
                cin >> priority;
                if (cin.fail() || priority < 1 || priority > 3)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid priority. Please enter 1, 2, or 3.\n";
                }
                else
                {
                    cin.ignore();
                    break;
                }
            }

            addToDo(toDoList, desc, priority);
            cout << "Task added.\n";
        }
        else if (choice == "D" || choice == "d")
        {
            size_t index;
            cout << "Enter task index to delete: ";
            cin >> index;
            cin.ignore();
            removeToDo(toDoList, index);
        }
        else if (choice == "E" || choice == "e")
        {
            saveToFile(filename, toDoList);
            cout << "Tasks saved to " << filename << ". Exiting program.\n";
            break;
        }
        else
        {
            cout << "Invalid option. Please choose A, D, or E.\n";
        }
    }

    return 0;
}
