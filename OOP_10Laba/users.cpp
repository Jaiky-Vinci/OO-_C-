#include "users.h"
#include <stdexcept>

User::User(const std::string& name, int id, int accessLevel)
    : name(name), id(id), accessLevel(accessLevel) {
    if (name.empty()) throw std::invalid_argument("Имя не может быть пустым.");
    if (accessLevel < 0) throw std::invalid_argument("Уровень доступа не может быть отрицательным.");
}

User::~User() {}

std::string User::getName() const { return name; }
int User::getId() const { return id; }
int User::getAccessLevel() const { return accessLevel; }

void User::displayInfo() const {
    std::cout << "Name: " << name << ", ID: " << id << ", Access Level: " << accessLevel << std::endl;
}

std::string User::toCSV() const {
    return "User," + name + "," + std::to_string(id) + "," + std::to_string(accessLevel);
}

Student::Student(const std::string& name, int id, int accessLevel, const std::string& group)
    : User(name, id, accessLevel), group(group) {}

void Student::displayInfo() const {
    std::cout << "[Student] ";
    User::displayInfo();
    std::cout << "Group: " << group << std::endl;
}

std::string Student::toCSV() const {
    return "Student," + name + "," + std::to_string(id) + "," + std::to_string(accessLevel) + "," + group;
}

Teacher::Teacher(const std::string& name, int id, int accessLevel, const std::string& department)
    : User(name, id, accessLevel), department(department) {}

void Teacher::displayInfo() const {
    std::cout << "[Teacher] ";
    User::displayInfo();
    std::cout << "Department: " << department << std::endl;
}

std::string Teacher::toCSV() const {
    return "Teacher," + name + "," + std::to_string(id) + "," + std::to_string(accessLevel) + "," + department;
}

Administrator::Administrator(const std::string& name, int id, int accessLevel, const std::string& role)
    : User(name, id, accessLevel), role(role) {}

void Administrator::displayInfo() const {
    std::cout << "[Administrator] ";
    User::displayInfo();
    std::cout << "Role: " << role << std::endl;
}

std::string Administrator::toCSV() const {
    return "Administrator," + name + "," + std::to_string(id) + "," + std::to_string(accessLevel) + "," + role;
}
