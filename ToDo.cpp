#include "ToDo.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

// Function to generate the current time using chrono, and then converting it to ISO standard, so it can be assigned to created_date attribute
string getCurrentTime()
{
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);

    ostringstream oss;
    oss << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Constructor
ToDo::ToDo(string d, int p) : description(d),
                              priority(p),
                              created_date(getCurrentTime())
{
}

// Getters
string ToDo::getDescription() const { return description; }
int ToDo::getPriority() const { return priority; }
string ToDo::getCreatedDate() const { return created_date; }

// Setter
void ToDo::setCreatedDate(const string &cd) { created_date = cd; }