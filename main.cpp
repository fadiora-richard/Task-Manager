#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Task //Class defining tasks
{
    private:

    string name;
    int priority;

    public:
    
    void display()
    {
        cout << "Task: " << name << ", Priority: " << priority << endl;
    }
    void setName(string name)
    {
        this->name = name;
    }

    void setPriority(int priority)
    {
        this->priority = priority;
    }

    int getPriority()
    {
        return priority;
    }
    string getName()
    { 
        return name;
    }
    
};

vector<Task> taskList; //To store the tasks in the program
string filename = "taskFile.txt";

void loadTasksFromFile() //Loads tasks from the file they're saved to to allow for viewing
{
    ifstream taskFile(filename);

    if (!taskFile) 
    {
    cerr << "⚠️ File not found: " << filename << ". Starting fresh.\n";
    return;
    }

    taskList.clear();

    string name;
    int priority;

    while(getline(taskFile, name))
    {
        if(taskFile >> priority)
        {
            taskFile.ignore();
            Task task;
            task.setName(name);
            task.setPriority(priority);
            taskList.push_back(task);
        }
    }

    taskFile.close();
}
void saveTasksToFile() //Saves tasks to a file 
{
    ofstream taskFile(filename);

    if (!taskFile) 
    {
    cerr << "❌ Failed to create or open file: " << filename << endl;
    return;
    }

    for(Task task : taskList)
    {
        taskFile << task.getName() << ", "<< task.getPriority() << endl;
    }

    taskFile.close();
}
void showMenu() // Shows the menu 
{
    cout << "========== Task Manager ==========" << endl 
    << "1. Add Task" << endl
    << "2. View Tasks" << endl
    << "3. Delete Task" << endl
    << "4. Exit" << endl
    << "==================================" << endl
    << "Enter your choice: ";
}
void addTask() //Adds a task to the file and vector for saving
{
    Task newTask;
    string name;
    int priority;

    cout << "Enter task name: ";
    cin.ignore();
    getline(cin, name);

    newTask.setName(name);

    cout << "Enter task priority (1 = Low, 2 = Medium, 3 = High): ";

    cin >> priority;   
    
    newTask.setPriority(priority);

    taskList.push_back(newTask);

    saveTasksToFile();

    cout << "Task added!" << endl;

}
void viewTasks() //Allows the task details to be seen
{
    loadTasksFromFile();
    

    if (taskList.empty()) {
        cout << "No tasks yet." << endl;
        return;
    }

    for(int i = 0; i < taskList.size(); i++)
    {
        cout << i+1 << ". ";
        taskList[i].display();
    }

    

    
}
void deleteTask() //Deletes a task
{
    loadTasksFromFile();

    if (taskList.empty()) {
        cout << "No tasks to delete." << endl;
        return;
    }

    int choice;

    viewTasks();

    cout << "What task would you like to delete?: " << endl;
    cin >> choice;

    if(choice > 0 && choice <= taskList.size())
    {
        taskList.erase(taskList.begin() + (choice - 1));
        saveTasksToFile();
        cout << "Task Deleted!" << endl;
    }
    else
    {
        cout << "An error occurred." << endl;
    }
   
}
int main()
{
    int choice;

    while(true)
    {
        showMenu();
        cin >> choice;

        switch(choice)
        {
            case 1:
            cout << "Adding Task..." << endl;
            addTask();
            break;

           case 2:
            cout << "Listing Tasks..." << endl;
            viewTasks();
            break;

            case 3:
            cout << "Deleting Task..." << endl;
            deleteTask();
            break;

            case 4:
            cout << "Goodbye!" << endl;
            return 0;

            default:
            cout << "Invalid Input." << endl;
            return 0;
        }

        cout << endl;
    }
    
}