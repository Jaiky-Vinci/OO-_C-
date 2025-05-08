#pragma once
#include <string>
#include "users.h"

class Resource {
    std::string name;
    int requiredAccessLevel;

public:
    Resource(const std::string& name, int requiredAccessLevel);
    bool checkAccess(const User& user) const;
    std::string getName() const;
    std::string toCSV() const;
};

// ===== resource.cpp =====
#include "resource.h"

Resource::Resource(const std::string& name, int requiredAccessLevel)
    : name(name), requiredAccessLevel(requiredAccessLevel) {}

bool Resource::checkAccess(const User& user) const {
    return user.getAccessLevel() >= requiredAccessLevel;
}

std::string Resource::getName() const {
    return name;
}

std::string Resource::toCSV() const {
    return name + "," + std::to_string(requiredAccessLevel);
}
