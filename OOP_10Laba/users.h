#pragma once
#include <string>
#include <iostream>

class User {
protected:
    std::string name;
    int id;
    int accessLevel;

public:
    User(const std::string& name, int id, int accessLevel);
    virtual ~User();

    std::string getName() const;
    int getId() const;
    int getAccessLevel() const;

    virtual void displayInfo() const;
    virtual std::string toCSV() const;
};

class Student : public User {
    std::string group;
public:
    Student(const std::string& name, int id, int accessLevel, const std::string& group);
    void displayInfo() const override;
    std::string toCSV() const override;
};

class Teacher : public User {
    std::string department;
public:
    Teacher(const std::string& name, int id, int accessLevel, const std::string& department);
    void displayInfo() const override;
    std::string toCSV() const override;
};

class Administrator : public User {
    std::string role;
public:
    Administrator(const std::string& name, int id, int accessLevel, const std::string& role);
    void displayInfo() const override;
    std::string toCSV() const override;
};
