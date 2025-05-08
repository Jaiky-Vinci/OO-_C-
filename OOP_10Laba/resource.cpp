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
