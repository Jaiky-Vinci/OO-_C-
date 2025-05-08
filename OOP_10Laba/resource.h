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
