#ifndef TODO_H
#define TODO_H

#include <string>

using namespace std;

class ToDo
{
private:
    string created_date;
    string description;
    // The priority will be 1-3. 1 is low, 2 is medium priority, and 3 is high. This will make it easy to do error validation when constructing the class, as the int must be between 1, 2, or 3.
    int priority;

public:
    // Constructor
    ToDo(string description, int priority);

    // Getters
    std::string getDescription() const;
    int getPriority() const;
    std::string getCreatedDate() const;

    // Setter for created date (used when loading from file)
    void setCreatedDate(const std::string &cd);
};

#endif